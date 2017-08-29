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
	PLAYER a  = {10,10,10};
	strcpy(a.userName, "shyam");
	a.money = 1;
	a.wood = 2;
	a.water = 3;
	a.produce = 4;
	a.maxXp = 10;
	a.index = 10;

	f.open("player.dat", ios::binary|ios::app);
	f.write((char*)&a, sizeof(a));
	f.close();

}
