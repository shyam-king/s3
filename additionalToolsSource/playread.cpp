#include<conio.h>
#include<iostream.h>
#include<fstream.h>
#include<string.h>
#include<stdio.h>


struct PLAYER
{
	int currXp;
	int id;
	int playerLevel;
	int userIcon[10][10];
	char userName[80];
	unsigned long money,wood,produce,water;
	int maxXp;
	int index;
};

void main()
{
	clrscr();
	fstream f;	
	PLAYER a ;

	f.open("player.dat", ios::binary|ios::in);
	while(f.read((char*)&a, sizeof(a)))
	{
		puts(a.userName);
		cout << a.produce << endl;
		cout << a.water << endl;
		cout << a.money << endl;
		cout << a.wood << endl;
		cout << a.id << endl;
		cout << endl;
		getch();
	}
}
