#include<conio.h>
#include<iostream.h>
#include<fstream.h>


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
	fstream f;	
	PLAYER a = {10,10,10};
	strcpy(a.userName, "shyam");
	f.open("Player.dat",ios::binary|ios::out|ios::ate);
	f.seekp(a.show_ID()*sizeof(PLAYER));
	f.write((char *)&a,sizeof(PLAYER));
	getch();
}
