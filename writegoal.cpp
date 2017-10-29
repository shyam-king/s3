#include<iostream>
#include<fstream>
#include<string>
#include<stdlib.h>

using namespace std;

struct Goaldata
{
	char title[40];
	char message[10][80];
	int message_length;
	int image_index;
} ;

Goaldata readGoal(int n)
{
	ifstream fin("GOALDATA.DAT");
	Goaldata t;
	fin.seekg(n * sizeof(t));
	fin.read((char*)&t, sizeof(t));
	fin.close();
	return t;
}

Goaldata appendGoal()
{
	ofstream fout("GOALDATA.DAT", ios::app);
	Goaldata t;
	string str; 
	cout << "ENTER TITLE: ";

	cin.ignore(256, '\n');

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
	cin >> t.image_index;

	fout.write((char*) &t, sizeof(t));
	fout.close();
}

int noOfGoals()
{
	ofstream fout("GOALDATA.DAT", ios::ate);
	return fout.tellp() / sizeof(Goaldata);
}

void viewAllGoals()
{
	int n = noOfGoals();
	for (int i = 0; i < n; i++)
	{
		Goaldata t = readGoal(i);
		cout << t.title << '\n';
		for (int j = 0; j < t.message_length; j++)
			cout << t.message[j] << endl;
		cout << t.image_index;
		char c = cin.get(); // wait for a key press
		if (c == 'x')
			break;
	}
}

int main(int argc, char *argv[])
{
	int mc = 0;
	if (argc > 1)
		mc = atoi(argv[1]);

	cout << "NUMBER OF GOALS: " << noOfGoals() << endl;
	cout << "1 - VIEW A GOAL\n";
	cout << "2 - APPEND A GOAL\n";
	if (!mc)
	{
		cout << "ENTER YOUR CHOICE: ";
		cin >> mc;
	}

	switch(mc)
	{
		case 2:
			appendGoal();
			break;
	}
	return 0;
}
