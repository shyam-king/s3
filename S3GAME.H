/////////////////Game data and functions
#include"S3TOOLS.H"
#include<ctype.h>
#include<string.h>
#include<fstream.h>

#ifndef S3GAME_H
#define S3GAME_H


// macros
#define MAX(x,y) (x>y)? x:y

#define DOWN_RIGHT 0
#define DOWN_LEFT 3
#define UP_RIGHT 1
#define UP_LEFT 2

///prototypes
/*
	class Road;
	class House;
	class customPalette;
	class goals;
	class Well;
	*/
///definitions

///////////////GLOBAL VARIABLES////////////////////////
int originX = 0, originY = +1000; // will be used for dragging
int terrW = 3000, terrH = 3000; // terrain size
int gameLoop = 0; // Loop controlling the game play
int animate = 1; // to prevent the ugly 'blinking' effect
int dragging = 0;
int dragx = 0, dragy = 0;
int mx, my, mc, mmx = 0, mmy = 0, mmc = 1; // Mouse control


// these stuff will be displayed in the scree using the drawDetails()
int showDetail = 0;
int detailCount = 0;
char detailObject[20] = "";
char detailObjType[20] = "";
int ecoMeter = 100;
long int population = 50;

// flags
int interact = 1;
int messageDisplay = 0;
int movemodeend = 0;

enum EDITMODES{VIEW_MODE, CREATE_MODE, REMOVE_MODE, SCRAMBLE_MODE, MOVE_MODE};
EDITMODES EDITMODE = VIEW_MODE;

//goal stuff
int goaldisplayed = 0;
int treeCount = 0;
int liveTreeCount = 0;
int houseCount =0 , liveHouseCount = 0;
int boatIncome = 0;
int miniMessageDisplay, miniMessageTimer;
char miniMessage[80], miniColorBack, miniColorBorder, miniColorFont;

//menu stuff
int menudisplay = 0;

// map_details
int nhouses = 8;
int ntrees = 15;
int treeCutCount = 0;
int houseBuiltCount;

// puzzle list
char  rlist[20][15]={"POSIEDON","ZEUS","HADES","APHRODITE","ATHENA","HEPHAESTUS","DIONISUS","APOLLO","ARTEMIS","ARES","HERMES","HERA","GAIA","KRONOS","ORANOUS","ATLAS","CHAOS","LOKI","THOR","ODIN"};
char  clist[20][15]={"POSIEDON","ZEUS","HADES","APHRODITE","ATHENA","HEPHAESTUS","DIONISUS","APOLLO","ARTEMIS","ARES","HERMES","HERA","GAIA","KRONOS","ORANOUS","ATLAS","CHAOS","LOKI","THOR","ODIN"};

//troubleshooting purposes
char tsstr[80] = "Troubleshooting test";
int tsval=0;

////////////////GRAPHIC PATTERNS/////////////////////////
int linePattern[] = {1,0};
char fillPattern_honeycomb[] = {0x18, 0x18, 0x24, 0xc3, 0xc3, 0x24, 0x18, 0x18}; // honey comb

///////////////CLASSES///////////////////////////////
// class Road
class Road{      // will be used for the buildRoad function
	//starting positions
	int x;
	int y;

	int size;
	int n; // number of road segments // to faciliate drawing

	int dir; // direction of building // UP_RIGHT OR DOWN_RIGHT

	int stripeFill, stripeColor, fill, color;

	int borderFill, stripeBorderFill;

	public:

	void setProperties(int xx, int yy, int s, int nn, int d, int stf, int stc, int f, int c, int bf, int sbf)
	{
		x = xx;
		y = yy;

		size = s;
		n = nn;

		dir = d;

		stripeFill = stf;
		stripeColor = stc;

		fill = f;
		color = c;

		borderFill = bf;

		stripeBorderFill - sbf;
	}

	void draw(int origx, int origy, int i, int stripeFlag = 1);
	void build(int origx, int origy);


};

void Road::draw(int origx, int origy, int i, int stripeFlag)
{
	int h, w;
	h = w= size;
	int upat = 0;

	//DIRECTION: 0 - RIGHT/LEFT  1 - UP/DOWN

	int poly_stripe[8];

	switch(dir)
	{
		case DOWN_RIGHT:
			origx += (size/2)*i;
			origy += (size/2)*i;
			poly_stripe[0] = origx + x - w/10;
			poly_stripe[1] = origy +y - h/6;
			poly_stripe[2] = origx +x - w/6;
			poly_stripe[3] = origy +y - h/10;
			poly_stripe[4] = origx +x + w/10;
			poly_stripe[5] = origy +y + h/6;
			poly_stripe[6] = origx +x + w/6;
			poly_stripe[7] = origy +y + h/10;
			break;
		case UP_LEFT:
			origx -= (size/2)*i;
			origy -= (size/2)*i;
			poly_stripe[0] = origx + x - w/10;
			poly_stripe[1] = origy +y - h/6;
			poly_stripe[2] = origx +x - w/6;
			poly_stripe[3] = origy +y - h/10;
			poly_stripe[4] = origx +x + w/10;
			poly_stripe[5] = origy +y + h/6;
			poly_stripe[6] = origx +x + w/6;
			poly_stripe[7] = origy +y + h/10;
			break;
		case UP_RIGHT:
			origx += (size/2)*i;
			origy -= (size/2)*i;
			poly_stripe[0] = origx +x + w/10;
			poly_stripe[1] = origy + y - h/6;
			poly_stripe[2] = origx +x + w/6;
			poly_stripe[3] = origy + y - h/10;
			poly_stripe[4] = origx +x - w/10;
			poly_stripe[5] = origy + y + h/6;
			poly_stripe[6] = origx +x - w/6;
			poly_stripe[7] = origy + y + h/10;
			break;
		case DOWN_LEFT:
			origx -= (size/2)*i;
			origy += (size/2)*i;
			poly_stripe[0] = origx +x + w/10;
			poly_stripe[1] = origy + y - h/6;
			poly_stripe[2] = origx +x + w/6;
			poly_stripe[3] = origy + y - h/10;
			poly_stripe[4] = origx +x - w/10;
			poly_stripe[5] = origy + y + h/6;
			poly_stripe[6] = origx +x - w/6;
			poly_stripe[7] = origy + y + h/10;
			break;
	}

	int poly[] = {origx + x ,origy +  y - h/2,origx +  x - w/2,origy +  y,origx +  x,origy +  y+h/2,origx +  x + w/2,origy +  y};
	setlinestyle (borderFill, upat, 1);
	setfillstyle(fill,color);
	setcolor(getbkcolor());
	fillpoly(4,poly);


	setfillstyle(stripeFill,stripeColor);
	setcolor(color);
	if (stripeFill == EMPTY_FILL)
		setlinestyle(USERBIT_LINE, upat, 1);
	else
		setlinestyle(stripeBorderFill, upat, 1);

	if (!stripeFlag) fillpoly(4, poly_stripe);


	setlinestyle(SOLID_LINE, upat, 1);
}

void Road::build(int origx, int origy)
{
	int i;
	for (i = 0; i < n; i++)
		draw(origx, origy, i, (!i || i == n-1));
}

class PLAYER
{
	int currXp;
	int id;
	int playerLevel;
	int userIcon[10][10];
	char userName[80];
	unsigned long money,wood,produce,water;
	int maxXp;
	int index;
	public:
	PLAYER ()
	{
		maxXp=100;
		currXp=0;
		playerLevel=1;
		strcpy(userName,"\0");
		money=6000;
		wood=700;
		water=0;
		produce=0;
	}
	//Accesor functions
	int getplayerLevel()
	{
		return playerLevel;
	}
	int getmaxXp()
	{
		return maxXp;
	}
	int getcurrXp()
	{
		return currXp;
	}
	unsigned long getmoney()
	{
		return money;
	}
	unsigned long getwater()
	{
		return water;
	}
	unsigned long getproduce()
	{
		return produce;
	}
	unsigned long getwood()
	{
		return wood;
	}
	char * getuserName()
	{
		return userName;
	}
	//Setters
	void setmoney(int a)
	{
		money=a;
	}
	void setwood(int a)
	{
		wood=a;
	}
	void setproduce(int a)
	{
		produce=a;
	}
	void setwater(int a)
	{
		water=a;
	}
	void setcurrXp(int a)
	{
		currXp+=a;
		if(currXp>maxXp)
		{
			playerLevel++;
			currXp=0;
			maxXp=playerLevel*100;
			animate=1;
		}
	}
	void accept();
	void drawIcon();
	void setid(int i)
	{
		id  = i;
	}

	int show_ID();


}player;

int PLAYER::show_ID()
{
	return id;
}

void PLAYER::drawIcon()
{
	int i,j;
	int poly[8];
	setlinestyle(USERBIT_LINE, 0, 1);
	for (i =0 ;i < 10; i++)
		for (j =0; j < 10; j++)
		{


			setfillstyle(SOLID_FILL, userIcon[i][j]);

			poly[0] = poly[2] = j * 5;
			poly[1] =poly[7] = getmaxy() - 100 + i * 5;
			poly[3] = poly[5] = getmaxy() - 100 + i * 5 + 5;
			poly[4] =poly[6]= j*5 + 5;

			fillpoly(4, poly);

		}
}

//class Tree

class Tree;

class Tree{
	int x,y;
	char cutdown;
	unsigned int recover;

	public:

	Tree()
	{
		cutdown = 0;
	}

	Tree(int a, int b)
	{
		x = a;
		y = b;
	}

	void setPositions(int a, int b)
	{
		x = a;
		y = b;
	}

	void draw(int , int);
	void interact( int n);
	int getx();
	int gety();
	int getCutStatus();
	void setCutStatus(int);
} map_trees[20];

void Tree::draw(int ox, int oy)
{
	int xx = ox + x, yy = oy + y;
	if (!cutdown && xx >= 0 && xx <= SCREEN_W && yy >= 0 && yy <= SCREEN_H)
	{
		int a = xx, b = yy;
		a -= 300;
		b -= 450;

		setcolor ( BROWN ) ;
		setfillstyle ( SOLID_FILL , BROWN ) ;
		drawtline ( a + 300 , b + 300 ,  a + 300 , b + 450 , 25 ) ;
		setfillstyle ( SOLID_FILL , BLACK ) ;
		ellipse ( a + 300 , b + 375 , 0 , 360 , 10 , 25 ) ;
		fillellipse ( a + 300 , b + 375 , 10 , 25 ) ;
		ellipse ( a + 300 , b + 375 , 0 , 360 , 8 , 20 ) ;
		fillellipse ( a + 300 , b + 375 , 8 , 20 ) ;
		ellipse ( a + 300 , b + 375 , 0 , 360 , 6 , 15 ) ;
		fillellipse ( a + 300 , b + 375 , 6 ,15 ) ;
		ellipse ( a + 300 , b + 375 , 0 , 360 , 4 , 10 ) ;
		fillellipse ( a + 300 , b + 375 , 4 , 10 ) ;
		setcolor ( BLACK ) ;
		setlinestyle ( SOLID_LINE , 1 , 2 ) ;
		line ( a + 310 , b + 310 , a + 310 , b + 350 ) ;
		line ( a + 310 , b + 390 , a + 310 , b + 430 ) ;
		line ( a + 290 , b + 400 , a + 290 , b + 440 ) ;
		line ( a + 290 , b + 310 , a + 290 , b + 350 ) ;
		line ( a + 300 , b + 310 , a + 300 , b + 330 ) ;
		line ( a + 300 , b + 420 , a + 300 , b + 430 ) ;

		a = xx; b = yy;

		a -= 300;
		b -= 450;
		setcolor ( LIGHTGREEN ) ;
		setfillstyle ( 9 , LIGHTGREEN ) ;
		//setfillpattern(fillPattern_honey, LIGHTGREEN);
		arc ( a + 225 , b + 295 , 130 , 310 , 25 ) ;
		arc ( a + 385 , b + 285 , 235 , 85 , 40 ) ;
		arc ( a + 210 , b + 250 , 70 , 270 , 30 ) ;
		arc ( a + 300 , b + 270 , 215 , 325 , 80 ) ;
		arc ( a + 360 , b + 210 , 305 , 150 , 50 ) ;
		arc ( a + 260 , b + 180 , 355 , 230 , 60 ) ;
		floodfill ( a + 300 , b + 300 , LIGHTGREEN ) ;
		floodfill ( a + 300 + 50, b + 300 , LIGHTGREEN ) ;
		floodfill ( a + 300 - 50, b + 300 , LIGHTGREEN ) ;
	}
	xx -= 30;
	yy -= 100;
	int color = LIGHTGREEN;
	setcolor ( color ) ;
	setfillstyle ( SOLID_FILL , color ) ;
	int poly [] = { xx + 20 , yy + 100 , xx + 15 , yy + 95 , xx + 10 , yy + 85 ,  xx + 20 , yy + 90 , xx + 20 , yy + 80 , xx + 25 , yy + 90 , xx + 30 , yy + 75 , xx + 35 , yy + 90 , xx + 40 , yy + 80 , xx + 40 , yy + 90 , xx + 50 , yy + 85 , xx + 45 , yy + 95 , xx + 40 , yy + 100 } ;
	fillpoly ( 13 , poly ) ;
}


int Tree::getx()
{
	return x;
}

int Tree::gety()
{
	return y;
}

int Tree::getCutStatus()
{
	return cutdown;
}

void Tree::setCutStatus(int c)
{
	cutdown = c;
}

struct customPalette{
	int r[16], g[16], b[16];
};

class House{
	int x,y,direction;
	int c,woc, goc, wic, pic, gic, wfill, pfill, gfill; // for plotter function
	int color1 ; int color2 ; int color3; // for drawHouse function

	int level;
	char name[20];
	int population;
	int timer, timerFlag,  timerMax;
	int rentToCollect, rentTimer;
	public:
	House()
	{}
	House (int a, int b, int C, int d, int e, int f, int g, int h, int i, int j, int k, int l, int m, int n, int o, int p, char * q, int r, int s, int t, int u, int v, int w )
	{
		x=a;y=b;direction=C;
		c=d;woc=e; goc=f; wic=g; pic=h; gic=i; wfill=j; pfill=k; gfill=l; // for plotter function
		color1=m ; color2=n ; color3=o ; // for drawHouse function

		level=p;
		strcpy(name,q);
		population=r;
		timer=s; timerFlag=t;  timerMax=u;
		rentToCollect=v; rentTimer=w;
	}
	int & rlevel()
	{
		return level;
	}
	int & rpopulation ()
	{
		return population;
	}
	void drawHouse ( int  , int  , int  , int  , int  , int  );
	void buildHouse(House &houses); // full house, all floors with roof and 'wall'
	void houseInteract(House *houses, int n, char); // to select a house

}obj;

House *MovingHouse = NULL;

class Well{
	int x, y, regenerateTimer, waterToCollect, canCollect, maxTimer;
	public:
	Well ()
	{
		x=-400;
		y=700;
		regenerateTimer=0;
		waterToCollect=25;
		canCollect=0;
		maxTimer=1000;
	}
	void wellInteract();
	int access(int wellaccess)
	{
		if (wellaccess==1)
			return x;
		else if(wellaccess==2)
			return y;
		return canCollect;
	}
	void drawWell(int , int , int );
}well;
// the well object is used to control the game well

class Boat
{
	int boatUsing, boatTimer, boatTimerMax, boat_xx, boat_yy;


	public:
	int boatAnimate, boat_x;
	int boat_y;

	Boat();

	void drawBoat(int x, int y);
	void boatInteract();
	void check();
} boat;
//the boat object is used for calling the functions elsewhere

class Industry

{
	public :
		int industryIncome , industry_x ,industry_y ;
		void industryInteract () ;
		void drawIndustry ( int x , int y , int color1 , int color2 , int color3 ) ;
		Industry ()
		{
			industry_x = - 500;
			industry_y = - 500;
			industryIncome = 0;
		}
} industry ;
class Puzzle
{
	char list [15];
	int index, locked;
	char  currscramble[15] ;
	int selection , choice , scselection ;
	char completedList[20][15];
	public:
	Puzzle();
	void drawPuzzleScreen();
	int limit;
	int sflag;
	int completed;

	void add(char letter)
	{
		int t =strlen(list);
		list[t] = letter;
		list[t+1]='\0';
	}

	void appendList();
	void puzzleInteract(char);



	void setIndex()
	{
		index = random(limit);
	}
	char pop();

} puzzle ;

char Puzzle::pop ()
{
	int x = index;
	int y = random(strlen(clist[x]));
	char t=clist[x][y];
	for(int i=y;i<strlen(clist[x]);i++)
		clist[x][i]=clist[x][i+1];
	return t;
}

#include"s3goalc.h"


///////////////FUNCTION PROTOTYPES/////////////////////

//drawing functions
void drawTerrain();
void drawDetails(); // user details
void plotter(int,int,int, int, int, int, int, int, int, int ,int , int); // the plot (empty) which is also used as roof
int scrollAnimation(int, int); // the scroll
void drawlake(int x,int y); // the big lake
void drawTrunk (int x, int y); // trunk of a tree
void drawbush ( int x , int y , int color ); // bush below the tree
void drawtreebush ( int x , int y ); // bush above the tree
void plotTree(Tree); // the whole tree
void messagebox(char message[][80] , int color, int n, int image_index);
int displayMenu();
void drawBarHoriz(int x, int y, int w, int h, int color0, int color1, float percent);
void drawBarVer(int x, int y, int w, int h, int color0, int color1, float percent);
void outtextVer(int x, int y, char m[]);
void showMiniBox();
void changePalette(customPalette);

//drawing icon functions
void drawMoneyIcon(int x, int y, int xscale, int yscale); // draw the coin
void drawWoodIcon(int x, int y, int xscale, int yscale); // draw the wood (log like) icon
void drawMenuIcon(int x, int y, int xscale, int yscale);
void drawCreateIcon(int x, int y, int xscale, int yscale);
void drawHelpIcon(int x, int y, int xscale, int yscale);
void drawGoalIcon(int x, int y, int xscale, int yscale);
void drawRemoveIcon(int x, int y, int xscale, int yscale);
void drawBackIcon(int x, int y, int xscale, int yscale);
void drawProduceIcon(int x, int y, int xscale, int yscale);
void drawDropIcon(int x, int y, int xscale, int yscale);
void drawScrambleIcon(int, int ,int, int);
void drawMoveIcon(int x, int y, int xscale, int yscale);


//game management fucntions
void goals_display();
void gameReset();
void setMiniBox(char  text[], int colorBorder , int colorIn , int fontColor );
void gameNew(); // when the user starts a new game
void drag(char); // to drag around the terrain
void setDetailDisplay (char a[], char b[]);
void gamesave();
void gameload();

//interact

void treeInteract(Tree*, int); // selecting a tree


// troubleshooting functions
void tsprint();


////////////////GAME MAP//////

Road mainRoad[4];

House map_houses[20] = {
	House(
			0 - 150, -3000/2 + 100 + 150, DOWN_LEFT,
			150,BROWN,WHITE,DARKGRAY,BROWN,WHITE,SOLID_FILL,SLASH_FILL,SLASH_FILL,
			MAGENTA , LIGHTGRAY , BROWN,
			0,
			"Residence",
			0,
			0,0,0
			,0,0
		  ),

	House(
			180- 150, -3000/2 + 280+ 150, DOWN_LEFT,
			150,BROWN,WHITE,DARKGRAY,BROWN,WHITE,SOLID_FILL,SLASH_FILL,SLASH_FILL,
			YELLOW , LIGHTGRAY , BROWN,
			0,
			"Residence",
			0,
			0,0,0
			,0,0
		  ),

	House(
			360- 150, -3000/2 + 100 + 360+ 150, DOWN_LEFT,
			150,BROWN,WHITE,DARKGRAY,BROWN,WHITE,SOLID_FILL,SLASH_FILL,SLASH_FILL,
			RED , LIGHTGRAY , BROWN,
			0,
			"Residence",
			0,
			0,0,0
			,0,0
		  ),

	House(
			540- 150, -3000/2 + 100 +540+ 150, DOWN_LEFT,
			150,BROWN,WHITE,DARKGRAY,BROWN,WHITE,SOLID_FILL,SLASH_FILL,SLASH_FILL,
			MAGENTA , LIGHTGRAY , BROWN,
			0,
			"Residence",
			0,
			0,0,0
			,0,0
		  ),

	House(
			720- 150, -3000/2 + 100 + 150+720, DOWN_LEFT,
			150,BROWN,WHITE,DARKGRAY,BROWN,WHITE,SOLID_FILL,SLASH_FILL,SLASH_FILL,
			BROWN , LIGHTGRAY , BROWN,
			0,
			"Residence",
			0,
			0,0,0
			,0,0
		  ),
	House(
			900- 150, -3000/2+900+100+ 150, DOWN_LEFT,
			150,BROWN,WHITE,DARKGRAY,BROWN,WHITE,SOLID_FILL,SLASH_FILL,SLASH_FILL,
			BROWN , LIGHTGRAY , BROWN,
			0,
			"Residence",
			0,
			0,0,0
			,0,0
		  ),
	House(
			1080- 150, -3000/2+1080+ 150+100, DOWN_LEFT,
			150,BROWN,WHITE,DARKGRAY,BROWN,WHITE,SOLID_FILL,SLASH_FILL,SLASH_FILL,
			BROWN , LIGHTGRAY , BROWN,
			0,
			"Residence",
			0,
			0,0,0
			,0,0
		  )
		,
	House(
			1260- 150, -3000/2+1260+100+ 150, DOWN_LEFT,
			150,BROWN,WHITE,DARKGRAY,BROWN,WHITE,SOLID_FILL,SLASH_FILL,SLASH_FILL,
			BROWN , LIGHTGRAY , BROWN,
			0,
			"Residence",
			0,
			0,0,0
			,0,0
		  )
};

///////////////FUNCTION DEFINITIONS////////////////////

void House::houseInteract(House *houses, int n, char k)
{
	House h;
	static int x, y;

	population = 0;

	for  (int i = 0; i < n; i++)
	{
		h = houses[i];
		if (mx  >= originX+houses[i].x -  95&& mx <= originX+houses[i].x + 95&& my >= houses[i].y+originY - 95 && my <= houses[i].y +originY+ 95)
		{
			if(mc == 1 && mmc != 1 && EDITMODE == VIEW_MODE)
			{
				(houses[i].level > 0)?setDetailDisplay("House", houses[i].name):setDetailDisplay("Plot", houses[i].name);
			}
			else if (mc == 1 && mmc != 1 && EDITMODE == MOVE_MODE)
			{
				if (MovingHouse == NULL)
				{
					MovingHouse = houses + i;
					x = originX;
					y = originY;
				}
			}
			else if (mc == 1 && mmc !=1 && EDITMODE == CREATE_MODE)
			{

				if ( player.getmoney()  >=  500 * (houses[i].level + 3)  && player.getwood() >= 250 * (houses[i].level + 1) && player.getplayerLevel() > houses[i].level && !houses[i].timerFlag && ((houses[i].level) ? houses[i].rentTimer: 1))
				{
					animate = 1;

					houses[i].timer = 200 * (houses[i].level + 1);
					houses[i].timerFlag = 1;
					houses[i].timerMax = 200 * (houses[i].level + 1);

					player.setmoney(player.getmoney() - 500 * (houses[i].level +3));

					char t[80];
					sprintf(t, "%d Gems and %d Resources have been spent!", 500 * (houses[i].level +3), 250 * (houses[i].level + 1) );
					setMiniBox(t, LIGHTGRAY, BLUE, WHITE);

					player.setwood(player.getwood()-250 * (houses[i].level + 1));
					animate = 1;
				}
				else if (player.getmoney() < 500 * (houses[i].level + 3) && !houses[i].timerFlag && ((houses[i].level) ? houses[i].rentTimer: 1) && player.getplayerLevel() > houses[i].level)
				{
					setMiniBox("Not enough money to build house!", WHITE, RED, WHITE);
				}
				else if (player.getwood() < 250 * (houses[i].level + 1) && !houses[i].timerFlag && ((houses[i].level) ? houses[i].rentTimer: 1)&&player.getplayerLevel() > houses[i].level)
				{
					setMiniBox("Not enough resources to build house!", WHITE, RED, WHITE);
				}
				else if (!houses[i].timerFlag && ((houses[i].level) ? houses[i].rentTimer: 1)&& player.getplayerLevel() <= houses[i].level)
				{
					setMiniBox("Need to level up...",WHITE, RED, WHITE);
				}
				else if (houses[i].rentTimer == 0 && houses[i].level)
				{
					player.setmoney(player.getmoney() + houses[i].rentToCollect);
					houses[i].rentTimer = 1000 * houses[i].level;
					animate = 1;
				}

			}
		}

		if (houses[i].timerFlag)
		{
			if (houses[i].timer)
			{
				drawBarHoriz(houses[i].x + originX - 50, houses[i].y + originY + -3, 100, 8, WHITE, BLUE, (float)(houses[i].timerMax - houses[i].timer)/houses[i].timerMax * 100);
				houses[i].timer --;
			}
			else
			{
				animate = 1;
				houses[i].timerFlag = 0;
				houses[i].level ++;
				houses[i].population += 2 + random(5);
				houses[i].rentTimer = houses[i].level * 300;
				houses[i].rentToCollect = houses[i].level * 30;

				if (houses[i].level == 1) houseBuiltCount ++;

				player.setcurrXp(10);
			}
		}

		if (houses[i].level)
		{
			if (houses[i].rentTimer)
			{
				houses[i].rentTimer --;
			}
			else
			{

				// pickup icon
				setcolor(WHITE);
				setlinestyle(SOLID_LINE,0,1);
				circle(originX + houses[i].x , originY + houses[i].y, 60);
				drawMoneyIcon(originX + houses[i].x - 55,  originY+ houses[i].y - 50 , 3,3);
			}
		}
		if (MovingHouse == houses + i && EDITMODE == MOVE_MODE)
		{
			houses[i].x -= originX - x;
			houses[i].y -= originY - y;
			x = originX;
			y = originY;
			if (tolower(k) == 'r')
			{
				houses[i].direction = (houses[i].direction == DOWN_LEFT)? DOWN_RIGHT: DOWN_LEFT;	
				animate = 1;
			}
			if (movemodeend)
			{
				movemodeend = 0;
				int f = 1;
				if (houses[i].x >= industry.industry_x - 150 && houses[i].x <= industry.industry_x + 150 && houses[i].y >= industry.industry_y - 150 && houses[i].y <= industry.industry_y + 150)
				{
					setMiniBox("Cannot place the house within Industry! You fool!", WHITE, RED, WHITE);
					f = 0;
				}
				else 
				{
					for (int j = 0; j <n ; j++ )
					{
						if (i != j)
							if (houses[i].x >= houses[j].x - 150 && houses[i].x <= houses[j].x + 150 && houses[i].y >= houses[j].y - 150  && houses[i].y <= houses[j].y + 150)
							{
								f = 0;
								setMiniBox("Do you want to destroy the house, or what? Idiot.", WHITE, RED, WHITE);
								break;
							}
					}
					if (f)
					{
						for (int k = 0; k < ntrees; k++)
							if (map_trees[k].getx() >= houses[i].x - 150 && map_trees[k].getx() <= houses[i].x + 150 && map_trees[k].gety() >= houses[i].y - 150 && map_trees[k].gety() <= houses[i].y + 150)
							{
								f = 0;
								setMiniBox("That\'s a tree, you bufoon!", WHITE, RED, WHITE);
								break;
							}
					}
					if (f)
					{
						if (houses[i].x <= 530 && houses[i].x >=  -220 && houses[i].y <= 680 && houses[i].y >= -70)
						{
							f = 0;
							setMiniBox("Houses don\'t float! Go learn some Physics first.", WHITE, RED, WHITE);
						}
					}
				}
				if (f)
				{
					EDITMODE = VIEW_MODE;
					animate = 1;
				}
			}

			sprintf(tsstr, "%d %d", houses[i].x, houses[i].y);


		}
		population += houses[i].population;
	}

	population += 50; // from industry
}

void PLAYER::accept()
{
	char edit[80];
	char k=0;
	// SCROLLING ANIMATION

	int h, f = 1;
	h = scrollAnimation(0, 0);
	mousereset();
	initmouse();
	while (k!= '\n' && k != '\r')
	{
		k = keyboardInput(NOKEY);
		strcpy(edit, userName);
		if (k != NOKEY || f)
		{
			cleardevice();
			scrollAnimation(1,h);

			if (k == '\b' )
			{
				if (strlen(userName) > 0)
					eraseLastChar(userName);
				//else
				//strcpy(userName, "");
			}
			else
				if (k != NOKEY) sprintf(userName, "%s%c", edit,k);


			settextstyle(7, HORIZ_DIR, 3);
			setcolor(WHITE);
			outtextxy(200,SCREEN_H/2 - 100, "ENTER YOUR NAME:");
			setcolor(LIGHTMAGENTA);
			settextstyle(7, HORIZ_DIR, 2);

			moveto(SCREEN_W/2 - textwidth(userName)/2,SCREEN_H/2);
			outtext(userName);
			outtext("_");

			f = 0;
			delay(150);
		}

	}

	strcpy(userName, formatString(0, userName));
	k = NOKEY;
	char info[][80] = {"Welcome ", "Now, create your user icon..."};
	strcat(info[0], userName);
	displayPara(0, 120, 200, info, " _", 1, 100);
	getch();
	displayPara(0, 120, 200, info+1, " _", 1, 100);
	getch();
	///////////////////////// GETTING USER ICON DETAILS ///////////////
	{
		cleardevice();
		int accept = 20;
		int maxx = getmaxx();
		int maxy = getmaxy();
		int poly[8] ;
		int polydet[8] = {10,400,10,470,60,470,60,400};
		int polydet2[8] = {100,400,100,470,160,470,160,400};
		int polyerase[8] = {200,400,200,470,260,470,260,400};
		int polyaccept[8] = {300,400,300,470,360,470,360,400};
		int i, w, h, j, mx, my,  mc, mmc; // mmx, mmy,
		int bg = WHITE, fg = BLACK;
		int animate = 1;
		int posx, posy;
		char kb = '0';
		w = (maxx - 40)/10;
		h = (maxy - 180)/10 ;

		for (i = 0; i < 10; i++)
			for (j = 0; j < 10; j++)
				userIcon[i][j] = bg;

		while(accept)
		{
			setcolor(BLACK);
			mousestatus();
			mc = out.x.bx;
			mx = out.x.cx;
			my = out.x.dx;
			kb = keyboardInput('0');
			if (kb == 'a') animate = 1;
			else if (kb == 'e') accept = 0;

			posx = (mx-20)/w;
			posy = (my- 20)/h;

			if (mc == 1 && mmc != 1)
			{

				if (mx >= 10 && mx <= 60 && my >= 400 && my <= 470)
				{
					for (i =0 ; i < 10; i++)
						for (j = 0; j < 10; j++)
							if (userIcon[i][j] == bg)
								if (userIcon[i][j] < 15) userIcon[i][j] ++; else userIcon[i][j] = 0;
					if (bg < 15) bg ++; else bg = 0;
				}
				if (mx >= 100 && mx <= 160 && my >= 400 && my <= 470) if (fg < 15) fg ++; else fg = 0;
				if (mx >= 300 && mx <= 360 && my >= 400 && my <= 470)
				{
					return;
				}
				if (mx >= 200 && mx <= 260 && my >= 400 && my <= 470) if (fg < 15)
				{
					for (i = 0; i < 10; i++)
						for (j = 0; j < 10; j++)
							userIcon[i][j] = bg;
				}
				animate = 1;
			}
			if (posx >= 0 && posx <10 && posy >= 0 && posy < 10 && mc ==1 && mmc ==1) userIcon[posy][posx] = fg, animate = 1;
			if (mc == 2 && mmc == 2)
			{
				if (posx >= 0 && posx <10 && posy >= 0 && posy < 10) userIcon[posy][posx] = bg;
				animate = 1;
			}

			if (animate)
			{
				cleardevice();
				setcolor(WHITE);
				settextstyle(1,HORIZ_DIR,1);
				outtextxy(10, 380, "BG");
				outtextxy(100,380, "FG");
				outtextxy(200,380, "Clear");
				outtextxy(300,380, "Accept");
				for (i = 0; i < 10; i++)
					for (j = 0; j < 10; j++)
					{
						poly[0] = 20 + j * w;
						poly[1] = 20 + i *h;
						poly[2] = 20 + j*w;
						poly[3] = 20 + i*h+ h;
						poly[4] = 20 + j * w + w;
						poly[5] = 20 + i * h + h;
						poly[6] = 20 + j * w + w;
						poly[7] = 20 + i * h;
						setfillstyle(SOLID_FILL, userIcon[i][j]);
						fillpoly(4, poly);


					}
				animate = 0;
				setcolor(fg);
				setfillstyle(SOLID_FILL, bg);
				fillpoly(4, polydet);

				setcolor(bg);
				setfillstyle(SOLID_FILL, fg);
				fillpoly(4, polydet2);

				setcolor(RED);
				setfillstyle(XHATCH_FILL, RED);
				fillpoly(4, polyerase);

				setcolor(GREEN);
				setfillstyle(LINE_FILL, GREEN);
				fillpoly(4, polyaccept);


				delay(100);
			}
			mmx = mx;
			mmy = my;
			mmc = mc;
		}
	}
}

void Industry::industryInteract()
{
	static int timer = 0;
	static int timerFlag = 0;
	static int timerMax = 0;
	static int barFlag = 0;


	if ( mx >= originX + industry_x - 100 && my >= originY + industry_y - 100 && mx <= originX + industry_x + 100 && my <= originY + industry_y + 100 && mc == 1 && mmc != 1)
	{
		if (EDITMODE == CREATE_MODE && player.getwood() >= 300 && !timerFlag)
		{
			timerFlag = 1;
			timer = 400;
			timerMax = 400;
			barFlag = 1;
			player.setwood(player.getwood() - 300);
			animate = 1;

		}
		else if (EDITMODE == CREATE_MODE && player.getwood() < 300 && !timerFlag)
		{
			setMiniBox("Not enough resources to get produce!", WHITE, RED, WHITE);
		}
		else if (EDITMODE == REMOVE_MODE)
		{
			setMiniBox("Cannot remove industry!", WHITE, RED, WHITE);
		}

		if (timerFlag && !timer)
		{
			player.setcurrXp(5);
			player.setproduce(player.getproduce() + 500);
			industryIncome += 500;
			timerFlag = 0;
			animate = 1;
		}

		if (EDITMODE == VIEW_MODE)
		{
			setDetailDisplay("Produce", "Industry");
		}

	}

	if (timer && timerFlag) timer --;

	if  (timerFlag && !timer && !barFlag)
	{
		// pickup icon

		setcolor(WHITE);
		setlinestyle(SOLID_LINE,0,1);
		circle(industry_x + originX - 10 + 30, industry_y +30+ originY - 10, 60);
		drawProduceIcon(industry_x + originX - 10, industry_y + originY - 10, 3,3);

	}

	if (barFlag)
	{
		drawBarHoriz(originX + industry_x - 50, originY + industry_y - 3, 100, 8, LIGHTGRAY, YELLOW, (float)(timerMax - timer)/timerMax * 100);
		if (!timer)
		{
			barFlag = 0;
			animate = 1;
			setMiniBox("Industry has completed its job!", LIGHTGRAY, BLUE, WHITE);
		}
	}


}

Boat::Boat()
{
	boatUsing = 0;
	boatTimer = 0;
	boatTimerMax = 0;
	boatAnimate = 0;
	boat_xx = terrW/2 - 80;
	boat_yy = 350;
	boat_x = terrW/2 - 80;
	boat_y = 350;
}

Puzzle::Puzzle ()
{
	randomize();
	completed = 0;
	list[0] = 0;
	limit = 20;
	sflag = 0;
	index = random(limit);
	locked = 0;

	strcpy(currscramble, "");
	selection = 0; choice = 0; scselection = 0;

	for (int i = 0; i < 20; i++)
	{
		completedList[i][0] = 0;
	}
}

void Puzzle::appendList()
{
	strcpy(completedList[completed], list);
	list [0] = 0;
	completed++;
	sflag = 1;

	for (int t = index; t < limit; t++)
		strcpy(clist[t], clist[t+1]);

	limit --;
	index = random(limit);

}

void Boat::boatInteract()
{
	if (mx >= originX + boat_x - 100 && my >= originY + boat_y - 25 && mx <= originX + boat_x + 100 && my <= originY + boat_y + 100 && mc == 1 && mmc != 1)
	{
		if (EDITMODE == CREATE_MODE )
		{
			if (!boatUsing && player.getproduce() >= 250 && !boatAnimate)
			{
				boatAnimate = 1 ;
				player.setproduce(player.getproduce() - 250);
			}
			else if (!boatUsing && player.getproduce() < 250 && !boatAnimate)
			{
				setMiniBox("Not enough produce to sell!", WHITE, RED, WHITE);
			}
			else if (boatAnimate == -2)
			{
				boatAnimate = 0 ;
				boatUsing = 0;

				player.setmoney(player.getmoney() + 1000);
				boatIncome += 1000;
				player.setcurrXp(10);
			}

		}

		if (EDITMODE == VIEW_MODE)
		{
			setDetailDisplay("Money", "The Boat");
		}

		animate = 1;
	}
	if (boatUsing)
	{
		if (boatTimer) boatTimer --;
		if (!boatTimer && boatAnimate == 2)
		{
			boatAnimate = -1;
			setMiniBox("Your boat has arrived!", LIGHTGRAY, BLUE, WHITE);
		}
		if (boatAnimate == -2)
		{
			// pickup icon

			setcolor(WHITE);
			setlinestyle(SOLID_LINE,0,1);
			circle(boat_x + originX - 10 + 30, boat_y +30+ originY - 10, 60);
			drawMoneyIcon(boat_x + originX - 38, boat_y + originY - 30, 3,3);
		}
	}

	if (boatAnimate == 2 )
	{
		drawBarHoriz(boat_x + originX - 50, originY + boat_y, 100, 8, BLACK, YELLOW, (float)(boatTimerMax - boatTimer)/boatTimerMax * 100);
	}

}

void Tree::interact( int n)
{
	int i;
	Tree *t = map_trees;
	void setMiniBox(char  text[], int colorBorder , int colorIn , int fontColor );
	void setDetailDisplay (char a[], char b[]);
	static char puzzleChar = 0;
	for (i = 0; i < n; i++)
	{
		if (mx >= originX + t[i].x - 50 && mx <= originX + t[i].x + 50 && my >= originY + t[i].y - 50 && my <= originY + t[i].y + 50)
		{
			if (mc == 1 && mmc !=1 && EDITMODE == VIEW_MODE)
			{
				if (t[i].cutdown == 0)
					setDetailDisplay("Resource", "Tree");
				else
					setDetailDisplay("Resource", "Bush");
			}
			else if (mc == 1 && mmc != 1 && EDITMODE == REMOVE_MODE && t[i].cutdown == 0)
			{
				t[i].cutdown = 1;
				player.setwood(player.getwood() + 100);
				player.setcurrXp(1);
				if (ecoMeter > 0) ecoMeter -= 5;
				animate = 1;
				treeCutCount ++;

				if (random(2))
				{
					puzzleChar = puzzle.pop();
					puzzle.add(puzzleChar);

					char text[80];
					sprintf(text, "You have collected one treasure: %c", puzzleChar);

					if (!puzzleChar)
					{
						sprintf(text, "You have collected all the letters. Try to unscramble them.");
						puzzle.appendList();
					}

					setMiniBox(text, GREEN, BLACK, GREEN);

				}

			}
			else if (mc == 1 && mmc != 1 && EDITMODE == CREATE_MODE)
			{
				if (player.getwater() >= 5 && t[i].cutdown)
				{
					t[i].cutdown = 0;
					player.setcurrXp(2);
					animate = 1;
					player.setwater(player.getwater() - 5);
					ecoMeter += 5;
					treeCutCount --;
				}
				else if (player.getwater() < 5)
				{
					setMiniBox("You need water to plant trees!", WHITE, RED, WHITE);
				}
				else if (!t[i].cutdown)
					setMiniBox("The tree is in good health!", WHITE, RED, WHITE);
			}
		}
	}
}

void Well :: wellInteract()
{

	well.waterToCollect = player.getplayerLevel() * 25;

	//when clicked on the well
	if (EDITMODE == CREATE_MODE && mx >= originX + well.x - 100 && my >= originY + well.y - 25 && mx <= originX + well.x + 100 && my <= originY + well.y + 100 && mc == 1 && mmc != 1)
	{
		if  (goal.currentGoalIndex() < 24 || !well.canCollect)
		{
			setMiniBox("Well is empty right now.", WHITE, RED, WHITE);
		}
		else if (well.canCollect)
		{
			// updating the water
			animate = 1;
			player.setwater(player.getwater() + well.waterToCollect);
			well.regenerateTimer = well.maxTimer * player.getplayerLevel();
			well.canCollect = 0;
		}
	}
	else if (EDITMODE == VIEW_MODE  && mx >= originX + well.x - 100 && my >= originY + well.y - 25 && mx <= originX + well.x + 100 && my <= originY + well.y + 100 && mc == 1 && mmc != 1)
	{
		setDetailDisplay("Water", "The Well");
	}
	else if (EDITMODE == REMOVE_MODE  && mx >= originX + well.x - 100 && my >= originY + well.y - 25 && mx <= originX + well.x + 100 && my <= originY + well.y + 100 && mc == 1 && mmc != 1)
	{
		setMiniBox("Cannot remove a well.", WHITE, RED, WHITE);
	}

	if (goal.currentGoalIndex() >= 24) // to enable the well implementation
	{
		if (!well.canCollect && well.regenerateTimer) well.regenerateTimer --;
		if (!well.regenerateTimer && !well.canCollect)
		{
			well.canCollect = 1;
			setMiniBox("The well has been replenished!", LIGHTGRAY, BLUE, WHITE);
			animate = 1;
		}

		if (well.canCollect)
		{
			//pickup icon
			setcolor(WHITE);
			setlinestyle(SOLID_LINE,0,1);
			circle(well.x + originX - 10 + 30, well.y +30+ originY - 10, 60);
			drawDropIcon(well.x + originX - 20, well.y + originY - 20, 3,3);
		}
	}
}

void plotter(int x,int y,int d,int c,int woc,int goc,int wic,int pic,int gic,int wfill,int pfill,int gfill)
{
	int s=c/50;
	int r  [8]  ={x,y-c,x+c,y,x,y+c,x-c,y};
	int p1 [8]  ={x,y-c,x+c,y,x+c,y-(s*10),x,y-(s*10)-c};
	int p2 [8]  ={x+c,y,x,y+c,x,y-(s*10)+c,x+c,y-(s*10)};
	int p3 [8]  ={x,y+c,x-c,y,x-c,y-(s*10),x,y-(s*10)+c};
	int p4 [8]  ={x-c,y,x,y-c,x,y-(s*10)-c,x-c,y-(s*10)};
	setcolor(woc);
	setfillstyle(pfill,pic);
	fillpoly(4,r);
	setcolor(woc);
	setfillstyle(wfill,wic);
	fillpoly(4,p1);
	fillpoly(4,p2);
	fillpoly(4,p4);
	fillpoly(4,p3);
	setcolor(goc);
	setfillstyle(gfill,gic);
	if (d==DOWN_LEFT) // downleft
	{
		int g1 [8] ={x-(s*30),y+(s*10),x-(s*30),y+(s*20),x-(s*10),y+(s*40),x-(s*10),y+(s*30)};
		fillpoly(4,g1);
	}
	else if (d==DOWN_RIGHT) // downright
	{
		int g2 [8] ={x+(s*30),y+(s*10),x+(s*30),y+(s*20),x+(s*10),y+(s*40),x+(s*10),y+(s*30)};
		fillpoly(4,g2);
	}
	else if (d==UP_RIGHT) // upright
	{
		int g3 [8] ={x+(s*30),y-(s*30),x+(s*30),y-(s*20),x+(s*10),y-(s*40),x+(s*10),y-(s*50)};
		fillpoly(4,g3);
	}
	else if(d==UP_LEFT) // upleft
	{
		int g4 [8] ={x-(s*30),y-(s*30),x-(s*30),y-(s*20),x-(s*10),y-(s*40),x-(s*10),y-(s*50)};
		fillpoly(4,g4);
	}
}

void House :: buildHouse(House &h)
{
	plotter(originX + h.x, originY + h.y + 50, h.direction, h.c, h.woc, h.goc, h.wic, h.pic, h.gic, h.wfill, h.pfill, h.gfill);

	int i;
	for (i = 0; i < h.level; i++)
	{
		obj.drawHouse(originX + h.x, originY + h.y - (50 * i), h.color1, h.color2, h.color3, h.direction);
	}
	if  (i) plotter(originX + h.x, originY + h.y + 50 - (50 * (i)), 10, 100, WHITE, h.goc, h.color2, h.color1, h.gic, h.wfill, INTERLEAVE_FILL, h.gfill);

	if (EDITMODE == MOVE_MODE && MovingHouse == &h)
	{
		setfillstyle(SOLID_FILL, YELLOW);
		drawtline(originX + h.x - 150 , 50 + originY + h.y, originX + h.x, 50+originY + h.y + 150, 8);
		drawtline(originX + h.x + 150 , 50 + originY + h.y, originX + h.x, 50+originY + h.y + 150, 8);
	}

}

void gameNew()
{

	cleardevice();
	randomize();
	char k = NOKEY;
	// cust color
	struct palettetype pal;
	getpalette(&pal);

	// GETTING USERNAME AS INPUT
	gameLoop = 1;
	mousereset();
	closegraph();
	int gd = DETECT, gm;
	initgraph(&gd, &gm, "..\\bgi");
	initmouse();
	// GAME
	setbkcolor(BLACK);
	animate = 1;
	while(gameLoop)
	{
		mousestatus();
		mx = out.x.cx;
		my = out.x.dx;
		mc = out.x.bx;

		k = keyboardInput(NOKEY);
		//if (tolower(k) == 'e') gameLoop = 0;
		//else
		if (tolower(k) == 'r') animate = 1;
		//else if (tolower(k) == 'b') animate = 0;
		else if (tolower(k) == 'o') {originX = 0; originY = 0;}
		//else if (tolower(k) == 'g') ecoMeter -= 25, animate = 1;
		//else if (tolower(k) == 'h') ecoMeter += 25, animate = 1;
		//else if (tolower(k) == 'e') exit(0);
		//else if (tolower(k) == 'h') goaldisplayed = 0, animate = 1;
		else if (tolower(k) == 'j') player.setcurrXp(10);


		if (animate)
		{

			cleardevice();
			//Green terrain
			drawTerrain();


			//All the roads
			mainRoad[0].build(originX, originY);
			mainRoad[1].build(originX, originY);
			mainRoad[2].build(originX, originY);
			mainRoad[3].build(originX, originY);

			// houses along with decorative trees
			obj.buildHouse(map_houses[0]);
			map_trees[0].draw(originX, originY);


			//
			obj.buildHouse(map_houses[1]);
			map_trees[1].draw(originX, originY);

			//
			obj.buildHouse(map_houses[2]);
			map_trees[2].draw(originX, originY);


			////
			obj.buildHouse(map_houses[3]);
			map_trees[3].draw(originX, originY);

			//
			obj.buildHouse(map_houses[4]);
			map_trees[4].draw(originX, originY);

			//
			obj.buildHouse(map_houses[5]);
			map_trees[5].draw(originX, originY);


			//
			obj.buildHouse(map_houses[6]);
			map_trees[6].draw(originX, originY);


			//
			obj.buildHouse(map_houses[7]);
			map_trees[7].draw(originX, originY);

			//industry
			industry.drawIndustry(originX , originY , BROWN, DARKGRAY, BLACK);

			//The Well
			well.drawWell(well.access(1) + originX, well.access(2) + originY, (well.access(3))? CYAN: BLACK);

			//the boat
			setrgbpalette(pal.colors[LIGHTMAGENTA], 0, 0, 0);

			//The huge lake
			drawlake(originX - 200, originY + 50);

			//trees elsewhere
			map_trees[8].draw(originX, originY);
			map_trees[9].draw(originX, originY);
			map_trees[10].draw(originX, originY);
			map_trees[11].draw(originX, originY);
			map_trees[12].draw(originX, originY);
			map_trees[13].draw(originX, originY);
			map_trees[14].draw(originX, originY);



			boat.drawBoat(originX, originY);

			setcolor(RED);


			//User details - name - icon - resources
			drawDetails();

			settextstyle(3, HORIZ_DIR,1);
			if (!messageDisplay && goaldisplayed)
				showMiniBox();

			//goal stuff
			goals_display();


			if (EDITMODE == SCRAMBLE_MODE)
				puzzle.drawPuzzleScreen();

			animate = 0;
		}
		tsprint();

		if (EDITMODE == SCRAMBLE_MODE)
			puzzle.puzzleInteract(k);

		if (!goaldisplayed)
		{
			goaldisplayed = 1;
			messageDisplay = 0;
			interact = 1;
			animate = 1;
		}


		if (!messageDisplay && interact)
			drag(k);

		if (miniMessageDisplay)
		{
			miniMessageTimer -- ;
			if (!miniMessageTimer) miniMessageDisplay = 0, animate = 1;
		}

		if (boat.boatAnimate == 1 || boat.boatAnimate == -1) animate = 1;


		boat.check();


		if (interact && !messageDisplay)
		{
			obj.houseInteract(map_houses, nhouses, k);

			Tree t;
			t.interact( ntrees);
			industry.industryInteract();
			boat.boatInteract();
			well.wellInteract();
		}

		if (showDetail)	detailCount --;
		if (detailCount == 0 && showDetail) {animate = 1; showDetail = 0;}

		if (mx >= 0 && mx <= 40 && my >= getmaxy() - 40 && my <= getmaxy() && mc == 1 && mmc != 1)
			menudisplay = 1 - menudisplay, animate = 1;

		if (menudisplay)
		{
			if (mx >= 218+43 && mx <= 258 + 43 && my >= getmaxy()-43 && my <= getmaxy() && mc == 1 && mmc != 1)
			{
				if (EDITMODE == VIEW_MODE)
				{gamesave(); ; return;}                    
				else
				{
					if (EDITMODE == SCRAMBLE_MODE)
						interact = 1;
					if (EDITMODE == MOVE_MODE)
					{
						movemodeend = 1;
					}
					else
						EDITMODE = VIEW_MODE;
					animate = 1;

				}
			}
			else if (mx >= 175 && mx <= 215 && my >= SCREEN_H - 43 && my <= SCREEN_H && mc == 1 && mmc != 1 && EDITMODE == VIEW_MODE)
			{
				goal.retut();
				animate = 1;
			}
			else if (mx >= 132 && mx <= 172 && my >= SCREEN_H - 43 && my <= SCREEN_H && mc == 1 && mmc != 1 && EDITMODE == VIEW_MODE)
			{
				goaldisplayed = 0;
				animate = 1;
			}
			else if (mx >= 89 && mx <= 129 && my >= SCREEN_H - 43 && my <= SCREEN_H && mc == 1 && mmc != 1 && EDITMODE == VIEW_MODE)
			{

				if (EDITMODE == VIEW_MODE)
				{
					EDITMODE = REMOVE_MODE;
					animate = 1;
				}
			}
			else if (mx >= 46 && mx <= 86 && my >= SCREEN_H - 43 && my <= SCREEN_H && mc == 1 && mmc != 1)
			{
				if (EDITMODE == VIEW_MODE)
				{
					EDITMODE = CREATE_MODE;
					animate = 1;
				}
			}
			else if (mx >= 218 && mx <= 258  && my >= getmaxy()-43 && my <= getmaxy() && mc == 1 && mmc != 1 && EDITMODE == VIEW_MODE && (puzzle.limit != 20 || puzzle.sflag))
			{
				EDITMODE = SCRAMBLE_MODE;
				interact = 0;
				animate = 1;
			}
			else if (mx >= 218 + 86 && mx <= 258 + 86 && my >= getmaxy()-43 && my <= getmaxy() && mc == 1 && mmc != 1 && EDITMODE == VIEW_MODE )
			{
				EDITMODE = MOVE_MODE;
				MovingHouse = NULL;
				animate = 1;
			}
		}

		goal.goalcheck();
		if (ecoMeter > 100 ) ecoMeter = 100;

		mmx = mx;
		mmy = my;
		mmc = mc;



		delay(50);
	}
}

void drawTerrain()
{
	int sea[] = {originX - terrW, originY, originX, originY - terrH, originX + terrW, originY, originX, originY + terrH};
	setcolor(BLUE);
	setfillstyle(CLOSE_DOT_FILL, BLUE);
	fillpoly(4, sea);

	struct palettetype pal;
	getpalette(&pal);
	setrgbpalette(pal.colors[LIGHTRED],  250, 181, 1);

	int beach[] = {originX - terrW/2 - 200, originY, originX, originY - terrH/2 - 200, originX + terrW/2 + 200, originY, originX, originY + terrH/2 + 200};
	setcolor(LIGHTRED);
	setfillstyle(CLOSE_DOT_FILL, LIGHTRED);
	fillpoly(4, beach);


	int terr[8] = {originX - terrW/2, originY, originX, originY - terrH/2, originX + terrW/2, originY, originX, originY + terrH/2};


	setcolor(GREEN);
	setfillstyle(CLOSE_DOT_FILL, GREEN);
	fillpoly(4,terr);


}

void changePalette(customPalette pal)
{
	for (int i = 0; i < 16; i++) setrgbpalette(i, pal.r[i], pal.g[i], pal.b[i]);
}

void drag(char l)
{

	int dg = 250;
	if (l == UP || tolower(l) == 'w') originY += dg, animate = 1;
	else if (l == DOWN|| tolower(l) == 's') originY -= dg, animate = 1;
	else  if (l == RIGHT|| tolower(l) == 'd') originX -= dg, animate = 1;
	else if (l == LEFT|| tolower(l) == 'a') originX += dg, animate = 1;

}

void drawDetails()
{
	int up = 0;

	char m[80];

	setcolor(CYAN);
	setlinestyle(USERBIT_LINE, 0, 1);
	setfillstyle(SOLID_FILL, MAGENTA);



	// DISPLAYING THE MONEY, RESOURCES, ETC.

	// money icon
	drawMoneyIcon(15, 10,2, 2);

	// wood icon
	drawWoodIcon(155, 10,2, 2);

	//produce icon
	drawProduceIcon(325, 10,3, 3);

	//water icon
	drawDropIcon(490, 10, 2, 2);

	//display player name
	settextstyle(7, HORIZ_DIR, 3);
	setcolor(YELLOW);
	outtextxy(55, getmaxy() - 100 + 10, player.getuserName());


	/// display resources
	settextstyle(8, HORIZ_DIR, 2);

	//display money
	sprintf(m, "%i", player.getmoney());
	outtextxy(10,80,m);
	//wood
	sprintf(m, "%d", player.getwood());
	outtextxy(150,80,m);
	//produce
	sprintf(m, "%d", player.getproduce());
	outtextxy(320 ,80,m);
	//water
	sprintf(m, "%d", player.getwater());
	outtextxy(485,80,m);


	setlinestyle(SOLID_LINE, 0, 1);

	drawBarHoriz(320 + 2 * 20 + 10 + textwidth("100000"),getmaxy() - 100 +20, 170, 20, BLACK, GREEN, ecoMeter );

	setcolor(YELLOW);
	settextstyle(8,HORIZ_DIR,1);
	sprintf(m, "Population: %d", population);
	outtextxy(320 + 2 * 20  + textwidth("100000"), getmaxy() - textheight("E") - 15, m);

	player.drawIcon();
	drawMenuIcon(3, getmaxy() - 43, 2, 2);

	int poly_details[] = {0,0, 0, 75, getmaxx(),75, getmaxx(), 0};


	if (showDetail)
	{
		setcolor(BLUE);
		setfillstyle(SOLID_FILL, BLUE);
		fillpoly(4, poly_details);
		setcolor(WHITE);
		setlinestyle(SOLID_LINE, up, 1);
		setcolor(WHITE);
		settextstyle(8, HORIZ_DIR, 3);
		outtextxy(55,10, detailObjType);
		outtextxy(320,10, detailObject);
	}

	if (menudisplay)
	{

		if (EDITMODE == VIEW_MODE || EDITMODE == REMOVE_MODE)
		{
			drawRemoveIcon(89, getmaxy()-43, 1,1);
		}
		if (EDITMODE == VIEW_MODE || EDITMODE == CREATE_MODE)
			drawCreateIcon(46, getmaxy()-43, 1,1);

		if (EDITMODE == VIEW_MODE)
		{
			drawGoalIcon(132, getmaxy()-43, 2,2);
			drawHelpIcon(175, getmaxy()-43, 2,2);
		}

		if(EDITMODE == VIEW_MODE || EDITMODE == SCRAMBLE_MODE)
		{
			drawScrambleIcon(175 + 43, getmaxy()-43, 1,1);
		}

		if (EDITMODE == VIEW_MODE || EDITMODE == MOVE_MODE)
		{
			drawMoveIcon(218 + 86, getmaxy() - 43, 2, 2);
		}

		drawBackIcon(218 + 43, getmaxy()-43, 2,2);
	}

	//level display
	drawBarVer(SCREEN_W - 50, 100, 20, 200, WHITE, CYAN, ((float)player.getcurrXp()/player.getmaxXp())*100);
	settextstyle(7, HORIZ_DIR, 1);
	sprintf(m, "Level %d", player.getplayerLevel());
	setcolor(BLACK);
	outtextVer(SCREEN_W - 50 + 3,100,m);


}

void House::drawHouse(int X, int Y, int color1, int color2, int color3, int Direction)
{
	// Color 1 - Roof , Color 2 - Walls , color3 - Door .
	setcolor(WHITE);
	int roof[] = { X , Y - 100 , X - 100, Y , X , Y + 100 , X + 100 , Y , X , Y - 100 };
	setfillstyle(INTERLEAVE_FILL, color1);
	fillpoly(4, roof);
	int wall1[] = { X - 100 , Y , X , Y + 100 , X , Y + 150 , X - 100 , Y + 50 , X - 100 , Y };
	setfillstyle(SOLID_FILL, color2);
	fillpoly(4, wall1);
	int wall2[] = { X , Y + 150 , X , Y + 100 , X + 100 , Y , X + 100 , Y + 50 , X , Y + 150 };
	fillpoly(4, wall2);
	if (Direction == DOWN_RIGHT)
	{
		int door[] = { X + 40 , Y + 110 , X + 65 , Y + 85 , X + 65 , Y + 50 , X + 40 , Y + 75 , X + 40 , Y + 110 };
		setfillstyle(SOLID_FILL, color3);
		fillpoly(4, door);
		putpixel(X + 45, Y + 90, WHITE);
		putpixel(X + 46, Y + 90, WHITE);
		setcolor(BLACK);
		int window[] = { X - 40 , Y + 100 , X - 65 , Y + 75 , X - 65 , Y + 45 , X - 40 , Y + 70 , X - 40 , Y + 100 };
		setfillstyle(SOLID_FILL, WHITE);
		fillpoly(4, window);
		line(X - 40, Y + 85, X - 65, Y + 60);
		line(X - 52.5, Y + 87.5, X - 52.5, Y + 57.5);
	}
	else if (Direction == DOWN_LEFT)
	{
		int door[] = { X - 40 , Y + 109 , X - 65 , Y + 84 , X - 65 , Y + 47 , X - 40 , Y + 72 , X - 40 , Y + 107 };
		setfillstyle(SOLID_FILL, color3);
		fillpoly(4, door);
		putpixel(X - 60, Y + 75, WHITE);
		putpixel(X - 61, Y + 75, WHITE);
		setcolor(BLACK);
		int window[] = { X + 37.5 , Y + 103.5 , X + 62.5 , Y + 78.5 , X + 62.5 , Y + 48.5 , X + 37.5 , Y + 73.5 , X + 40 , Y + 103.5 };
		setfillstyle(SOLID_FILL, WHITE);
		fillpoly(4, window);
		line(X + 62.5, Y + 63.5, X + 37.5, Y + 88.5);
		line(X + 50, Y + 90, X + 50, Y + 60);
	}
}

int scrollAnimation(int frame, int h)
{
	int sw, sh;
	int scrollH = 40;
	sw = getmaxx();
	sh = getmaxy();
	int bgPoly[8];
	bgPoly[0] = 60;
	bgPoly[1] = 0;
	bgPoly[2] = 60;
	bgPoly[4] = sw-60;
	bgPoly[6] = sw-60;
	bgPoly[7] = 0;
	int spd = 10;
	int acc = 25;
	int fgPoly[8];
	unsigned int lp = 0;
	int f = 0;
	//scrolling animations
	switch(frame)
	{
		case 0:
			setcolor(MAGENTA);
			for (int i =0;; i+= spd) // i <= sh - scrollH
			{

				spd += acc;

				bgPoly[3] = bgPoly[5] = i;

				setlinestyle(USERBIT_LINE, lp, 1);
				setcolor(YELLOW);
				setfillstyle(SOLID_FILL, RED);
				fillpoly(4,bgPoly);

				setlinestyle(USERBIT_LINE, lp, 1);
				setfillstyle(SOLID_FILL, RED);

				fgPoly[0] = 61;
				fgPoly[1] = i ;
				fgPoly[2] = 61 + (sw - 122)/2;
				fgPoly[3] = i + scrollH - 1;
				fgPoly[4] = sw-61;
				fgPoly[5] = i ;

				fillpoly(3, fgPoly);

				setlinestyle(SOLID_LINE, lp, 1);
				setcolor(YELLOW);
				setfillstyle(SOLID_FILL, YELLOW);
				drawtline(65, 0, 65, i, 5);
				drawtline(sw - 65, 0, sw - 65, i, 5);
				delay(100);
				if (f) { return i;}
				if (i > sh - scrollH) {i = sh - scrollH - spd - 10; cleardevice(); f = 1; }
			}
			break;

		case 1:
			bgPoly[3] = bgPoly[5] = h;

			setlinestyle(USERBIT_LINE, lp, 1);
			setcolor(YELLOW);
			setfillstyle(SOLID_FILL, RED);
			fillpoly(4,bgPoly);

			setlinestyle(USERBIT_LINE, lp, 1);
			setfillstyle(SOLID_FILL, RED);

			fgPoly[0] = 61;
			fgPoly[1] = h ;
			fgPoly[2] = 61 + (sw - 122)/2;
			fgPoly[3] = h + scrollH - 1;
			fgPoly[4] = sw-61;
			fgPoly[5] = h ;

			fillpoly(3, fgPoly);

			setlinestyle(SOLID_LINE, lp, 1);
			setcolor(YELLOW);
			setfillstyle(SOLID_FILL, YELLOW);
			drawtline(65, 0, 65, h, 5);
			drawtline(sw - 65, 0, sw - 65, h, 5);
			break;


	}
	return h;
}

void drawlake(int x,int y)
{

	int a=-80,b=-80,c=140,d=-50; //e=150,f=280;
	setcolor(BLUE);
	arc(140+x+a,140+y+b,40,150,50);
	arc(205+x+a,78+y+b,220,320,40);
	arc(300+x+a,218+y+b,50,120,130);
	arc(401+x+a,94+y+b,220,310,30);
	arc(435+x+a,144+y+b,15,120,30);

	arc(426+x+a,355+y+b,220,20,70);

	arc(150+x+a,193+y+b,200,280,80);
	arc(135+x+a,176+y+b,115,215,75);
	arc(280+x+a,350+y+b,152,210,205);
	arc(280+x+a,350+y+b,240,345,205);
	arc(300+x+c,218+y+d,50,120,130);
	arc(435+x+c,144+y+d,15,120,30);
	arc(405+x+c,147+y+d,330,15,60);
	arc(503+x+c,230+y+d,130,220,70);
	arc(337+x+c,403+y+d,20,50,170);
	arc(426+x+c,355+y+d,220,15,70);
	arc(x+510,y+380,250,15,100);
	arc(x+350,y+360,220,330,180);
	arc(x+500,y+80,360,150,80);
	arc(x+100,y+380,150,300,100);
	setfillstyle(SOLID_FILL,BLUE);
	floodfill(154+a+x,200+b+y,1);
	floodfill(20+x,60+y,1);
	floodfill(20+x,330+y,1);
	floodfill(500+x,320+y,1);
	floodfill(500+x,60+y,1);
	floodfill(320+x,240+y,1);
	floodfill(320+x,400+y,1);
	floodfill(400+x,400+y,1);
	floodfill(400+x,420+y,1);
}

void Well::drawWell(int X, int Y, int watercolor)
{

	X -= 200;
	Y -= 200;


	//drawRoad(int X, int Y, int direction, int w, int h, int color, int stripeColor, int fill, int stripeFill, int borderFill, int stripeBorderFill)
	//drawRoad( X + 215 ,  Y + 215 , DOWN_LEFT, 450, 450, BROWN, BLACK, CLOSE_DOT_FILL, EMPTY_FILL, DOTTED_LINE, 0);
	Road r;
	r.setProperties(X + 215, Y + 215, DOWN_LEFT, 450, 1, BROWN, BLACK, CLOSE_DOT_FILL, EMPTY_FILL, DOTTED_LINE, 0);
	r.build(originX, originY);

	setcolor(WHITE);
	ellipse(200 + X, 200 + Y, 0, 360, 100, 40);
	ellipse(200 + X, 200 + Y, 0, 360, 80, 25);
	line(100 + X, 200 + Y, 100 + X, 293 + Y);
	line(300 + X, 200 + Y, 300 + X, 293 + Y);
	arc(200 + X, 58 + Y, 247, 293, 255);
	arc(200 + X, 10 + Y, 247, 293, 255);
	arc(200 + X, 35 + Y, 247, 293, 255);
	//setfillstyle(SOLID_FILL,BROWN);
	//drawtline(120+X,220+Y,120+X,150-3-20+Y - 25,6);
	//drawtline(270+X,180+Y,270+X,135+Y,6);
	//drawtline(120+X,150-50+Y,270+X,150-80+Y,4);
	line(140 + X, 232 + Y, 140 + X, 257 + Y);
	line(140 + X, 283 + Y, 140 + X, 307 + Y);
	line(195 + X, 240 + Y, 195 + X, 265 + Y);
	line(195 + X, 290 + Y, 195 + X, 313 + Y);
	line(255 + X, 234 + Y, 255 + X, 257 + Y);
	line(255 + X, 284 + Y, 255 + X, 308 + Y);
	line(120 + X, 252 + Y, 120 + X, 278 + Y);
	line(165 + X, 262 + Y, 165 + X, 286 + Y);
	line(225 + X, 263 + Y, 225 + X, 289 + Y);
	line(275 + X, 252 + Y, 275 + X, 278 + Y);
	setfillstyle(SOLID_FILL, BROWN);
	drawtline(120 + X, 220 + Y, 120 + X, 150 - 3 - 20 + Y - 25, 6);
	drawtline(270 + X, 180 + Y, 270 + X, 135 + Y, 6);
	drawtline(120 + X, 150 - 50 + Y, 270 + X, 150 - 80 + Y, 4);
	line(120 + 30 + X, 160 + Y, 270 + 30 + X, 130 + Y);
	line(120 + X, 100 + Y, 140 + 10 + X, 160 + Y);
	line(270 + X, 70 + Y, 290 + 10 + X, 130 + Y);
	line(120 + X, 100 + Y, 90 + X, 155 + Y);
	line(90 + X, 155 + Y, 90 + 50 + X, 155 - 13 + Y);
	floodfill(110 + X, 140 + Y, WHITE);
	floodfill(130 + X, 140 + Y, WHITE);
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	floodfill(150 + X, 120 + Y, WHITE);
	floodfill(270 + X, 110 + Y, WHITE);
	setfillstyle(SOLID_FILL, watercolor);
	floodfill(200 + X, 200 + Y, WHITE);//inner ellipse
	setfillstyle(SOLID_FILL, DARKGRAY);
	floodfill(290 + X, 200 + Y, WHITE);
	floodfill(130 + X, 232 + Y, WHITE);
	floodfill(150 + X, 240 + Y, WHITE);
	floodfill(200 + X, 250 + Y, WHITE);
	floodfill(130 + X, 300 + Y, WHITE);
	floodfill(200 + X, 300 + Y, WHITE);
	floodfill(150 + X, 300 + Y, WHITE);
	floodfill(280 + X, 280 + Y, WHITE);
	floodfill(110 + X, 272 + Y, WHITE);
	floodfill(130 + X, 272 + Y, WHITE);
	floodfill(200 + X, 272 + Y, WHITE);
	floodfill(250 + X, 272 + Y, WHITE);
	floodfill(290 + X, 272 + Y, WHITE);
}



void Boat::check()
{

	if (boatAnimate == 3)
	{
		boatAnimate = 2;
		animate = 1;
		boatUsing = 1;
	}
}

void Boat::drawBoat(int x, int y)
{
	x += boat_xx;
	y += boat_yy;
	x -= 230 ; y -= 230 ;

	if (boatAnimate != 2)
	{
		struct palettetype pal;
		getpalette(&pal);
		setrgbpalette(pal.colors[LIGHTCYAN],  63, 40, 10);

		setcolor(14);
		arc ( x + 312 , y + 590 , 81 , 122 , 400 ) ;
		arc ( x + 160 , y - 145 , 261 , 302 , 400 ) ;
		arc ( x + 100 , y - 100 , 270  , 313 , 400 ) ;
		line ( x + 100 , y + 248 , x + 100 , y + 301 ) ;
		setfillstyle ( SOLID_FILL , BROWN ) ;
		floodfill ( x + 120 , y + 270 , YELLOW ) ;
		line ( x + 100 , y + 249 , x + 75 , y + 305 ) ;
		arc ( x + 75 , y + 250 , 270 , 300 , 56 ) ;
		setfillstyle ( SOLID_FILL , YELLOW ) ;
		drawtline ( x + 220 , y + 100 , x + 220 , y + 250 , 3 ) ;
		setfillstyle ( SOLID_FILL , DARKGRAY ) ;
		floodfill ( x + 85 , y + 290  , YELLOW ) ;
		tcircle ( x + 220 , y + 100 , 5 , 10 ) ;
		arc ( x + 85 , y + 180 , 336 , 24 , 150 ) ;
		arc ( x + 220 , y + 180 , 272 , 90 , 60 ) ;
		setfillstyle ( SOLID_FILL , LIGHTGRAY ) ;
		floodfill ( x + 240 , y + 180  , YELLOW ) ;
		setfillstyle ( SOLID_FILL , LIGHTGRAY ) ;
		floodfill ( x + 240 , y + 200  , YELLOW ) ;
		setcolor ( LIGHTGRAY ) ;
		arc ( x + 312 , y + 590 , 95 , 101 , 400 ) ;
		setfillstyle ( SOLID_FILL , LIGHTCYAN ) ;
		floodfill ( x + 200 , y + 210  , YELLOW ) ;
		setfillstyle ( SOLID_FILL , LIGHTCYAN ) ;
		floodfill ( x + 312 , y + 200  , YELLOW ) ;
		setfillstyle ( SOLID_FILL , LIGHTCYAN ) ;
		floodfill ( x + 230 , y + 210 , YELLOW ) ;
	}
	if (boatAnimate == 1)
	{
		if (boat_xx < boat_x + 200 && boat_yy > boat_y - 100)
		{
			boat_xx += 40;
			boat_yy -= 20;
		}
		else
		{
			boatAnimate = 3;
			boatTimer = 500;
			boatTimerMax = 500;
			boatUsing = 0 ;
		}
	}
	else if (boatAnimate == -1)
	{
		if (boat_xx > boat_x && boat_yy < boat_y)
		{
			boat_xx -= 40;
			boat_yy += 20;
		}
		else
		{
			boatAnimate = -2;
		}
	}

}


void drawMoneyIcon(int x, int y, int xscale, int yscale)
{
	int poly[8];
	int up = 0;
	setlinestyle(USERBIT_LINE, up, 0);

	static int picture[40][40] = {15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,10,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,10,10,10,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,10,10,10,10,10,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,10,10,10,10,10,10,10,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,10,10,10,10,10,10,10,10,10,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,10,10,10,10,10,10,10,10,10,10,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,10,10,10,10,10,10,10,10,10,10,10,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,10,10,10,10,10,10,10,10,10,10,10,10,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,10,10,10,10,10,10,10,10,10,10,10,10,10,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,10,10,10,10,10,10,10,10,10,10,10,10,10,10,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,10,10,10,10,10,10,10,10,10,10,10,10,10,10,10,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,10,10,10,10,10,10,10,10,10,10,10,10,10,10,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,10,10,10,10,10,10,10,10,10,10,10,10,10,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,10,10,10,10,10,10,10,10,10,10,10,10,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,10,10,10,10,10,10,10,10,10,10,10,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,10,10,10,10,10,10,10,10,10,10,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,10,10,10,10,10,10,10,10,10,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,10,10,10,10,10,10,10,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,10,10,10,10,10,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,10,10,10,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,10,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15
	};


	for (int i = 0; i < 40; i++)
		for (int j = 0; j < 40; j++)
		{
			setfillstyle(SOLID_FILL, picture[i][j]);
			poly[0] = poly[2] = x + i*(xscale);
			poly[1] = poly[7] = y + j*(yscale);
			poly[3] = poly[5] = y + (j+1) * yscale;
			poly[4] = poly[6] = x + (i+1) * xscale;
			if (picture[i][j] != WHITE)
				fillpoly(4, poly);
		}
}


void drawScrambleIcon(int x, int y, int xscale, int yscale)
{

	int picture[40][40] = {15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,14,14,14,14,14,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,
		15,15,15,15,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15
	};

	int poly[8]	;
	for (int i = 0; i < 40; i++)
		for (int j = 0; j < 40; j++)
		{
			if (picture[i][j] == 14)
				picture[i][j] = RED;
			setfillstyle(SOLID_FILL, picture[i][j]);
			poly[0] = poly[2] = x + i*(xscale);
			poly[1] = poly[7] = y + j*(yscale);
			poly[3] = poly[5] = y + (j+1) * yscale;
			poly[4] = poly[6] = x + (i+1) * xscale;
			if (picture[i][j] != WHITE) fillpoly(4, poly);
		}

	setcolor(WHITE)	;
	rectangle(x,y, x +  40, y + 40);


}

void drawMoveIcon(int x, int y, int xscale, int yscale)
{
	static int picture[20][20] = {15,15,15,15,15,15,15,15,15,15,7,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,7,7,7,7,7,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,7,15,7,15,7,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,7,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,7,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,7,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,7,15,15,15,15,15,15,15,15,15,
		15,7,7,15,15,15,15,15,15,15,7,15,15,15,15,15,15,7,7,15,
		15,7,15,15,15,15,15,15,15,15,7,15,15,15,15,15,15,15,7,15,
		7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,7,
		15,7,15,15,15,15,15,15,15,15,7,15,15,15,15,15,15,15,7,15,
		15,7,7,15,15,15,15,15,15,15,7,15,15,15,15,15,15,7,7,15,
		15,15,15,15,15,15,15,15,15,15,7,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,7,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,7,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,7,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,7,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,7,15,7,15,7,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,7,7,7,7,7,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,7,15,15,15,15,15,15,15,15,15
	};

	int poly[8]	;
	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
		{
			if (picture[i][j] == 14)
				picture[i][j] = RED;
			setfillstyle(SOLID_FILL, picture[i][j]);
			poly[0] = poly[2] = x + i*(xscale);
			poly[1] = poly[7] = y + j*(yscale);
			poly[3] = poly[5] = y + (j+1) * yscale;
			poly[4] = poly[6] = x + (i+1) * xscale;
			if (picture[i][j] != WHITE) fillpoly(4, poly);
		}

	setcolor(WHITE)	;
	rectangle(x,y, x +  40, y + 40);

}

void drawWoodIcon(int x, int y, int xscale, int yscale)
{
	int poly[8];
	int up = 0;
	setlinestyle(USERBIT_LINE, up, 0);

	static int picture[40][40] = {15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,6,6,6,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,6,6,14,6,6,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,6,6,14,14,14,6,6,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,6,14,14,14,14,14,6,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,6,14,14,14,14,14,6,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,6,6,6,15,15,6,14,14,14,6,14,6,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,6,6,14,6,6,15,6,14,14,14,6,14,6,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,6,6,14,14,14,6,6,6,14,14,14,6,14,6,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,6,14,14,14,14,14,6,6,14,14,14,14,14,6,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,6,14,14,14,14,14,6,6,14,14,14,14,14,6,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,6,14,14,14,14,14,6,6,14,14,14,14,14,6,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,6,14,6,14,14,14,6,6,14,6,14,14,14,6,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,6,14,6,14,14,6,6,6,14,6,14,14,14,6,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,6,14,6,14,14,14,6,6,14,6,14,14,14,6,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,6,14,14,14,14,14,6,6,14,14,14,14,14,6,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,6,14,14,14,14,14,6,6,14,14,14,6,14,6,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,6,6,14,14,14,14,6,6,14,14,14,14,14,6,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,6,6,14,14,6,14,6,6,14,14,14,14,14,6,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,6,14,14,14,6,14,6,6,14,14,14,14,14,6,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,6,14,14,14,6,14,6,6,14,14,6,14,14,6,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,6,14,14,14,14,14,6,6,6,6,6,6,6,6,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,6,14,14,14,14,14,6,6,6,14,14,14,6,6,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,6,14,14,14,14,14,6,6,14,14,6,14,14,6,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,6,14,14,6,14,14,6,6,14,14,6,14,14,6,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,6,6,6,6,6,6,6,6,6,14,14,14,6,6,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,6,6,14,14,14,6,6,6,6,6,6,6,6,6,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,6,14,14,6,14,14,6,6,14,14,6,14,14,6,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,6,14,14,6,14,14,6,6,6,6,6,6,6,6,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,6,6,14,14,14,6,6,6,6,14,14,14,6,6,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,6,6,6,6,6,15,6,14,14,6,14,14,6,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,6,15,15,15,6,14,14,6,14,14,6,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,6,6,14,14,14,6,6,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,6,6,6,6,6,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,6,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15
	};
	for (int i = 0; i < 40; i++)
		for (int j = 0; j < 40; j++)
		{
			setfillstyle(SOLID_FILL, picture[i][j]);
			poly[0] = poly[2] = x + i*(xscale);
			poly[1] = poly[7] = y + j*(yscale);
			poly[3] = poly[5] = y + (j+1) * yscale;
			poly[4] = poly[6] = x + (i+1) * xscale;
			if (picture[i][j] != WHITE) fillpoly(4, poly);
		}
}

void drawMenuIcon(int x, int y, int xscale, int yscale)
{
	int poly[8];
	int up = 0;
	setlinestyle(USERBIT_LINE, up, 0);

	static int picture[20][20] = {15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,9,9,15,15,9,9,15,15,9,9,15,15,15,15,15,15,15,15,15,15,9,9,15,15,9,9,15,15,9,9,15,15,15,
		15,15,15,15,15,15,15,9,9,15,15,9,9,15,15,9,9,15,15,15,15,15,15,15,15,15,15,9,9,15,15,9,9,15,15,9,9,15,
		15,15,15,15,15,15,15,15,15,9,9,15,15,9,9,15,15,9,9,15,15,15,15,15,15,15,15,15,15,9,9,15,15,9,9,15,15,
		9,9,15,15,15,15,15,15,15,15,15,15,9,9,15,15,9,9,15,15,9,9,15,15,15,15,15,15,15,15,15,15,9,9,15,15,9,9,
		15,15,9,9,15,15,15,15,15,15,15,15,15,15,9,9,15,15,9,9,15,15,9,9,15,15,15,15,15,15,15,15,15,15,9,9,15,
		15,9,9,15,15,9,9,15,15,15,15,15,15,15,15,15,15,9,9,15,15,9,9,15,15,9,9,15,15,15,15,15,15,15,15,15,15,
		9,9,15,15,9,9,15,15,9,9,15,15,15,15,15,15,15,15,15,15,9,9,15,15,9,9,15,15,9,9,15,15,15,15,15,15,15,15,
		15,15,9,9,15,15,9,9,15,15,9,9,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15};



	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
		{
			setfillstyle(SOLID_FILL, picture[i][j]);
			poly[0] = poly[2] = x + i*(xscale);
			poly[1] = poly[7] = y + j*(yscale);
			poly[3] = poly[5] = y + (j+1) * yscale;
			poly[4] = poly[6] = x + (i+1) * xscale;
			if (picture[i][j] != WHITE) fillpoly(4, poly);
		}

	setlinestyle(SOLID_LINE, up, 0);
	setcolor(WHITE);
	rectangle(x,y, x + 20 * xscale, y + 20 * yscale);
}

void drawCreateIcon(int x, int y, int xscale, int yscale)
{
	int poly[8];
	int up = 0;
	setlinestyle(USERBIT_LINE, up, 0);

	static int picture[40][40] = {WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,WHITE,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,WHITE,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,WHITE,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,WHITE,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,BLACK,BLACK,BLACK,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,WHITE,WHITE,BLACK,BLACK,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,WHITE,WHITE,BLACK,BLACK,BLACK,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,WHITE,WHITE,BLACK,BLACK,BLACK,BLACK,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BROWN,BROWN,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BROWN,BROWN,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BLACK,BLACK,BLACK,BLACK,BLACK,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BLACK,BLACK,BLACK,BLACK,BLACK,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BROWN,BROWN,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BROWN,BROWN,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BROWN,BROWN,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BROWN,BROWN,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BROWN,BROWN,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BROWN,BROWN,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BROWN,BROWN,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BROWN,BROWN,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BROWN,BROWN,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,BROWN,BROWN,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,WHITE,BROWN,BROWN,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,BROWN,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,WHITE,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,WHITE,LIGHTGRAY,LIGHTGRAY,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,WHITE,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,WHITE,LIGHTGRAY,LIGHTGRAY,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,LIGHTGRAY,LIGHTGRAY,LIGHTGRAY,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE
	};

	for (int i = 0; i < 40; i++)
		for (int j = 0; j < 40; j++)
		{
			setfillstyle(SOLID_FILL, picture[i][j]);
			poly[0] = poly[2] = x + i*(xscale);
			poly[1] = poly[7] = y + j*(yscale);
			poly[3] = poly[5] = y + (j+1) * yscale;
			poly[4] = poly[6] = x + (i+1) * xscale;
			if (picture[i][j] != WHITE) fillpoly(4, poly);
		}

	setcolor(WHITE);
	setlinestyle(SOLID_LINE, up, 0);
	rectangle(x,y, x + 40 * xscale, y + 40 * yscale);
}

void drawRemoveIcon(int x, int y, int xscale, int yscale)
{
	int poly[8];
	int up = 0;
	setlinestyle(USERBIT_LINE, up, 0);

	static int picture[40][40] = {WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,YELLOW,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,YELLOW,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,YELLOW,YELLOW,WHITE,WHITE,YELLOW,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,YELLOW,YELLOW,WHITE,WHITE,YELLOW,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,YELLOW,YELLOW,WHITE,WHITE,YELLOW,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,YELLOW,YELLOW,WHITE,WHITE,YELLOW,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,YELLOW,YELLOW,WHITE,WHITE,YELLOW,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,YELLOW,YELLOW,WHITE,WHITE,YELLOW,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,YELLOW,YELLOW,WHITE,WHITE,YELLOW,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,YELLOW,YELLOW,WHITE,WHITE,YELLOW,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,YELLOW,YELLOW,WHITE,WHITE,YELLOW,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,YELLOW,YELLOW,WHITE,WHITE,YELLOW,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,YELLOW,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,YELLOW,YELLOW,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,YELLOW,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE
	};

	for (int i = 0; i < 40; i++)
		for (int j = 0; j < 40; j++)
		{
			setfillstyle(SOLID_FILL, picture[i][j]);
			poly[0] = poly[2] = x + i*(xscale);
			poly[1] = poly[7] = y + j*(yscale);
			poly[3] = poly[5] = y + (j+1) * yscale;
			poly[4] = poly[6] = x + (i+1) * xscale;
			if (picture[i][j] != WHITE)  fillpoly(4, poly);
		}

	setcolor(WHITE);
	setlinestyle(SOLID_LINE, up, 0);
	rectangle(x,y, x + 40 * xscale, y + 40 * yscale);
}

void drawGoalIcon(int x, int y, int xscale, int yscale)
{
	int poly[8];
	int up = 0;
	setlinestyle(USERBIT_LINE, up, 0);

	static int picture[20][20] = {15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,14,14,14,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15
			,4,4,4,4,4,4,4,4,4,4,4,14,14,15,15,15,15,15,15,15,4,4,4,4,4,4,4,4,4,4,4,4,14,14,15,15,15,15,15,15,4,4,
		4,4,4,4,4,4,4,4,4,4,4,14,14,15,15,15,15,15,4,4,4,4,4,4,4,4,4,4,4,4,4,4,14,14,15,15,15,15,4,4,4,4,4,4,4
			,4,4,4,4,4,4,4,4,14,14,15,15,15,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,14,14,15,15,4,4,4,4,4,4,4,4,4,4,4,4,4,
		4,4,4,4,14,14,15,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,14,14,15,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,14,14,15,
		15,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,14,14,15,15,15,4,4,4,4,4,4,4,4,4,4,4,4,4,4,14,14,15,15,15,15,4,4,4,4
			,4,4,4,4,4,4,4,4,4,14,14,15,15,15,15,15,4,4,4,4,4,4,4,4,4,4,4,4,14,14,15,15,15,15,15,15,4,4,4,4,4,4,4,
		4,4,4,4,14,14,15,15,15,15,15,15,15,14,14,14,14,14,14,14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15};

	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
		{
			setfillstyle(SOLID_FILL, picture[i][j]);
			poly[0] = poly[2] = x + i*(xscale);
			poly[1] = poly[7] = y + j*(yscale);
			poly[3] = poly[5] = y + (j+1) * yscale;
			poly[4] = poly[6] = x + (i+1) * xscale;
			if (picture[i][j] != WHITE) fillpoly(4, poly);
		}

	setcolor(WHITE);
	setlinestyle(SOLID_LINE, up, 0);
	rectangle(x,y, x + 20 * xscale, y + 20 * yscale);
}

void drawHelpIcon(int x, int y, int xscale, int yscale)
{
	int poly[8];
	int up = 0;
	setlinestyle(USERBIT_LINE, up, 0);

	static int picture[20][20] = {15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,3,3,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,3,3,3,3,15,15,15,15,15,15,15,15,15,15,15,15,15,15,3,3,3,
		3,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,3,3,15,15,15,15,15,15,15,15,3,3,3,3,15,3,3,15,15,15,
		3,3,3,3,15,15,15,15,3,3,3,3,3,3,15,3,3,15,15,15,15,15,3,3,3,3,3,3,3,3,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,3,3,3,3,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15};

	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
		{
			setfillstyle(SOLID_FILL, picture[i][j]);
			poly[0] = poly[2] = x + i*(xscale);
			poly[1] = poly[7] = y + j*(yscale);
			poly[3] = poly[5] = y + (j+1) * yscale;
			poly[4] = poly[6] = x + (i+1) * xscale;
			if (picture[i][j] != WHITE) fillpoly(4, poly);
		}

	setcolor(WHITE);
	setlinestyle(SOLID_LINE, up, 0);
	rectangle(x,y, x + 20 * xscale, y + 20 * yscale);
}

void drawBackIcon(int x, int y, int xscale, int yscale)
{
	int poly[8];
	int up = 0;
	setlinestyle(USERBIT_LINE, up, 0);

	static int picture[20][20] = {15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,GREEN,GREEN,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,15,15,15,15,15,
		15,15,15,15,15,15,15,15,GREEN,GREEN,15,GREEN,GREEN,15,GREEN,GREEN,15,15,15,15,15,15,GREEN,GREEN,15,15,15,GREEN,GREEN,15,15,GREEN,GREEN,15,15,GREEN,GREEN,15,
		15,15,15,15,GREEN,GREEN,15,15,15,GREEN,15,15,15,GREEN,GREEN,15,15,15,GREEN,15,15,15,15,15,GREEN,GREEN,15,15,15,GREEN,15,15,15,GREEN,GREEN,15,15,15,
		GREEN,15,15,15,15,15,GREEN,GREEN,15,15,15,15,15,15,15,GREEN,GREEN,15,15,15,15,15,15,15,15,15,GREEN,GREEN,15,15,15,15,15,15,15,GREEN,GREEN,15,
		15,15,15,15,15,15,15,15,GREEN,GREEN,15,15,15,15,15,15,15,GREEN,GREEN,15,15,15,15,15,15,15,15,15,GREEN,GREEN,15,15,15,15,15,15,15,
		GREEN,GREEN,15,15,15,15,15,15,15,15,15,GREEN,GREEN,15,15,15,15,15,15,15,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,15,15,15,15,15,15,15,GREEN,
		GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,GREEN,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15};

	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
		{
			setfillstyle(SOLID_FILL, picture[i][j]);
			poly[0] = poly[2] = x + i*(xscale);
			poly[1] = poly[7] = y + j*(yscale);
			poly[3] = poly[5] = y + (j+1) * yscale;
			poly[4] = poly[6] = x + (i+1) * xscale;
			if (picture[i][j] != WHITE) fillpoly(4, poly);
		}

	setcolor(WHITE);
	setlinestyle(SOLID_LINE, up, 0);
	rectangle(x,y, x + 20 * xscale, y + 20 * yscale);
}

void drawProduceIcon(int x, int y, int xscale, int yscale)
{
	int poly[8];
	int up = 0;
	setlinestyle(USERBIT_LINE, up, 0);

	static int picture[20][20] = {WHITE,WHITE,WHITE,WHITE,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,WHITE,
		WHITE,WHITE,WHITE,BLACK,BLACK,BLACK,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BLACK,WHITE,
		WHITE,WHITE,BLACK,BLACK,BROWN,BLACK,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BLACK,WHITE,
		WHITE,BLACK,BLACK,BROWN,BROWN,BLACK,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BLACK,WHITE,
		BLACK,BLACK,BROWN,BROWN,BROWN,BLACK,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BLACK,WHITE,
		BLACK,BROWN,BROWN,BROWN,BROWN,BLACK,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BLACK,WHITE,
		BLACK,BROWN,BROWN,BROWN,BROWN,BLACK,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BLACK,WHITE,
		BLACK,BROWN,BROWN,BROWN,BROWN,BLACK,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BLACK,WHITE,
		BLACK,BROWN,BROWN,BROWN,BROWN,BLACK,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BLACK,WHITE,
		BLACK,BROWN,BROWN,BROWN,BROWN,BLACK,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BLACK,WHITE,
		BLACK,BROWN,BROWN,BROWN,BROWN,BLACK,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BLACK,WHITE,
		BLACK,BROWN,BROWN,BROWN,BROWN,BLACK,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BLACK,WHITE,
		BLACK,BROWN,BROWN,BROWN,BROWN,BLACK,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BLACK,WHITE,
		BLACK,BROWN,BROWN,BROWN,BROWN,BLACK,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BLACK,WHITE,
		BLACK,BROWN,BROWN,BROWN,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,WHITE,
		BLACK,BROWN,BROWN,BLACK,BLACK,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BLACK,BLACK,WHITE,
		BLACK,BROWN,BLACK,BLACK,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BLACK,BLACK,WHITE,WHITE,
		BLACK,BLACK,BLACK,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BROWN,BLACK,BLACK,WHITE,WHITE,WHITE,
		BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,BLACK,WHITE,WHITE,WHITE,WHITE,
		WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE,WHITE
	};

	for (int i = 0; i < 20; i++)
		for (int j = 0; j < 20; j++)
		{
			if (picture[i][j] != WHITE)
			{
				setfillstyle(SOLID_FILL, picture[i][j]);
				poly[0] = poly[2] = x + i*(xscale);
				poly[1] = poly[7] = y + j*(yscale);
				poly[3] = poly[5] = y + (j+1) * yscale;
				poly[4] = poly[6] = x + (i+1) * xscale;
				fillpoly(4, poly);
			}
		}
}

void drawDropIcon(int x, int y, int xscale, int yscale)
{
	int poly[8];
	int up = 0;
	setlinestyle(USERBIT_LINE, up, 0);
	static int picture[30][30] =
	{
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,1,1,1,1,1,1,1,1,1,1,1,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,1,1,1,1,1,1,1,1,1,1,1,1,1,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,1,1,1,1,1,1,
		1,1,1,1,1,1,1,1,1,15,15,15,15,15,15,15,15,15,15,15,15,15,15,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,15,15,15,15,
		15,15,15,15,15,15,15,15,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,15,15,15,15,15,15,15,15,15,15,15,1,1,1,1,1,1,1,
		1,1,1,1,1,1,1,3,3,3,3,1,1,15,15,15,15,15,15,15,15,15,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,1,1,15,15,15,15,
		15,15,15,15,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,1,1,15,15,15,15,15,15,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,
		3,3,3,3,3,3,3,1,15,15,15,15,15,15,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,3,3,3,1,15,15,15,15,15,15,15,1,1,
		1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,3,3,1,1,15,15,15,15,15,15,15,15,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,3,3,1,
		1,15,15,15,15,15,15,15,15,15,15,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,3,3,3,1,1,15,15,15,15,15,15,15,15,15,15,15,
		1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,15,15,15,15,15,15,15,15,15,15,15,15,15,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
		1,1,15,15,15,15,15,15,15,15,15,15,15,15,15,15,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,1,1,1,1,1,1,1,1,1,1,1,1,1,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,1,1,1,1,
		1,1,1,1,1,1,1,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,
		15,15,15,15,15,15,15
	};


	for (int i = 0; i < 30; i++)
		for (int j = 0; j < 30; j++)
		{
			setfillstyle(SOLID_FILL, picture[i][j]);
			poly[0] = poly[2] = x + i*(xscale);
			poly[1] = poly[7] = y + j*(yscale);
			poly[3] = poly[5] = y + (j+1) * yscale;
			poly[4] = poly[6] = x + (i+1) * xscale;
			if (picture[i][j] != WHITE)
				fillpoly(4, poly);
		}
}

// Color 1 - Roof , Color 2 - Walls , color3 - Door .
void Industry::drawIndustry ( int x , int y , int color1 , int color2 , int color3 )
{
	x+=industry_x ;
	y+=industry_y ;
	setcolor ( BROWN ) ;
	int roof [] = { x , y - 200 , x - 200, y , x , y + 200 , x + 200 , y , x , y - 200 } ;
	setfillstyle ( INTERLEAVE_FILL , color1 ) ;
	fillpoly ( 4 , roof ) ;
	int wall1 [] = { x - 200 , y , x , y + 200 , x , y + 300 , x - 200 , y + 100 , x - 200 , y } ;
	setfillstyle ( SOLID_FILL , color2 ) ;
	fillpoly ( 4 , wall1 ) ;
	int wall2 [] = { x , y + 300 , x , y + 200 , x + 200 , y , x + 200 , y + 100 , x , y + 200 } ;
	fillpoly ( 4 , wall2 ) ;
	setcolor ( BROWN ) ;
	setlinestyle ( SOLID_LINE , 0 , 3 ) ;
	int door [] = { x - 75 , y + 225 , x - 140 , y + 160 , x - 140 , y + 105 , x - 75 , y + 170 } ;
	setfillstyle ( SOLID_FILL , color3 ) ;
	fillpoly ( 4 , door ) ;
	setlinestyle ( SOLID_LINE , 0 , 3 ) ;
	setcolor ( BROWN ) ;
	line ( x - 110 , y + 190 , x - 110 , y + 135 ) ;
	setlinestyle ( SOLID_LINE , 0 , 1 ) ;
	x -= 10 , y -= 20 ;
	int roofz [] = { x , y - 100 , x - 100, y , x , y + 100 , x + 100 , y , x , y - 100 } ;
	setfillstyle ( INTERLEAVE_FILL , color1 ) ;
	fillpoly ( 4 , roofz ) ;
	int wall1z [] = { x - 100 , y , x , y + 100 , x , y + 150 , x - 100 , y + 50 , x - 100 , y } ;
	setfillstyle ( SOLID_FILL , color2 ) ;
	fillpoly ( 4 , wall1z ) ;
	int wall2z [] = { x , y + 150 , x , y + 100 , x + 100 , y , x + 100 , y + 50 , x , y + 150 } ;
	fillpoly ( 4 , wall2z ) ;
	x += 162 , y += 220 ;
	int roofzq [] = { x , y - 100 , x - 100, y , x , y + 100 , x + 100 , y , x , y - 100 } ;
	setfillstyle ( INTERLEAVE_FILL , color1 ) ;
	fillpoly ( 4 , roofzq ) ;
	int wall1zq [] = { x - 100 , y , x , y + 100 , x , y + 150 , x - 100 , y + 50 , x - 100 , y } ;
	setfillstyle ( SOLID_FILL , color2 ) ;
	fillpoly ( 4 , wall1zq ) ;
	int wall2zq [] = { x , y + 150 , x , y + 100 , x + 100 , y , x + 100 , y + 50 , x , y + 150 } ;
	fillpoly ( 4 , wall2zq ) ;
	int doorzq [] = { x - 40 , y + 109 , x - 65 , y + 84 , x - 65 , y + 47 , x - 40 , y + 72 , x - 40 , y + 107 } ;
	setfillstyle ( SOLID_FILL , color3 ) ;
	fillpoly ( 4 , doorzq ) ;
	putpixel ( x - 60 , y + 75 , WHITE ) ;
	putpixel ( x - 61 , y + 75 , WHITE ) ;

}

void messagebox(char message[][80] , int color, int n, int image_index)
{
	messageDisplay = 1;
	int y = 10;
	int x = 80;
	setcolor(color);
	scrollAnimation(1, 300);
	for (int i = 0; i < n; i++)
	{

		settextstyle(7,HORIZ_DIR, 3);
		outtextxy(x,y + i * (textheight(message[i])+ 10), message[i]);
	}
	switch (image_index)
	{
		case 1:
			drawMoneyIcon(getmaxx()/2 - 40/2, y + i * (textheight(message[i-1])+ 10), 2,2);
			break;
		case 2:
			drawWoodIcon(getmaxx()/2 - 40/2, y + i * (textheight(message[i-1])+ 10), 2,2);
			break;
		case 3:
			drawMenuIcon(getmaxx()/2 - 40/2, y + i * (textheight(message[i-1])+ 10), 2,2);
			break;
		case 4:
			drawCreateIcon(getmaxx()/2 - 40/2,y + i * (textheight(message[i-1])+ 10), 1,1);
			break;
		case 5:
			drawRemoveIcon(getmaxx()/2 - 40/2, y + i * (textheight(message[i-1])+ 10), 1,1);
			break;
		case 6:
			drawGoalIcon(getmaxx()/2 - 40/2, y + i * (textheight(message[i-1])+ 10), 2,2);
			break;
		case 7:
			drawHelpIcon(getmaxx()/2 - 40/2, y + i * (textheight(message[i-1])+ 10), 2,2);
			break;
		case 8:
			drawBackIcon(getmaxx()/2 - 40/2, y + i * (textheight(message[i-1])+ 10), 2,2);
			break;
		case 9:
			drawProduceIcon(getmaxx()/2 - 40/2, y + i * (textheight(message[i-1])+ 10), 2,2);
			break;
		case 10:
			drawDropIcon(getmaxx()/2 - 40/2, y + i * (textheight(message[i-1])+ 10), 2,2);
			break;
		case 11:
			drawScrambleIcon(getmaxx()/2 - 40/2, y + i * (textheight(message[i-1] + 10)), 1,1);
			break;
		case 12:
			drawMoveIcon(getmaxx()/2 - 40/2, y + i * (textheight(message[i-1] + 10)), 2,2);
			break;
	};


}

void goals_display()
{

	if (!goaldisplayed)
	{
		char goalmessage[11][80];
		strcpy(goalmessage[0], goal.getTitle());
		for (int i = 0; i < goal.getMessageLength(); i++)
			strcpy(goalmessage[i+1], goal.getMessage(i));
		messagebox(goalmessage, YELLOW, goal.getMessageLength() + 1, goal.getImage());
		char c = '0';
		while (1)
		{
			c = keyboardInput('0');
			if (c == '\n' || c == '\r' ) return;
		}
		//getch();
	}

}

int displayMenu()
{
	int mc, mx, my, mclick;    //mouse vars
	int mmx, mmy, mmc = 1;      //checking movement of mouse
	int TRANSITION_MODE = 0,MENU_MODE = 1,l_mouse_using;  //checks
	int logo = 1; // For the loop
	char key;  // KEYSTROKE KEYBOARD INPUT
	char text[40] = "";
	int menu_selection = 0; // 0 - New Game || 1 - Continue || 2 - About || 3 - Exit

	SCREEN_W = getmaxx();
	SCREEN_H = getmaxy();

	// LOGO
	int x,y,r[] = {170, 150, 130},a[6];
	x = SCREEN_W/2;
	y = SCREEN_H/2;
	a[0] = 0;
	a[1] = 80;
	a[2] = 180;
	a[3] = 180 + 80;
	a[4] = 180 + -80;
	a[5] = 180;

	int tr = 0, trSpeed = 0, trAcc = 10;

	//LOGO LOOP

	initmouse();

	while (logo)
	{
		cleardevice();

		//GETTING MOUSE STATUS
		mousestatus();
		mc = out.x.bx;
		mx = out.x.cx;
		my = out.x.dx;

		if (mx != mmx || my != mmy) l_mouse_using = 1 ;
		else l_mouse_using = 0;

		key = keyboardInput(NOKEY);


		if (key == 'w' || key == 'W' || key == UP)                 // KEY UP
		{
			l_mouse_using = 0;
			if (menu_selection > 0)
			{
				menu_selection -= 1;
			}
			else
			{
				menu_selection = 3;
			}
		}
		if (key == 's' || key == 'S' || key == DOWN)     // menu down
		{
			l_mouse_using  = 0;
			if (menu_selection < 3)
			{
				menu_selection += 1;
			}
			else
			{
				menu_selection = 0;
			}
		}

		// DRAWING LOGO

		if (MENU_MODE == 1)
		{

			int f = 0;
			setcolor(LIGHTBLUE);
			settextstyle(8, HORIZ_DIR, 4);
			for (f =0; f < 6; f ++)
				outtextxy(getmaxx()/2 - textwidth("MENU")/2 + f, 20 + f, "MENU");


			if (l_mouse_using == 1 && my >= SCREEN_H/2 - 90 && my < SCREEN_H/2 - 60) {
				menu_selection = 0;
			}
			if (l_mouse_using == 1 && my >= SCREEN_H/2 - 60 && my < SCREEN_H/2 - 30)
			{
				menu_selection = 1;
			}
			if (l_mouse_using && my >= SCREEN_H/2 - 30 && my < SCREEN_H/2)
			{
				menu_selection = 2;
			}
			if (l_mouse_using == 1 && my >= SCREEN_H/2 && my < SCREEN_H/2 + 30)
			{
				menu_selection = 3;
			}

			if (menu_selection == 0 ) setcolor(LIGHTBLUE);
			else setcolor(YELLOW);

			settextstyle(1, HORIZ_DIR, 2);
			if(!TRANSITION_MODE) outtextxy(SCREEN_W/2 - 60, SCREEN_H/2  - 90, "New Game");

			if (menu_selection == 1) setcolor(LIGHTBLUE);
			else setcolor(YELLOW);

			if(!TRANSITION_MODE) outtextxy(SCREEN_W/2 - 60, SCREEN_H/2 - 60, "Continue");

			if (menu_selection == 2)  setcolor(LIGHTBLUE);
			else setcolor(YELLOW);
			if(!TRANSITION_MODE) outtextxy(SCREEN_W/2 - 60, SCREEN_H/2 - 30, "  About");


			if (menu_selection == 3)  setcolor(LIGHTBLUE);
			else setcolor(YELLOW);
			if (!TRANSITION_MODE)outtextxy(SCREEN_W/2 - 60, SCREEN_H/2 , "   Exit");

			if (key == '\r' || (mc == 1 && mmc != 1) )     //   SELECTING FROM MENU
			{

				TRANSITION_MODE = 1;
				MENU_MODE = 0;

			}

		}


		// ARCS MOVING AROUND

		x = SCREEN_W/2;
		y = SCREEN_H/2 ;
		setcolor(RED);
		drawtarc(x,y, a[0], a[1], r[0] + tr, 5);
		setcolor(BLUE);
		drawtarc(x,y,a[2],a[3],r[1] + tr,5);
		setcolor(GREEN);
		drawtarc(x,y,a[4],a[5],r[2] + tr,5);


		//TRANSITION FROM THE MENU TO THE SELECTED SCREEN

		if(TRANSITION_MODE)
		{
			switch(menu_selection)
			{

				case 0:
					setcolor(LIGHTBLUE);
					outtextxy(SCREEN_W/2 - 60, SCREEN_H/2  - 90, "New Game");
					if (tr < 200)
					{
						tr += trSpeed;
						trSpeed += trAcc;
					}

					else
					{
						strcpy(text, "");
						gameReset();
						gameNew();
						TRANSITION_MODE = 0;
						MENU_MODE = 1;
					}

					break;

				case 1:
					setcolor(LIGHTBLUE);
					outtextxy(SCREEN_W/2 - 60, SCREEN_H/2  - 60, "Continue");
					ifstream file1("player.dat"), file4("goals.dat"), file2("houses.dat"), file3("trees.dat");
					if (file1 && file2 && file3 && file4)
					{
						if (tr < 200)
						{
							tr += trSpeed;
							trSpeed += trAcc;
						}

						else
						{
							gameload();
							gameNew();
							TRANSITION_MODE = 0;
							MENU_MODE = 1;
						}
					}
					else
					{
						strcpy(text, "No old game exists! Try New Game.");
						TRANSITION_MODE  =0;
						MENU_MODE = 1;
					}
					file1.close();
					file2.close();
					file3.close();
					break;

				case 2:
					setcolor(LIGHTBLUE);
					outtextxy(SCREEN_W/2 - 60, SCREEN_H/2 - 30, "  About");
					if (tr < 200)
					{
						tr += trSpeed;
						trSpeed += trAcc;
					}

					else
					{
						displayAbout();
						TRANSITION_MODE = 0;
						MENU_MODE = 1;
					}

					break;

				case 3:
					setcolor(LIGHTBLUE);
					outtextxy(SCREEN_W/2 - 60, SCREEN_H/2 , "   Exit");
					if (tr < 200)
					{
						tr += trSpeed;
						trSpeed += trAcc;
					}

					else
					{
						logo = displayExit(1);
						if (!logo) 
						{
							exit(0);
						}
						TRANSITION_MODE = 0;
						MENU_MODE = 1;
					}

					break;


			}
		}


		settextstyle(1,HORIZ_DIR,1);
		//outtextxy(400,400, inttochar(mc));

		if (!TRANSITION_MODE && tr > 0)
		{
			tr -= trSpeed;
			trSpeed -= trAcc;
		}

		if (tr < 0) tr = 0;

		//red
		a[0] -= 9 * !tr;
		a[1] -= 9 * !tr;

		//blue
		a[2] += 7 * !tr;
		a[3] += 7 * !tr;

		//green
		a[4] -= 5 * !tr;
		a[5] -= 5 * !tr;

		setcolor(WHITE);
		outtextxy(10, getmaxy() - 20, text);


		delay(50); // 90 - 110 is working fine
		mmc = mc;
		mmx = mx;
		mmy = my;

	}
	return 0;
}

void gameReset()
{
	player=PLAYER();

	// reset houses
	for (int i = 0; i < nhouses; i++)
	{
		map_houses[i].rlevel() = 0;
		map_houses[i].rpopulation() = 0;
	}

	for ( i = 0; i < ntrees; i++)
		map_trees[i].setCutStatus(0);

	menudisplay = 0;
	treeCount = ntrees;
	houseCount = 0;
	goaldisplayed = 0;
	goal.setGoalIndex(0);


	mainRoad[0].setProperties(
			-300+150-150,-3000/2+300-75+150,
			150,
			terrH/150,
			DOWN_RIGHT,
			EMPTY_FILL,
			WHITE,
			CLOSE_DOT_FILL,
			BROWN,
			DOTTED_LINE,
			SOLID_LINE
			);

	mainRoad[1].setProperties(
			+ 3000/4 - 150*3 + 75 - 75 - 150,-3000/4 + 75 + 150,
			150,
			terrH/150 - 5,
			DOWN_LEFT,
			SOLID_FILL,
			WHITE,
			CLOSE_DOT_FILL,
			DARKGRAY,
			DOTTED_LINE,
			SOLID_LINE
			);

	mainRoad[2].setProperties(
			industry.industry_x - 150-75-20-30,industry.industry_y +150,
			150,
			6,
			DOWN_RIGHT,
			SOLID_FILL,
			WHITE,
			CLOSE_DOT_FILL,
			DARKGRAY,
			DOTTED_LINE,
			SOLID_LINE
			);

	mainRoad[3].setProperties(
			well.access(1) - 300,well.access(2) - 225,
			150,
			3,
			DOWN_RIGHT,
			EMPTY_FILL,
			WHITE,
			CLOSE_DOT_FILL,
			BROWN,
			DOTTED_LINE,
			SOLID_LINE
			);

	map_trees[0].setPositions(150 - 20,-3000/2 + 100+ 80);
	map_trees[1].setPositions(150 - 60 - 20+150,-3000/2 + 100+ 80+150);
	map_trees[2].setPositions(150 - 40+150+150-25,-3000/2 +150+ 100+ 80+150);
	map_trees[3].setPositions( + 150 - 100+150+150+150 - 5,-3000/2 +150+150+ 100+ 80+150);
	map_trees[4].setPositions(+ 150 - 50+150+150+150+150-15,-3000/2 +150+ 100+ 80+150+150+150);
	map_trees[5].setPositions(+ 150 - 150+150+150+150+150+150-30,-3000/2 +150+ 100+ 80+150+150+150+150);
	map_trees[6].setPositions(+600+ 150 - 20+150+150,-3000/2 +150+ 100+600+ 80+150);
	map_trees[7].setPositions(+ 150 -80+150+150+600+150-30,-3000/2 +150+ 100+ 80+150+600+150);
	map_trees[8].setPositions( - 100,0);
	map_trees[9].setPositions(-1000, 10);
	map_trees[10].setPositions(-1300, -25);
	map_trees[11].setPositions(-750, 60);
	map_trees[12].setPositions(-1000, 250);
	map_trees[13].setPositions(industry.industry_x, industry.industry_y - 450);
	map_trees[14].setPositions(industry.industry_x - 100, industry.industry_y - 350);

	cleardevice();
	player.accept();

}

void drawBarHoriz(int x, int y, int w, int h, int color0, int color1, float percent)
{
	setcolor(color1);setlinestyle(SOLID_LINE, 0, 1);
	rectangle(x, y, x + w, y + h);
	int polyBack[] = {x + 2, y + 2, x + 2, y + h -2, x + w - 2, y + h -2 , x + w -2, y + 2};
	int polyFore[] = {x + 2, y + 2, x + 2, y + h -2, x + (percent/100) * w -2, y + h -2 , x + (percent/100) *w -2, y + 2};

	setfillstyle(SOLID_FILL, color0);
	fillpoly(4, polyBack);
	setfillstyle(SOLID_FILL, color1);
	fillpoly(4, polyFore);
}

void drawBarVer(int x, int y, int w, int h, int color0, int color1, float percent)
{
	setcolor(color1);setlinestyle(SOLID_LINE, 0, 1);
	setlinestyle(SOLID_LINE, 0, 1);
	rectangle(x, y, x + w, y + h);
	int polyBack[] = {x + 2, y + 2, x + 2, y + h -2, x + w - 2, y + h -2 , x + w -2, y + 2};
	int polyFore[] = {x + 2, y + 2 + (100-percent)/100 * h, x + 2, y + h  -2, x +  w -2, y + h -2, x + w -2, y + 2 + (100-percent)/100 * h};

	setfillstyle(SOLID_FILL, color0);
	fillpoly(4, polyBack);
	setfillstyle(SOLID_FILL, color1);
	fillpoly(4, polyFore);
}

void outtextVer(int x, int y, char m[])
{
	for (int xxx = 0; m[xxx]; xxx++)
	{
		char t[] = " ";
		t[0] = m[xxx];
		outtextxy(x, y + textheight(m)*xxx, t);
	}
}

void showMiniBox()
{
	if (miniMessageDisplay && miniMessageTimer)
	{


		// drawing the box
		int poly[8];
		setcolor(miniColorBack);
		setlinestyle(SOLID_LINE, 0, 1);
		setfillstyle(SOLID_FILL, miniColorBack);
		poly[0] = poly[2] = 0;
		poly[1] = poly[7] = 300;
		poly[3] = poly[5] = poly[1] + textheight(miniMessage) + 20;
		poly[4] = poly[6] = poly[0] + MAX(textwidth(miniMessage), 100) + 10;
		fillpoly(4, poly);

		setcolor(miniColorFont);
		outtextxy(poly[0] + 5, poly[1] + 10, miniMessage);


	}
}

void setMiniBox(char  text[], int colorBorder , int colorIn , int fontColor  )
{
	strcpy(miniMessage, text);
	miniColorBorder = colorBorder;
	miniColorBack = colorIn;
	miniColorFont = fontColor;
	miniMessageDisplay = 1;
	miniMessageTimer = 50;
	animate = 1;
}

void setDetailDisplay (char a[], char b[])
{
	strcpy(detailObjType , a);
	strcpy(detailObject , b);
	detailCount = 20;
	showDetail = 1;

	animate = 1;
}
void Puzzle::drawPuzzleScreen ()
{
	int pad = 50;
	int screen[8] = {
		pad,pad,
		getmaxx() - pad, pad,
		getmaxx() - pad, getmaxy() - pad,
		pad, getmaxy() - pad
	}	;


	setfillstyle(SOLID_FILL, BROWN);
	setcolor(BLACK);

	fillpoly(4,screen);

	rectangle(pad, pad, getmaxx() - pad, getmaxy());

	int sx = getmaxx() / 2;
	sx += 10;

	settextstyle(7, HORIZ_DIR, 2);

	for (int i = 0; i < completed; i++)
	{
		if (i == selection && selection >= locked)
			setcolor(YELLOW);
		else
			setcolor(BLACK);
		outtextxy(pad + 5, pad + 5 + i*(textheight("H")+5) , completedList[i]);
	}

	for (i =0 ; i < strlen(completedList[selection]); i++)
	{
		if(scselection == i)
			setcolor(RED);
		else
			setcolor(BLACK);

		char t[2];
		t[1] = 0;
		t[0] = completedList[selection][i];
		outtextxy(sx + 10 + i * (textwidth("A ")), pad + 10, t);
	}

	outtextxy(sx + 10, getmaxy()  - pad - textheight("S") - 20, currscramble);

	setcolor(RED);
	if (choice == 0)
		rectangle(pad + 2,pad + 2, sx - 2, getmaxy() - pad - 2);
	else
		rectangle(sx + 2, pad + 2, getmaxx() - pad - 2, getmaxy() - pad - 2);
}

void Puzzle::puzzleInteract(char k)
{
	if (k != NOKEY)
	{

		if (choice == 0) // The menu on the left
		{
			if (k == DOWN || tolower(k) == 's')
				if (selection == completed - 1)
					selection = 0;
				else
					selection ++ ;

			if (k == UP || tolower(k) == 'w')
				if (selection == 0)
					selection = completed - 1;
				else
					selection -- ;

			if ((k == RIGHT || tolower(k) == 'd' || k ==  '\r' || k == '\n') && selection >= locked)
				choice = 1;

			if (k == '\b')
			{
				EDITMODE = VIEW_MODE;
				animate = 1;
				interact = 1;
			}

		}
		else // The scrambling work on the right
		{

			if (k == DOWN || tolower(k) == 's' || k == ' ' || k == '\n' || k == '\r')
			{
				char t[2];
				t[1] = 0;
				t[0] = completedList[selection][scselection];
				strcat(currscramble, t);
				for (int j = scselection; j < strlen(completedList[selection]); j++)
					completedList[selection][j] = completedList[selection][j+1];
				if (scselection == strlen(completedList[selection]))
					scselection --;
				if (strlen(completedList[selection]) == 0)
				{
					k = '\b'; // to simulate the press of a backspace
				}
			}


			if ((k == UP || tolower(k) == 'w') && strlen(currscramble))
			{
				char t[2];
				t[1] = 0;
				t[0] = currscramble[strlen(currscramble) - 1];
				strcat(completedList[selection], t);
				currscramble[strlen(currscramble) - 1] = 0;
			}

			if (k == LEFT || tolower(k) == 'a')
			{
				if (scselection == 0)
					scselection = strlen(completedList[selection]) - 1;
				else
					scselection --;
			}


			if (k == RIGHT || tolower(k) == 'd' )
			{
				if (scselection == strlen(completedList[selection]) - 1)
					scselection = 0;
				else
					scselection ++;
			}


			if (tolower(k) == '\b') // when either pressing the back key or when all the words above are completed
			{
				strcat(currscramble, completedList[selection]);
				strcpy(completedList[selection], currscramble);
				currscramble[0] = 0;
				scselection = 0;
				choice = 0;
				if (stringSearch(rlist, completedList[selection]))
				{
					locked ++; // Put the rewards here!
					selection = locked;
					char t[15];
					strcpy(t, completedList[selection]);
					for (int i = selection; i > 0; i--)
						strcpy(completedList[i], completedList[i-1]);
					strcpy(completedList[0], t);
				}
			}

		}
		animate = 1;
	}
}

void tsprint()
{
	char value[20];
	strcpy(value, itoa(tsval, value, 10));
	settextstyle(7, HORIZ_DIR, 3);
	setcolor(WHITE);
	outtextxy(100,100, tsstr);
	outtextxy(100, 120, value);
}


void gamesave()
{
	cleardevice();
	setcolor(GREEN);
	outtextxy(10,10, "Saving game...");
	char *s = (char*)&player;
	ofstream file("player.dat", ios::binary);
	file.write(s, sizeof(player));
	file.close();
	file.open("houses.dat", ios::binary);
	s = (char*)map_houses;
	file.write(s, sizeof(map_houses));
	file.close();
	file.open("trees.dat", ios::binary);
	s = (char*)map_trees;
	file.write(s, sizeof(map_trees));
	file.close();
	file.open("goals.dat");
	file << goal.currentGoalIndex(); 
	outtextxy(10,50, "Game saved! press any key to continue..");
	file.close();
	getch();
}

void gameload()
{
	cleardevice();
	outtextxy(10,10,"Loading game...");
	char *s = (char*)&player;
	ifstream file("player.dat", ios::binary);
	for(int i = 0; i < sizeof(PLAYER); i++)
	{file.get(*s);
		s++;
	}
	file.close();
	file.open("houses.dat", ios::binary);
	s = (char*)map_houses;
	for(i = 0; i < sizeof(map_houses); i++)
	{
		file.get(*s);
		s++;
	}
	file.close();
	file.open("trees.dat", ios::binary);

	s = (char*)map_trees;
	for (i =0; i < sizeof(map_trees); i++)
	{
		file.get(*s);
		s++;
	}
	file.close();
	file.open("goals.dat");
	int n;
	file >> n;
	goal.setGoalIndex(n);
	goaldisplayed = 0;
	file.close();
	mainRoad[0].setProperties(
			-300+150-150,-3000/2+300-75+150,
			150,
			terrH/150,
			DOWN_RIGHT,
			EMPTY_FILL,
			WHITE,
			CLOSE_DOT_FILL,
			BROWN,
			DOTTED_LINE,
			SOLID_LINE
			);

	mainRoad[1].setProperties(
			+ 3000/4 - 150*3 + 75 - 75 - 150,-3000/4 + 75 + 150,
			150,
			terrH/150 - 5,
			DOWN_LEFT,
			SOLID_FILL,
			WHITE,
			CLOSE_DOT_FILL,
			DARKGRAY,
			DOTTED_LINE,
			SOLID_LINE
			);

	mainRoad[2].setProperties(
			industry.industry_x - 150-75-20-30,industry.industry_y +150,
			150,
			6,
			DOWN_RIGHT,
			SOLID_FILL,
			WHITE,
			CLOSE_DOT_FILL,
			DARKGRAY,
			DOTTED_LINE,
			SOLID_LINE
			);

	mainRoad[3].setProperties(
			well.access(1) - 300,well.access(2) - 225,
			150,
			3,
			DOWN_RIGHT,
			EMPTY_FILL,
			WHITE,
			CLOSE_DOT_FILL,
			BROWN,
			DOTTED_LINE,
			SOLID_LINE
			);
	outtextxy(10,50, "Game loaded. Press any key to continue..");
	getch();
}

#endif

