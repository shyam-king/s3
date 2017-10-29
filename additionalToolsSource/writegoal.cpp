#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>
#include<limits>


using namespace std;

struct Goaldata
{
	char title[40];
	char message[10][80];
	int message_length;
	int image_index;
} ;

//accepting a value from std in
	template <class type>
void accept(type &var)
{
	cin >> var;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//read a single goal
Goaldata readGoal(int n)
{
	ifstream fin("GOALDATA.DAT");
	Goaldata t;
	fin.seekg(n * sizeof(t));
	fin.read((char*)&t, sizeof(t));
	fin.close();
	return t;
}

void editGoal(int n)
{
	Goaldata t;
	ifstream fin("GOALDATA.DAT");
	fin.seekg(n * sizeof(t));
	fin.read((char*)&t, sizeof(t));
	fin.close();
	fstream fout("GOALDATA.DAT", ios::in | ios::out);
	fout.seekp(n * sizeof(t));
	cout << "OLD TITLE: " << t.title << endl;
	cout << "NEW TITLE: ";
	string str;
	getline(cin, str);
	str.copy(t.title, str.length(), 0);
	cout << "OLD MESSAGE: " << endl;
	for (int j = 0; j < t.message_length; j++)
		cout << t.message[j] << endl;
	cout << endl;
	cout << "NEW MESSAGE: " << endl;
	int i = 0;
	do 
	{
		getline(cin, str);
		if (str.compare("--") != 0)
		{
			str.copy(t.message[i++], str.length(), 0);
		}
	} while (str.compare("--") != 0);

	t.message_length = i;

	cout << "OLD IMAGE INDEX: " << t.image_index << endl;
	cout << "NEW IMAGE INDEX: ";
	accept(t.image_index);


	fout.write((char*)&t, sizeof(t));
	fout.close();

}

//append a goal to the end
void appendGoal()
{
	Goaldata t;
	string str; 
	cout << "ENTER TITLE: ";
	getline(cin, str);
	str.copy(t.title, str.length(), 0);
	cout << "Enter message (-- to stop):\n";
	int i = 0;
	do 
	{
		getline(cin, str);
		if (str.compare("--") != 0)
		{
			str.copy(t.message[i++], str.length(), 0);
		}
	} while (str.compare("--") != 0);

	t.message_length = i;
	cout << "Enter image index: ";
	accept(t.image_index);

	ofstream fout("GOALDATA.DAT", ios::app);
	fout.write((char*) &t, sizeof(t));
	fout.tellp();
	fout.close();
}

//total no of goals present in the goaldata.dat file
int noOfGoals()
{
	ifstream f("GOALDATA.DAT");
	f.seekg(0, ios::end);
	int p = f.tellg();
	f.close();
	return p / (int)(sizeof(Goaldata));
}

//to print all the goals
void viewAllGoals()
{
	int n = noOfGoals();
	for (int i = 0; i < n; i++)
	{
		cout << "index: " << i << endl;
		Goaldata t = readGoal(i);
		cout << t.title << '\n';
		for (int j = 0; j < t.message_length; j++)
			cout << t.message[j] << endl;
		cout << t.image_index;
		cout << endl;
		cout << endl;
		char c = cin.get();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (c == 'x') return;
	}
}

//inserting a goal in the specified position
void insertGoal(int x)
{
	Goaldata t;
	string str; 
	cout << "ENTER TITLE: ";

	getline(cin, str);
	str.copy(t.title, str.length(), 0);
	cout << "Enter message (-- to stop):\n";
	int i = 0;
	do 
	{
		getline(cin, str);
		if (str.compare("--") != 0)
		{
			str.copy(t.message[i++], str.length(), 0);
		}
	} while (str.compare("--") != 0);

	t.message_length = i;
	cout << "Enter image index: ";
	accept(t.image_index);

	ofstream temp("temp.dat");
	ifstream f("GOALDATA.DAT");

	Goaldata b;
	i = 0;
	while(f.read((char*)&b, sizeof(b)))
	{
		if (i == x)
			temp.write((char*)&t, sizeof(t));
		temp.write((char*)&b, sizeof(b));
		i++;
	}
	f.close();
	temp.close();
	remove("GOALDATA.DAT");
	rename("temp.dat", "GOALDATA.DAT");
}

//the main program
int main(int argc, char *argv[])
{
	int mc = 0;
	if (argc > 1)
		mc = atoi(argv[1]);

	cout << "NUMBER OF GOALS: " << noOfGoals() << endl;
	cout << "1 - VIEW ALL GOAL\n";
	cout << "2 - APPEND A GOAL\n";
	cout << "3 - INSERT A GOAL\n";
	cout << "4 - VIEW A GOALS\n";
	cout << "5 - EDIT A GOAL\n";
	if (!mc)
	{
		cout << "ENTER YOUR CHOICE: ";
		accept(mc);
	}
	int x;
	Goaldata t;

	switch(mc)
	{
		case 1:
			viewAllGoals();
			break;
		case 2:
			appendGoal();
			break;
		case 3:
			cout << "Enter the index: ";
			accept(x);
			insertGoal(x);
			break;
		case 5:
			cout << "Enter the index: ";
			accept(x);
			editGoal(x);
			break;
		case 4:
			cout << "Enter the index: ";
			accept(x);
			t = readGoal(x);
			cout << "TITLE: " << t.title << endl;
			cout << "MESSAGE: \n";
			for (x = 0; x < t.message_length; x++)
				cout << t.message[x] << endl;
			cout << "IMAGE INDEX: " << t.image_index;
			break;
	}
	return 0;
}
