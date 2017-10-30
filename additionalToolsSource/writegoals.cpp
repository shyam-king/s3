/* THIS FILE IS TO WRITE TO GOALDATA.DAT
*/
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
	char goalObjective[40]; 
	char postGoalCommand[40];
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
	ifstream fin("GOALDATA.DAT", ios::binary);
	ofstream fout("TEMP.DAT", ios::binary);

	Goaldata t;
	int i = 0;
	while (fin.read((char*)&t, sizeof(t)))
	{
		if (i!= n)
			fout.write((char*)&t, sizeof(t));
		else
			fout.write((char*)&g, sizeof(g));

		i++;
	}

	fout.close();
	fin.close();

	remove("GOALDATA.DAT");
	rename("TEMP.DAT", "GOALDATA.DAT");

}

//To insert a goal
void insertGoalToFile(Goaldata g, int n)
{
	ifstream originalFile("GOALDATA.DAT", ios::binary);
	ofstream duplicate("GOALDAT2.DAT", ios::binary);

	Goaldata t;

	int i = 0;
	while(originalFile.read((char*)&t, sizeof(t)))
	{
		if (i == n)
			duplicate.write((char*)&g, sizeof(g));
		duplicate.write((char*)&t, sizeof(t));
		i++;
	}

	originalFile.close();
	duplicate.close();

	remove("GOALDATA.DAT");
	rename("GOALDAT2.DAT", "GOALDATA.DAT");
}

void removeGoal(int n)
{
	ifstream fin;
	ofstream fout;
	fin.open("GOALDATA.DAT", ios::binary);
	fout.open("temp.dat", ios::binary);

	Goaldata g;

	while (fin.read((char*)&g, sizeof(g)))
	{
		static int i = 0;
		if (i != n)
		{
			fout.write((char*)&g, sizeof(g));
		}
		i++;
	}

	fout.close();
	fin.close();

	remove("GOALDATA.DAT");
	rename("temp.dat", "GOALDATA.DAT");

}


//to print all the goals
void printAllGoals()
{
	ifstream file("GOALDATA.DAT", ios::binary);
	Goaldata g;
	clrscr();
	int ind = 0;
	char k = '0';
	while(file.read((char*)&g , sizeof(g)) && tolower(k) != 'e')
	{
		clrscr();
		cout << "Goal index = " << ind << endl;
		ind ++;
		puts(g.title);
		for(int i = 0; i < g.message_length; i++)
			puts(g.message[i]);
		cout << g.message_length << endl;
		cout << g.image_index << endl;
		cout << g.goalObjective << endl;
		cout << g.postGoalCommand;
		k = getch();
	}
	file.close();
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
	int x;
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
		cout << "\t6 - REMOVE A GOAL\n";

		uc = tolower(getch());
		cout << endl << "Enter details:\n";

		switch(uc - '0')
		{
			case 1: 
				cout << "Enter title:";
				gets(g.title);
				cout << "Enter message length:";
				cin >> g.message_length;
				cout << "Enter message: \n";
				for ( i =0; i < g.message_length ; i++)
					gets(g.message[i]);
				cout << "Enter image index:";
				cin >> g.image_index;
				cout << "Enter goal objective:";
				gets(g.goalObjective);
				cout << "Enter goal command:";
				gets(g.postGoalCommand);

				addGoalToFile(g);
				break;
			case 2: 
				cout << "Enter title:";
				gets(g.title);
				cout << "Enter message length:";
				cin >> g.message_length;
				cout << "Enter message: \n";
				for ( i =0; i < g.message_length ; i++)
					gets(g.message[i]);
				cout << "Enter image index:";
				cin >> g.image_index;
				cout << "Enter goal objective:";
				gets(g.goalObjective);
				cout << "Enter goal command:";
				gets(g.postGoalCommand);
				cout << "Enter position:";
				cin >> i;

				insertGoalToFile(g, i);
				break;
			case 3: 
				cout << "Enter position:";
				cin >> i;
				g = viewGoalFromFile(i);
				puts(g.title);
				for(i = 0; i < g.message_length; i++)
					puts(g.message[i]);
				cout << g.message_length << endl;
				cout << g.image_index;
				cout << endl << g.goalObjective << endl;
				cout << g.postGoalCommand;
				break;
			case 4:
				printAllGoals();
				break;
			case 5:
				cout << "Enter position:";
				cin >> x;

				cout << "ORIGINAL ENTRY:\n";
				g = viewGoalFromFile(x);
				puts(g.title);
				for(i = 0; i < g.message_length; i++)
					puts(g.message[i]);
				cout << g.image_index;
				cout << endl << g.goalObjective << endl;
				cout << g.postGoalCommand;
				cout << endl;

				cout << "Enter title:";
				gets(g.title);
				cout << "Enter message length:";
				cin >> g.message_length;
				cout << "Enter message: \n";
				for ( i =0; i < g.message_length ; i++)
					gets(g.message[i]);
				cout << "Enter image index:";
				cin >> g.image_index;
				cout << "Enter goal objective:";
				gets(g.goalObjective);
				cout << "Enter goal command:";
				gets(g.postGoalCommand);
				replaceGoalInFile(g,  x);
				break;

			case 6:
				cout << "Enter the goal index: ";
				cin >> i;
				removeGoal(i);
				break;
			default:
				cout << "Invalid choice!";
		}
		cout << "\nPRESS (Y/y) TO RESTART..";
		uc = tolower(getch());

	}while(uc == 'y');
}
