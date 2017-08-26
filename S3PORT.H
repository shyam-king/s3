//s3 portable
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<dos.h>
#include<graphics.h>
#include<conio.h>
#include<iostream.h>
#include<math.h>

//S3 tools (helper functions and some intro functions too)
#ifndef S3PORT_H
#define S3PORT_H


/////////////////////////GLOBAL VARIABLES////////////////////////

const long double PI = 3.1415926535;


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
char *inttochar(int);
void drawtarc(int, int, int, int, int, int);
void initmouse();
void mousereset();
void mousestatus();
void drawtline(int, int, int, int, int);
void drawAtlantis () ;
void drawthickline ( int , int , int , int , int ) ;
char keyboardInput(char);
void string_copy(char*, char*, int);
void eraseLastChar(char*);
void tune(double, int);
void displayPara(int style, int x, int y, char **credits, char *cursor,int n, int delaySpd);
double toRadians(double deg);
double toDegrees(double rad);
void drawellipse(int x, int y, int xrad, int yrad, double angle);
char *formatString(int type, char string[]);
void fillCircle(int x, int y, int r, int color, int patt);

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
			 int spd = 0;
			 int acc = 5;
			for ( int x = -600 ; x <= 800 ; x += spd )
			{
				if ( x>= 0) x =0;
				 cleardevice () ;
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
				 setcolor ( CYAN ) ;
				 settextstyle ( 4 , HORIZ_DIR , 12 ) ;
				 outtextxy ( 100 , 125 , "Atlantis" ) ;
				 setbkcolor ( BLACK ) ;
				 spd += acc;
				 acc += 10;
				 delay ( 90 ) ;
				 if ( x >= 0 )
					break;
			}
	     delay (3000);
		 }


// copies string to another string variable for given number
void string_copy(char* strDest, char*strSrc, int n)
{
 for (int i = 0; i <= n; i++)
 strDest[i] = strSrc[i];
 strDest[i] = '\0';
}

void eraseLastChar(char* strSrc)
{
	char *strNew; 
	string_copy(strNew, strSrc, strlen(strSrc) - 2);
	sprintf(strSrc, "%s", strNew);
}

void tune(double a, int b)
{
 sound(a);
 delay(b);
 nosound();
}

void displayPara(int style, int x, int y, char **credits, char *cursor,int n, int delaySpd)
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
					string_copy(print, text, j);
					moveto(x,y);
					outtext(print);
					outtext(cursor);

					delay(delaySpd);
					cleardevice();
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

void fillCircle(int x, int y, int r, int color, int patt)
{
	int t = 0; 
	for (long i = x - r ; i <= x + r; i+= 1)
		for (long j = y - r; j <= y+r; j+= 1)
		{
			if ((i-x) * (i-x) + (j-y) *(j-y) <= (long)r * r && !t)
				putpixel(i,j,color);
			t--;
			if ( t == -patt) t *= -1;
		}
}

#endif