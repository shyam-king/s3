#include<conio.h>
#include<iomanip.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<iostream.h>
#include<fstream.h>

//added a comment!


struct Goaldata
{
	char title[40];
	char message[10][80];
	int message_length;
	int image_index;
} ;

//Write to the file
void addGoalToFile(Goaldata g)
{
	ofstream file("GOALDATA.DAT", ios::binary | ios::app);
	file.write((char*) &g, sizeof(g));
	file.close();
}


//Read from the file
Goaldata viewGoalFromFile(int n)
{
	Goaldata g;
	ifstream file("GOALDATA.DAT", ios::binary);
	file.seekg(n * sizeof(g));
	file.read((char*)&g, sizeof(g));
	file.close();

	return g;
}


//To edit the already existing goal in the file
void replaceGoalInFile(Goaldata g, int n)
{
	ofstream file("GOALDATA.DAT", ios::binary | ios::ate);	
	file.seekp(sizeof(g) * n);
	file.write((char*)&g, sizeof(g));
	file.close();
}

//To insert a goal
void insertGoalToFile(Goaldata g, int n)
{
	ifstream originalFile("GOALDATA.DAT", ios::binary);
	ofstream duplicate("GOALDAT2.DAT", ios::binary);

	Goaldata t;

	for (int i = 0; i < n; i++)
	{
		originalFile.read((char*)&t, sizeof(t));
		duplicate.write((char*)&t, sizeof(t));
	}

	duplicate.write((char*)&g, sizeof(g));

	while(originalFile.read((char*)&t, sizeof(t)))
	{
		duplicate.write((char*)&t, sizeof(t));
	}

	originalFile.close();
	duplicate.close();

	remove("GOALDATA.DAT");
	rename("GOALDAT2.DAT", "GOALDATA.DAT");
}


//to print all the goals
void printAllGoals()
{
	ifstream file("GOALDATA.DAT");
	Goaldata g;
	clrscr();
	while(file.read((char*)&g , sizeof(g)))
	{
		clrscr();
		puts(g.title);
		for(int i = 0; i < g.message_length; i++)
			puts(g.message[i]);
		cout << g.message_length << endl;
		cout << g.image_index;
		getch();
	}
}

//to print at the center of the screen
void print(char *t)
{
	cout << setw(40 + strlen(t)/2) << t << endl;
}

void main()
{
	clrscr();
	Goaldata g;
	int i;
	char uc;
	do
	{
		clrscr();
		print("EDITING GOALDATA");
		print("----------------");
		cout << "\t1 - ADD A NEW GOAL";
		cout << "\n\t2 - INSERT A NEW GOAL\n";
		cout << "\t3 - VIEW A GOAL\n";
		cout << "\t4 - LIST ALL GOALS\n";
		cout << "\t5 - REPLACE A GOAL\n";

		uc = tolower(getch());
		cout << endl << "Enter details:\n";

		switch(uc - '0')
		{
			case 1: 
				gets(g.title);
				cin >> g.message_length;
				for ( i =0; i < g.message_length ; i++)
					gets(g.message[i]);
				cin >> g.image_index;

				addGoalToFile(g);
				break;
			case 2: 
				gets(g.title);
				cin >> g.message_length;
				for ( i =0; i < g.message_length ; i++)
					gets(g.message[i]);
				cin >> g.image_index;
				cin >> i;

				insertGoalToFile(g, i);
				break;
			case 3: 
				cin >> i;
				g = viewGoalFromFile(i);
				puts(g.title);
				for(i = 0; i < g.message_length; i++)
					puts(g.message[i]);
				cout << g.message_length << endl;
				cout << g.image_index;
				break;
			case 4:
				printAllGoals();
				break;
			case 5:
				gets(g.title);
				cin >> g.message_length;
				for ( i =0; i < g.message_length ; i++)
					gets(g.message[i]);
				cin >> g.image_index;
				cin >> i;
				replaceGoalInFile(g,  i);
				break;

			default:
				cout << "Invalid choice!";
		}
		cout << "\nPRESS (Y/y) TO RESTART..";
		uc = tolower(getch());


	}while(uc == 'y');
	getch();
}
