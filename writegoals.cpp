#include<conio.h>
#include<iostream.h>
#include<fstream.h>


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


void main()
{
	clrscr();

	getch();
}
