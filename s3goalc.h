//S3's New goal control

#ifndef S3GOALC_H
#define S3GOALC_H

#include "S3goalma.h"

void log(char* t)
{
	ofstream fout("log.txt", ios::app);
	fout << t << endl;
	fout.close();
}

struct Goaldata
{
	char title[40];
	char message[10][80];
	int message_length;
	int image_index;
} ;


Goaldata Loadgoal ( int n )
{
	ifstream fin ( "Goaldata.dat" ) ;
	Goaldata Goal ;
	char * S = (char*)&Goal;
	fin.seekg ( n*sizeof(Goal)) ;
	for ( int i = 0 ; i < sizeof(Goaldata) ; i++ )
	{

		fin.get (*S) ;
		S++ ;
	}
	return Goal ;
}



class Goal
{
	Goaldata currgoal;
	int currgoalindex;
	int goalbeftut;

	public:

	Goal()
	{
		goalbeftut = -1;
	}

	void goalcheck();
	void goalload();
	char *getTitle();
	char *getMessage(int n);
	int getMessageLength();
	int getImage();
	int currentGoalIndex();
	int nextGoalIndex();
	void retut();
	void setGoalIndex(int);
	void nextGoal();

}goal;

void Goal::goalload()
{
	currgoal = Loadgoal(currgoalindex);	
}

void Goal::retut()
{
	goalbeftut = currgoalindex;
	currgoalindex = 0;
	currgoal = Loadgoal(0);
	goaldisplayed = 0;
}

char *Goal::getTitle()
{
	return currgoal.title;
}

char *Goal::getMessage(int n)
{
	return currgoal.message[n];
}

int Goal::getMessageLength()
{
	return currgoal.message_length;
}

int Goal::getImage()
{
	return currgoal.image_index;
}

int Goal::currentGoalIndex()
{
	return currgoalindex;
}


void Goal::setGoalIndex(int n)
{
	currgoalindex = n;
	currgoal =  Loadgoal(n);
	goaldisplayed = 0;
}

void Goal::nextGoal()
{
	currgoalindex++;
	currgoal = Loadgoal(currgoalindex);
	goaldisplayed = 0;
}

void Goal::goalcheck()
{
	int i;
	static int tf;
	switch (currgoalindex)
	{
		case 0: 
			if (goaldisplayed) 
				nextGoal();
			break;
		case 1:
			if (menudisplay) 
				nextGoal();                             
			break;
		case 10:
			if (EDITMODE == CREATE_MODE) 
			{ 
				nextGoal();
				tf = houseBuiltCount;
			} break;
		case 11:
			if (houseBuiltCount - tf >= 1)
			{
				nextGoal();          
			}

			break;
		case 12:
			if (EDITMODE == REMOVE_MODE) 
			{
				nextGoal();
				tf = treeCutCount;
			}
			break;
		case 13:
			if (treeCutCount - tf >= 1)
			{
				nextGoal();             
			}

			break;
		case 14:
			if (goaldisplayed) {
				originX = +200 -industry.industry_x;
				originY = +200 -industry.industry_y;

				nextGoal();         

				strcpy(tsstr, "Goal passed from panning!");
				tsval = 2;
			}
			break;
		case 15:
			strcpy(tsstr, "It should work!");
			if (goaldisplayed) 
			{
				nextGoal();          
				tf = treeCutCount;
			}
			break;
		case 16:
			sprintf(tsstr, "%d %d", tf, treeCutCount);

			if (treeCutCount - tf >= 5)
			{
				nextGoal();
				goaldisplayed = 0;
			}

			break;
		case 17:
			if (industry.industryIncome > 0) 
			{
				nextGoal();
			} 
			break;
		case 18:
			//panning towards the boat
			{
				if (goaldisplayed) {
					originX = +200-boat.boat_x;
					originY = +200 -boat.boat_y;
					nextGoal();

				} // next part
			}
			break;
		case 19:
			if (boatIncome > 0) 
			{
				nextGoal();
			}
			break;
		case 20:
			if (goaldisplayed)
			{

				tf = houseBuiltCount;
				nextGoal();

				/*for (i = 0; i < nhouses; i++)
				  if (map_houses[i].level) liveHouseCount++;
				  houseCount = liveHouseCount;*/
			}
			break;
		case 21:

			if (houseBuiltCount - tf >= 3)
			{
				nextGoal();
				tf = treeCutCount;
			}
			break;
		case 22:

			if (ecoMeter <= 40 || treeCutCount - tf >= 2)
			{
				nextGoal();
			}
			break;
		case 23:
			if (goaldisplayed)
			{
				tf = treeCutCount;
				nextGoal();
			}
			break;
		case 24:
			if (treeCutCount - tf <= -5)
			{
				nextGoal();
				goaldisplayed = 0;
			}

			break;
		case 25:
			if (goaldisplayed)
			{
				nextGoal();
			}
			break;
		case 26:
			if (player.getplayerLevel() == 2)
			{
				player.setmoney(player.getmoney()+ 2000);
				player.setwood(player.getwood()+ 2000);
				player.setwater(player.getwater()+ 25);

				nextGoal();
			}
			break;
		case 27:
			if (goaldisplayed)
			{
				nextGoal();
			}
			break;
		case 28:
			if (goaldisplayed)
			{
				nextGoal();
			}
			break;
		default:
			if (currgoalindex >= 2 && currgoalindex <= 8)
			{
				if(goaldisplayed)
					nextGoal();
			}
			else if (currgoalindex  == 9)
			{
				if(goaldisplayed)
					if(goalbeftut != -1)
						setGoalIndex(goalbeftut);
					else
						nextGoal();
			}
	}

}

#endif
