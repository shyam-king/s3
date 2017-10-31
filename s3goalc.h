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
	char goalObjective[40]; 
	char postGoalCommand[40];
} ;


Goaldata Loadgoal ( int n )
{
	ifstream fin ("GOALDATA.DAT", ios::binary);
	Goaldata Goal ;
	fin.seekg ( n*sizeof(Goal)) ;
	fin.read((char*)&Goal, sizeof(Goal));
	fin.close();

	return Goal ;
}

class Goal
{
	Goaldata currgoal;
	int currgoalindex;
	int tf ;
	int goalbeftut;
	char splitObjective[5][20];
	char splitCommand[5][20];

	public:

	Goal()
	{
		goalbeftut = -1;
		tf = 0;
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

	char *rGoalObjective()
	{
		return currgoal.goalObjective;
	}

}goal;

void Goal::goalload()
{
	currgoal = Loadgoal(currgoalindex);	
	strSplit(currgoal.goalObjective, splitObjective, ':');
	strSplit(currgoal.postGoalCommand, splitCommand, ':');
}

void Goal::retut()
{
	goalbeftut = currgoalindex;
	currgoalindex = 0;
	currgoal = Loadgoal(0);
	strSplit(currgoal.goalObjective, splitObjective, ':');
	strSplit(currgoal.postGoalCommand, splitCommand, ':');
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
	strSplit(currgoal.goalObjective, splitObjective, ':');
	strSplit(currgoal.postGoalCommand, splitCommand, ':');
	goaldisplayed = 0;
}

void Goal::nextGoal()
{
	currgoalindex++;
	currgoal = Loadgoal(currgoalindex);
	strSplit(currgoal.goalObjective, splitObjective, ':');
	strSplit(currgoal.postGoalCommand, splitCommand, ':');
	goaldisplayed = 0;
}

void Goal::goalcheck()
{
	static int completionFlag = 0; // the target

	//the target
	if (strcmp(splitObjective[0], "enter") == 0)
	{
		if (goaldisplayed)
			completionFlag = 1;
	}
	else if (strcmp(splitObjective[0], "menu") == 0)
	{
		if (strcmp(splitObjective[1], "open") == 0 && menudisplay) completionFlag = 1;
		else if (strcmp(splitObjective[1], "create") == 0 && EDITMODE == CREATE_MODE) completionFlag =  1;
		else if (strcmp(splitObjective[1], "remove") == 0 && EDITMODE == REMOVE_MODE) completionFlag =  1;
		else if (strcmp(splitObjective[1], "move") == 0 && EDITMODE == MOVE_MODE) completionFlag =  1;
	}
	else if (strcmp(splitObjective[0], "check") == 0)
	{
		if (strcmp(splitObjective[1], "inc?") == 0)
		{
			if (strcmp(splitObjective[2], "ch") == 0 && houseBuiltCount - tf >= atoi(splitObjective[3])) completionFlag = 1;
			else if (strcmp(splitObjective[2], "ct") == 0 && player.getTreeCutCount() - tf >= atoi(splitObjective[3])) completionFlag = 1;
			else if (strcmp(splitObjective[2], "ii") == 0 && industry.industryIncome - tf >= atoi(splitObjective[3])) completionFlag = 1;
			else if (strcmp(splitObjective[2], "bi") == 0 && boatIncome - tf >= atoi(splitObjective[3])) completionFlag = 1;
		}
		else if (strcmp(splitObjective[1], "dec?") == 0)
		{
			if (strcmp(splitObjective[2], "ch") == 0 &&  tf - houseBuiltCount >= atoi(splitObjective[3])) completionFlag = 1;
			else if (strcmp(splitObjective[2], "ct") == 0 &&  tf - player.getTreeCutCount() >= atoi(splitObjective[3])) completionFlag = 1;
			else if (strcmp(splitObjective[2], "ii") == 0 &&  tf - industry.industryIncome >= atoi(splitObjective[3])) completionFlag = 1;
			else if (strcmp(splitObjective[2], "ii") == 0 &&  tf - boatIncome >= atoi(splitObjective[3])) completionFlag = 1;
		}
		else if (strcmp(splitObjective[1], "wall") == 0 )
		{
			if (strcmp(splitObjective[2], "<") == 0 && player.getWalls() < atoi(splitObjective[3])) completionFlag = 1;
			else if (strcmp(splitObjective[2], ">") == 0 && player.getWalls() > atoi (splitObjective[3])) completionFlag = 1;
			else if (strcmp(splitObjective[2], "=") == 0 && player.getWalls() == atoi (splitObjective[3])) completionFlag = 1;
			else if (strcmp(splitObjective[2], ">=") == 0 && player.getWalls() >= atoi (splitObjective[3])) completionFlag = 1;
			else if (strcmp(splitObjective[2], "<=") == 0 && player.getWalls() <= atoi (splitObjective[3])) completionFlag = 1;
		}
		else if (strcmp(splitObjective[1], "money") == 0 ) 
		{
			if (strcmp(splitObjective[2], "<") == 0 && player.getmoney() < atol (splitObjective[3])) completionFlag = 1;
			else if (strcmp(splitObjective[2], ">") == 0 && player.getmoney() > atol (splitObjective[3])) completionFlag = 1;
			else if (strcmp(splitObjective[2], "=") == 0 && player.getmoney() == atol (splitObjective[3])) completionFlag = 1;
			else if (strcmp(splitObjective[2], ">=") == 0 && player.getmoney() >= atol (splitObjective[3])) completionFlag = 1;
			else if (strcmp(splitObjective[2], "<=") == 0 && player.getmoney() <= atol (splitObjective[3])) completionFlag = 1;
		}
		else if (strcmp(splitObjective[1], "water") == 0 ) 
		{
			if (strcmp(splitObjective[2], "<") == 0 && player.getwater() < atol (splitObjective[3])) completionFlag = 1;
			else if (strcmp(splitObjective[2], ">") == 0 && player.getwater() > atol (splitObjective[3])) completionFlag = 1;
			else if (strcmp(splitObjective[2], "=") == 0 && player.getwater() == atol (splitObjective[3])) completionFlag = 1;
			else if (strcmp(splitObjective[2], ">=") == 0 && player.getwater() >= atol (splitObjective[3])) completionFlag = 1;
			else if (strcmp(splitObjective[2], "<=") == 0 && player.getwater() <= atol (splitObjective[3])) completionFlag = 1;
		}
		else if (strcmp(splitObjective[1], "wood") == 0 ) 
		{
			if (strcmp(splitObjective[2], "<") == 0 && player.getwood() < atol (splitObjective[3])) completionFlag = 1;
			else if (strcmp(splitObjective[2], ">") == 0 && player.getwood() > atol (splitObjective[3])) completionFlag = 1;
			else if (strcmp(splitObjective[2], "=") == 0 && player.getwood() == atol (splitObjective[3])) completionFlag = 1;
			else if (strcmp(splitObjective[2], ">=") == 0 && player.getwood() >= atol (splitObjective[3])) completionFlag = 1;
			else if (strcmp(splitObjective[2], "<=") == 0 && player.getwood() <= atol (splitObjective[3])) completionFlag = 1;
		}
		else if (strcmp(splitObjective[1], "produce") == 0 ) 
		{
			if (strcmp(splitObjective[2], "<") == 0 && player.getproduce() < atol (splitObjective[3])) completionFlag = 1;
			else if (strcmp(splitObjective[2], ">") == 0 && player.getproduce() > atol (splitObjective[3])) completionFlag = 1;
			else if (strcmp(splitObjective[2], "=") == 0 && player.getproduce() == atol (splitObjective[3])) completionFlag = 1;
			else if (strcmp(splitObjective[2], ">=") == 0 && player.getproduce() >= atol (splitObjective[3])) completionFlag = 1;
			else if (strcmp(splitObjective[2], "<=") == 0 && player.getproduce() <= atol (splitObjective[3])) completionFlag = 1;
		}
		else if (strcmp(splitObjective[1], "eco") == 0 ) 
		{
			if (strcmp(splitObjective[2], "<") == 0 && player.getecoMeter() < atoi (splitObjective[3])) completionFlag = 1;
			else if (strcmp(splitObjective[2], ">") == 0 && player.getecoMeter() > atoi (splitObjective[3])) completionFlag = 1;
			else if (strcmp(splitObjective[2], "=") == 0 && player.getecoMeter() == atoi (splitObjective[3])) completionFlag = 1;
			else if (strcmp(splitObjective[2], ">=") == 0 && player.getecoMeter() >= atoi (splitObjective[3])) completionFlag = 1;
			else if (strcmp(splitObjective[2], "<=") == 0 && player.getecoMeter() <= atoi (splitObjective[3])) completionFlag = 1;
		}
		else if (strcmp(splitObjective[1], "level") == 0 && player.getplayerLevel() == atoi(splitObjective[2])) completionFlag = 1;
		else if (strcmp(splitObjective[1], "puzzle") == 0 && player.getPuzzleStatus() == atoi(splitObjective[2])) completionFlag = 1;
	}

	//goalcompleted: execute post goal commands and proceed to the next goal
	if (completionFlag)
	{
		int nflag = 1;

		//executing post goal commands
		if (strcmp(splitCommand[0], "null"))
		{
			if (strcmp(splitCommand[0], "set") == 0) // set a variable
			{
				if (strcmp(splitCommand[1], "tf") == 0)
				{
					if (strcmp(splitCommand[2],"ch") == 0) tf = houseBuiltCount;
					else if (strcmp(splitCommand[2],"ct") == 0) tf = player.getTreeCutCount();
					else if (strcmp(splitCommand[2],"ii") == 0) tf = industry.industryIncome;
					else if (strcmp(splitCommand[2],"bi") == 0) tf = boatIncome;
				}
				else if (strcmp(splitCommand[1], "pos") == 0)
				{
					if (strcmp(splitCommand[2], "i") == 0)
					{
						originX = +200 -industry.industry_x;
						originY = +200 -industry.industry_y;
					}
					else if (strcmp(splitCommand[2], "b") == 0)
					{
						originX = +200-boat.boat_x;
						originY = +200 -boat.boat_y;
					}
					else if (strcmp(splitCommand[2], "z") == 0)
					{
						originX = +200-well.access(1);
						originY = +200 -well.access(2);
					}
					else
					{
						originX = atoi(splitCommand[2]);
						originY = atoi(splitCommand[3]);
					}
				}
				else if (strcmp(splitCommand[1], "money") == 0)
				{
					if (strcmp(splitCommand[2], "=")) player.setmoney(atol(splitCommand[3]));
					else if (strcmp(splitCommand[2], "+")) player.setmoney(player.getmoney() + atol(splitCommand[3]));
					else if (strcmp(splitCommand[2], "-")) player.setmoney(player.getmoney() - atol(splitCommand[3]));
				}
				else if (strcmp(splitCommand[1], "water")== 0)
				{
					if (strcmp(splitCommand[2], "=")) player.setwater(atol(splitCommand[3]));
					else if (strcmp(splitCommand[2], "+")) player.setwater(player.getwater() + atol(splitCommand[3]));
					else if (strcmp(splitCommand[2], "-")) player.setwater(player.getwater() - atol(splitCommand[3]));
				}
				else if (strcmp(splitCommand[1], "produce")== 0)
				{
					if (strcmp(splitCommand[2], "=")) player.setproduce(atol(splitCommand[3]));
					else if (strcmp(splitCommand[2], "+")) player.setproduce(player.getproduce() + atol(splitCommand[3]));
					else if (strcmp(splitCommand[2], "-")) player.setwater(player.getproduce() - atol(splitCommand[3]));
				}
				else if (strcmp(splitCommand[1], "wood")== 0)
				{
					if (strcmp(splitCommand[2], "=")) player.setwood(atol(splitCommand[3]));
					else if (strcmp(splitCommand[2], "+")) player.setwood(player.getwood() + atol(splitCommand[3]));
					else if (strcmp(splitCommand[2], "-")) player.setwood(player.getwood() - atol(splitCommand[3]));
				}
				else if (strcmp(splitCommand[1], "well") == 0) player.wellEnabled = atoi(splitCommand[2]);
			}
			else if (strcmp(splitCommand[0], "award") == 0)
			{
				player.setmoney(player.getmoney() + atol(splitCommand[1]));
				player.setwood(player.getwood() + atol(splitCommand[2]));
				player.setproduce(player.getproduce() + atol(splitCommand[3]));
				player.setwater(player.getwater() + atol(splitCommand[4]));
			}
			else if (strcmp(splitCommand[0], "end") == 0)
			{
				nflag = 0;
			}
		}

		if (nflag)
		{
			completionFlag = 0;
			nextGoal();
		}
	}
}

#endif
