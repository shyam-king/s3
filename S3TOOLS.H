#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<dos.h>
#include<math.h>

//S3 tools (helper functions and some intro functions too)
#ifndef S3TOOLS_H
#define S3TOOLS_H


/////////////////////////GLOBAL VARIABLES////////////////////////
/////////////////////////////AND MACROS//////////////////////////
#define PI 3.1415926535

//screen
int SCREEN_W, SCREEN_H; 

//ASCII VALUES FOR ARROW KEYS
const int LEFT =75;
const int RIGHT =77;
const int UP =72;
const int DOWN =80;

//USED FOR DIFFERENTIATING IF THE USER HAS PRESSED A KEY OR NOT
const char NOKEY = '0';

//Mouse stuff
union REGS in, out;

/////////////////////////FUNCTION PROTOTYPES//////////////////////
void strSplit(char *src, char dest[][20], char symbol);
char *inttochar(int);
void outtextcenter(int y, char*);
void drawtarc(int, int, int, int, int, int);
void initmouse();
void mousereset();
void mousestatus();
void displayAbout();
void drawtline(int, int, int, int, int);
void drawAtlantis () ;
void drawthickline ( int , int , int , int , int ) ;
char keyboardInput(char);
void string_copy(char*, char*, int);
void eraseLastChar(char*);
void tune(double, int);
void displayPara(int style, int x, int y, char credits[][80], char *cursor,int n, int delaySpd);
double toRadians(double deg);
double toDegrees(double rad);
char *formatString(int type, char string[]);
void drawellipse(int x, int y, int xrad, int yrad, double angle);
void tcircle ( int x , int y , int r , int t );
int stringSearch(char list[20][15], char *str);

////////////////////////FUNCTION DEFINITIONS//////////////////////

//For getting keyboard input 
char keyboardInput(char nk)
{
	char k = nk;
	if (kbhit()) k = getch();
	else k = nk;
	return k;
}

//For drawing thick arcs
void drawtarc(int x, int y, int stangle, int endangle, int r, int t)
{
	for (int l =0; l <= t; l++)
	{
		arc(x,y, stangle, endangle, r-l);
	}
}

// initializing mouse

void initmouse()
{
	in.x.ax = 1;
	int86(51,&in,&out);
}

//refreshing mouse status
void mousestatus()
{
	in.x.ax = 3;
	int86(51, &in, &out);
}

//changing integers to string
char *inttochar(int n){
	char *s;
	sprintf(s, "%d", n);
	return s;
}

//deleting the mouse

void mousereset()
{
	in.x.ax = 2;
	int86(51, &in, &out);
}

//to display the about screen

void displayAbout()
{

	//cleardevice();

	int x = 25, y = 50;
	settextstyle(7,HORIZ_DIR,1);
	setcolor(MAGENTA);

	int i = 0;
	setcolor(MAGENTA);
	cleardevice();
	rectangle(5,5,635,475);
	rectangle(10,10,630,470);
	outtextxy(x,y   ,"Alas!!! Myth has finally turned into legend. The long");
	outtextxy(x,y+30," lost radical city has been found. Thanks to the");
	outtextxy(x,y+60,"hard work of an archaeologist humans can now ");
	outtextxy(x,y+90,"really begin to understand that the ancient");
	outtextxy(x,y+120,"civilisations were far more advanced than us. But....");
	outtextxy(x,y+150,"Plato’s vision is now in ruins thanks to time and");
	outtextxy(x,y+180,"nature. The archaeologist has outdone himself but ");
	outtextxy(x,y+210,"society had other plans for him. The Legendary");
	outtextxy(x,y+240,"ATLANTIS, the land of the most advanced");
	outtextxy(x,y+270,"civilisation to have ever lived on Earth is now in the  ");
	outtextxy(x,y+300,"hands of an archaeologist to develop and protect.");
	outtextxy(x,y+330,"Can he protect the city from further disasters? Is");
	outtextxy(x,y+360,"he really capable of that much stress and planning.");
	outtextxy(x,y+390,"Can he really manage time and win over nature?");
	getch();

	cleardevice();
	rectangle(5,5,635,475);
	rectangle(10,10,630,470);
	outtextxy(x,y   ,"Atlantis is a management game that tests the");
	outtextxy(x,y+30," player’s ability to foresee, plan and productively");
	outtextxy(x,y+60,"manage time. The player is the archaeologist who");
	outtextxy(x,y+90,"has to renew and re-establish a city and develop it.");
	outtextxy(x,y+120,"But this is not as easy as it sounds for there are");
	outtextxy(x,y+150,"many deadly traps. The city has limited resources");
	outtextxy(x,y+180,"which can only be saved and balanced with proper");
	outtextxy(x,y+210,"planning. If the player is a little careless he might");
	outtextxy(x,y+240,"get stuck for a while when a resource has got ");
	outtextxy(x,y+270,"depleted from which recovery is difficult. Secondly  ");
	outtextxy(x,y+300,"the player should also take care of the ");
	outtextxy(x,y+330,"ecosystem ,which if he misses to take care the ");
	outtextxy(x,y+360,"player will loose the city altogether. Furthermore ");
	outtextxy(x,y+390,"the land is prone to disasters!!! Yes that is right. ");
	getch();

	cleardevice();
	rectangle(5,5,635,475);
	rectangle(10,10,630,470);
	outtextxy(x,y,"The player also has to save his city from disasters");
	outtextxy(x,y+30,"for which the player has to build a wall enclosing");
	outtextxy(x,y+60,"the city and protecting it from disasters.");
	getch();
}

// to draw thick lines
void drawtline(int x1, int y1, int x2, int y2, int t)
{
	int poly[8];
	if (y1 == y2)
	{
		poly[0] = x1;
		poly[1] = y1 - t/2;
		poly[2] = x2;
		poly[3] = y2 - t/2;
		poly[4] = x2;
		poly[5] = y2 + t/2;
		poly[6] = x1;
		poly[7] = y1 + t/2;
	}
	else
	{
		poly[0] = x1 - t/2;
		poly[1] = y1;
		poly[2] = x2 - t/2;
		poly[3] = y2;
		poly[4] = x2 + t/2;
		poly[5] = y2;
		poly[6] = x1 + t/2;
		poly[7] = y1;

	}
	fillpoly(4,poly);
}


//Thick line 
void drawthickline ( int x1 , int y1 , int x2 , int y2 , int t )
{
	for ( int i = 1 ; i <= t ; i++ )
	{ if ( y1 == y2 )
		{
			line ( x1 , y1 + i , x2 , y2 + i ) ;
		}
		else
		{
			line ( x1 + i , y1 , x2 + i , y2 ) ;
		}
	}
}

//Atlantis logo
void drawAtlantis ()
{
	int spd = 0 , ra ;
	int acc = 0;
	for ( int x = -600 ; x <= 800 ; x += spd )
	{
		cleardevice () ;
		setcolor ( CYAN ) ;
		settextstyle ( 4 , HORIZ_DIR , 12 ) ;
		for ( int u = 0 ; u < 4 ; u++ )
			outtextxy ( u + 100 , u + 125 , "Atlantis" ) ;
		ra = 0 + random (getmaxx()) ;

		if ( x>= 0) x =0;

		setcolor ( WHITE ) ;
		drawthickline ( 60 + x , 220 ,560 + x , 220 , 5 ) ;
		arc ( 55 + x , 518 , 80 , 100 , 300 ) ;
		arc ( 53 + x , -72 , 260 , 280 , 300 ) ;
		setfillstyle ( SOLID_FILL , WHITE ) ;
		floodfill ( 52 + x , 223 , WHITE ) ;
		arc ( 575 + x , 517 , 80 , 100 , 300 ) ;
		arc ( 573 + x , -72 , 260 , 281 , 300 ) ;
		floodfill ( 575 + x , 223 , WHITE ) ;
		arc ( 585 + x , 243 , 120 , 160 , 60 ) ;
		arc ( 583 + x , 243 , 120 , 160 , 52 ) ;
		arc ( 587 + x , 208 , 194 , 235 , 60 ) ;
		arc ( 586 + x , 208 , 194 , 235 , 52 ) ;
		line ( 555 + x , 191 , 620 + x , 205 ) ;
		line ( 556 + x , 198 , 620 + x , 205 ) ;
		line ( 554 + x , 257 , 620 + x , 243 ) ;
		line ( 556 + x , 249 , 620 + x , 243 ) ;
		floodfill ( 554 + x , 195 , WHITE ) ;
		floodfill ( 554 + x , 253 , WHITE ) ;

		for ( int x1 = 0 ; x1 <= 150 ; x1 += 150 )
		{ //cleardevice () ;
			drawtline ( ra , x1 + 0 , ra - 30 , x1 + 100 , 5 ) ;  // 190
			drawtline ( ra , x1 + 75 , ra - 30 , x1 + 100 , 5 ) ;
			setfillstyle ( SOLID_FILL , WHITE ) ;
			int polygon [] = { ra , x1 + 75 , ra + 5 , x1 + 75 , ra - 38 , x1 + 250 , ra , x1 + 75 } ;
			fillpoly ( 3 , polygon ) ;
			delay (80) ;
		}



		spd += acc;
		acc += 5;
		//delay ( 40 ) ;
		if ( x >= 0 )
			break;
	}
	//delay (2000);
}


// copies string to another string variable for given number
void string_copy(char* strDest, char*strSrc, int n)
{
	for (int i = 0; i <= n && strSrc[i]; i++)
		strDest[i] = strSrc[i];
	strDest[i] = '\0';
}

void eraseLastChar(char* strSrc)
{
	if (strlen(strSrc) > 0) strSrc[strlen(strSrc) - 1] = 0;
}

void tune(double a, int b)
{
	sound(a);
	delay(b);
	nosound();
}

void displayPara(int style, int x, int y, char credits[][80], char *cursor,int n, int delaySpd)
{

	char text[80];
	char print[80];
	switch(style)
	{
		case 0: // like a typewriter uses clearscreen so beware
			for (int i = 0; i <= n-1; i++ )
			{
				strcpy(text, credits[i]);

				for (int j = 0; j <= strlen(text); j++)
				{
					delay(delaySpd);
					cleardevice();
					string_copy(print, text, j);
					moveto(x,y);
					outtext(print);
					outtext(cursor);
				}
			}
			break;
	}

}

void drawellipse(int x, int y, int xrad, int yrad , double angle)
{

	angle = toRadians(angle);
	double arcangle = toDegrees(angle);
	int c1_x = x + xrad * cos(angle), c1_y = y - xrad * sin(angle), c2_x = x - xrad * cos(angle), c2_y = y + yrad * sin(angle);
	arc (c1_x, c1_y, 270 + arcangle, 90 + arcangle, yrad);
	arc (c2_x, c2_y, 90 + arcangle, 270 + arcangle, yrad);
	int base1_x1 = c1_x + yrad * sin(angle), base1_y1 = c1_y + yrad * cos(angle);
	int base1_x2 = c2_x + yrad * sin(angle), base1_y2 = c2_y + yrad * cos(angle);
	int base2_x1 = c1_x - yrad * sin(angle), base2_y1 = c1_y - yrad * cos(angle);
	int base2_x2 = c2_x - yrad * sin(angle), base2_y2 = c2_y - yrad * cos(angle);
	line (base1_x2,base1_y2, base1_x1, base1_y1);
	line (base2_x2,base2_y2, base2_x1, base2_y1);
}

double toRadians(double deg)
{
	return (deg/180 * PI);
}

double toDegrees(double rad)
{
	return (rad * 180 / PI);
}


char *formatString(int type, char string[])
{
	int i;

	for (i = 0; i < strlen(string); i++)
		if ( type == 0 && (!i || string[i-1] == ' ' || string[i-1] == '.')) // Title Case
			string[i] = toupper(string[i]);
		else if (type == 1) // UPPER CASE
			string[i] = toupper(string[i]);
		else if (type == 2) // 	LOWER CASE
			string[i] = tolower(string[i]);
	return string;
}

void tcircle ( int x , int y , int r , int t )
{ for ( int i = 0 ; i < t ; i++ , r-- )
	circle ( x , y , r ) ;
}

int stringSearch(char list[20][15], char *str)
{
	for (int i = 0; i < 20; i++)
		if (strcmp(list[i], str) == 0)
			return 1;

	return 0;
}

void outtextcenter(int y, char *t)
{
	outtextxy(getmaxx()/2 - textwidth(t)/2, y, t);
}

void strSplit(char *src, char dest[][20], char symbol)
{
	int i = 0, j = 0;
	for (; *src; src++)
	{
		if (*src == symbol)
		{
			dest[i][j] = 0;
			i++;
			j = 0;
		}
		else
			dest[i][j++] = *src;
	}
	dest[i][j] = 0; // closing the last string
}

#endif
