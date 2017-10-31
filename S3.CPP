
/************************************************************
  "Atlantis" Management Game made by Shankrith, Shyam and Sriram
 ************************************************************/


/////////////////////////HEADER FILES////////////////////////////
#include<iostream.h>
#include<conio.h>
#include<graphics.h>
#include<dos.h>
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<process.h>


/////////////////////////GLOBAL VARIABLES/////////////////////////

//nothing here...


/////////////////////Our own header file///////////////////////////
#include"s3tools.h"
#include"s3game.h"

/////////////////////////FUNCTION PROTOTYPES////////////////////////


void displayAnim();

//////////////////////////MAIN FUNCTION//////////////////////////
void main()
{
	// INITIALIZING GRAPHICS
	int gd = DETECT, gm;
	//int menuChoice = 0;
	initgraph(&gd, &gm, "..\\bgi");
	SCREEN_H = getmaxy();
	SCREEN_W =  getmaxx();
	//drawAtlantis();
	//delay(3000);


	//TO SKIP STRAIGHT TO THE GAME_NEW

	/*
		gameNew();
		exit(0);
	/* */

	displayAnim();
	delay(100);
	drawAtlantis();
	displayMenu();


	closegraph();
}

//////////////////////////////////FUNCTION DEFINITIONS/////////////////

/*
void displayAnim()
{
	randomize();
	setcolor(RED);
	settextstyle(7, HORIZ_DIR, 7);
	char title[] = "Virtz";
	int j;
	for (j = 0; j < 6; j++)
		outtextxy(getmaxx()/2 - textwidth(title)/2 + j, getmaxy()/2 - textheight(title)/2 + j, title);

	int i;
	int color[] = {BLUE, LIGHTBLUE, CYAN, LIGHTCYAN};
	for (i = 0; i<=100; i++)
	{
		setcolor(color[i % (sizeof(color)/2)]);
		arc(getmaxx()/2 , getmaxy()/2 , 0, 90, i + 100);
		arc(getmaxx()/2 , getmaxy()/2 , 180, 270, i + 100);
		delay(10);
	}

	int c2[] = {GREEN, LIGHTGREEN, LIGHTGRAY};

	for (i= 0; i<=50; i++)
	{
		setcolor(c2[i % (sizeof(c2)/2)]);
		arc(getmaxx()/2 , getmaxy()/2 , 100, 170, i + 130);
		arc(getmaxx()/2 , getmaxy()/2 , 280, 350, i + 130);
		delay(20);
	}

	setcolor(WHITE);
	settextstyle(1,HORIZ_DIR, 2);

	for (i = 0; i>= 0; i--)
		outtextxy(450 - i, getmaxy()-80 - i, "Presents you...");

	for (i =0; i <= getmaxx(); i++)
	{
		setcolor(MAGENTA);
		drawtline(0, getmaxy()-20, i, getmaxy()-20, 5);
		delay(i%20);
	}

}
*/

void displayAnim()
{
	int c[] = {GREEN, GREEN, BLUE, BLUE};
while (!kbhit())
	{ static int j = 0;
		for(int i=0,k=350;i<350;i++,k--)
		{
				//coloured inner arcs
				setcolor(c[i% (sizeof(c)/2)]);
				if (j%2)
				{
				arc(getmaxx()/2,getmaxy()/2,i+0,i+30,i);
				arc(getmaxx()/2,getmaxy()/2,i+60,i+90,i);
				arc(getmaxx()/2,getmaxy()/2,i+120,i+150,i);
				arc(getmaxx()/2,getmaxy()/2,i+180,i+210,i);
				arc(getmaxx()/2,getmaxy()/2,i+240,i+270,i);
				arc(getmaxx()/2,getmaxy()/2,i+300,i+330,i);
				}
				else
				{

				arc(getmaxx()/2,getmaxy()/2,i+30,i+60,i);
				arc(getmaxx()/2,getmaxy()/2,i+90,i+120,i);
				arc(getmaxx()/2,getmaxy()/2,i+150,i+180,i);
				arc(getmaxx()/2,getmaxy()/2,i+210,i+240,i);
				arc(getmaxx()/2,getmaxy()/2,i+270,i+300,i);
				arc(getmaxx()/2,getmaxy()/2,i+330,i+360,i);
				}
				setcolor(BLACK);
				if(j%2)
				{
					arc(getmaxx()/2,getmaxy()/2,k+330,k+360,k);
					arc(getmaxx()/2,getmaxy()/2,k+270,k+300,k);
					arc(getmaxx()/2,getmaxy()/2,k+210,k+240,k);
					arc(getmaxx()/2,getmaxy()/2,k+150,k+180,k);
					arc(getmaxx()/2,getmaxy()/2,k+90,k+120,k);
					arc(getmaxx()/2,getmaxy()/2,k+30,k+60,k);
				}
				else
				{
					arc(getmaxx()/2,getmaxy()/2,k+300,k+330,k);
					arc(getmaxx()/2,getmaxy()/2,k+240,k+270,k);
					arc(getmaxx()/2,getmaxy()/2,k+180,k+210,k);
					arc(getmaxx()/2,getmaxy()/2,k+120,k+150,k);
					arc(getmaxx()/2,getmaxy()/2,k+60,k+90,k);
					arc(getmaxx()/2,getmaxy()/2,k+0,k+30,k);
				}
				for (int t = 0; t < 5; t++)
				{
					setcolor(WHITE);
					settextstyle(7, HORIZ_DIR, 7);   //5
					outtextxy(getmaxx()/2 - textwidth("Virtz")/2 -2 + t,
										getmaxy()/2 - textheight("Virtz")/2, "Virtz");
				}
		 }
		 j++;
		}
		getch(); // may stop the pressed key from proceeding to the menu...
}
