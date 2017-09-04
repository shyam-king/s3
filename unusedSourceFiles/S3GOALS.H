#ifndef S3GOALS_H
#define S3GOALS_H

class goals{
	char title[40];
	char message[10][80];
	int message_length;
	int image_index;
	int copyflag;
	int currgoalindex;
	int nextgoalindex;

	int tutorial_begins_on;
	int tutorial_ends_on;
	int tf;


	public:
	goals()
	{
		strcpy(title, "~~WELCOME TO ATLANTIS~~");
		strcpy(message[0], "Welcome to Atlantis.");
		strcpy(message[1], "Press enter to start the tutorial.");
		message_length = 2;
		image_index = 0;

		tutorial_begins_on = 1;
		copyflag = 1;
		currgoalindex = 0;
		nextgoalindex = 1;

		goaldisplayed = 0;
	}

	int currentGoalIndex();
	int nextGoalIndex();
	void goalcheck();
	char *getTitle();
	char *getMessage(int n);
	int getMessageLength();
	int getImage();

	void retut();
	void setGoalIndex(int);

} goal, t_goal;

int GOALS_TUTORIAL = 0;

void goals::retut()
{
	currgoalindex = 0;
	goaldisplayed = 1;
	GOALS_TUTORIAL = 1;
}

char *goals::getTitle()
{
	return title;
}

char *goals::getMessage(int n)
{
	return message[n];
}

int goals::getMessageLength()
{
	return message_length;
}

int goals::getImage()
{
	return image_index;
}

int goals::currentGoalIndex()
{
	return currgoalindex;
}

int goals::nextGoalIndex()
{
	return nextgoalindex;
}

void goals::setGoalIndex(int a)
{
	currgoalindex = a;	
}
void goals::goalcheck()
{
	int i;
	int f1, f2;
	switch (currgoalindex)
	{
		case 0: 
			nextgoalindex = 1;
			if (goaldisplayed) 
			{
				currgoalindex = nextgoalindex; goaldisplayed = 0;
				// changing the messages and stuff
				strcpy(title, "~~KNOW YOUR ICONS~~");
				strcpy(message[0], "This is the menu icon.");
				strcpy(message[1], "Click in it to view the different");
				strcpy(message[2], "options.");
				strcpy(message[3], "Click on it again to close it later.");

				message_length = 4;
				image_index = 3;
			}
			break;
		case 1:
			nextgoalindex = 2;
			if (menudisplay) 
			{
				currgoalindex = nextgoalindex; goaldisplayed = 0;
				strcpy(title, "~~KNOW YOUR ICONS~~");
				strcpy(message[0], "This is the Create icon.");
				strcpy(message[1], "You can use this to build");
				strcpy(message[2], "houses, to collect");
				strcpy(message[3], "money, resources, etc.");

				message_length = 4;
				image_index = 4;
			}
			break;
		case 2:
			nextgoalindex = 3;
			if (goaldisplayed) 
			{
				currgoalindex = nextgoalindex; goaldisplayed = 0;
				strcpy(title, "~~KNOW YOUR ICONS~~");
				strcpy(message[0], "This is the Remove Icon."); 
				strcpy(message[1], "You cna use this to cut"); 
				strcpy(message[2], "trees and remove houses."); 

				message_length = 3;
				image_index  =5;
			}
			break;
		case 3:
			nextgoalindex = 4;
			if (goaldisplayed)
			{
				currgoalindex = nextgoalindex; goaldisplayed = 0;
				strcpy(title, "~~KNOW YOUR ICONS~~");
				strcpy(message[0], "This is the Goal Icon."); 
				strcpy(message[1], "Click this to view the current goal."); 

				message_length = 2;
				image_index = 5;
			}

			break;
		case 4:
			nextgoalindex = 5;
			if (goaldisplayed)
			{
				currgoalindex = nextgoalindex; goaldisplayed = 0;
				strcpy(title, "~~KNOW YOUR ICONS~~");
				strcpy(message[0], "This is the Help Icon."); 
				strcpy(message[1], "Click on this to KNOW YOUR"); 
				strcpy(message[2], "ICONS"); 

				message_length = 3;
				image_index = 7;
			}
			break;
		case 5:
			nextgoalindex = 6;
			if (goaldisplayed) 
			{
				currgoalindex = nextgoalindex; goaldisplayed = 0;
				strcpy(title, "~~KNOW YOUR ICONS~~");
				strcpy(message[0], "This is the Exit Icon."); 
				strcpy(message[1], "Use this to return to menu and"); 
				strcpy(message[2], "exit the create or remove mode."); 

				message_length = 3;
				image_index = 8;
			}
			break;
		case 6:
			nextgoalindex = 7;
			if (goaldisplayed)
			{
				currgoalindex = nextgoalindex; goaldisplayed =0;
				strcpy(title, "~~KNOW YOUR ICONS~~");
				strcpy(message[0], "This is the Money Icon."); 
				strcpy(message[1], "This shows the amount of money");
				strcpy(message[2], "you currently have.");

				message_length = 3;
				image_index = 1;
			}
			break;
		case 7:
			nextgoalindex = 8;
			if (goaldisplayed)
			{
				currgoalindex = nextgoalindex; goaldisplayed = 0;
				strcpy(title, "~~KNOW YOUR ICONS~~");
				strcpy(message[0], "This is the Resources Icon."); 
				strcpy(message[1], "This is the total amount of");
				strcpy(message[2], "resources you have.");

				message_length = 3;
				image_index = 2;
			}
			break;
		case 8:
			nextgoalindex = 9;
			if (goaldisplayed)
			{
				currgoalindex = nextgoalindex; goaldisplayed = 0;
				strcpy(title, "~~KNOW YOUR ICONS~~");
				strcpy(message[0], "This is the Produce Icon."); 
				strcpy(message[1], "This is the total amount of Produce");
				strcpy(message[2], "you have. ");

				message_length = 3;
				image_index = 9;
			}
			break;
		case 9:
			nextgoalindex = 10;
			if (goaldisplayed)
			{
				currgoalindex =  nextgoalindex; goaldisplayed = 0;
				strcpy(title, "~~TUTORIALS~~");
				strcpy(message[0], "Let us begin your tutorial:");
				strcpy(message[1], "Press the create icon to enable");
				strcpy(message[2], "create mode.");

				message_length = 3;
				image_index = 4;

				if (GOALS_TUTORIAL)
				{ goal = t_goal;
					GOALS_TUTORIAL = 0;
				}
			}
			break;
		case 10:
			nextgoalindex = 11;
			if (EDITMODE == CREATE_MODE) 
			{ 
				currgoalindex = nextgoalindex; goaldisplayed = 0; 
				strcpy(title, "~~TUTORIALS~~");
				strcpy(message[0], "Click on an empty plot to build a");
				strcpy(message[1], "house");
				strcpy(message[2], "(Houses generate money)");

				message_length = 3;
				image_index = 0;

				tf = houseBuiltCount;
			}
			break;
		case 11:
			/*
				liveHouseCount = 0;
				for (i = 0; i < nhouses; i++)
				if (map_houses[i].level) liveHouseCount++;
				if (liveHouseCount - houseCount >= 1) {houseCount = liveHouseCount; goalcounter++; goaldisplayed = 0;}
				*/
			nextgoalindex = 12;

			if (houseBuiltCount - tf >= 1)
			{
				currgoalindex = nextgoalindex;
				strcpy(title, "~~TUTORIALS~~");
				strcpy(message[0], "Good. Now choose the remove icon.");

				message_length = 1;
				image_index = 5;

				goaldisplayed = 0;
			}

			break;
		case 12:
			nextgoalindex = 13;
			if (EDITMODE == REMOVE_MODE) 
			{
				currgoalindex = nextgoalindex; goaldisplayed = 0;
				strcpy(title, "~~TUTORIALS~~");
				strcpy(message[0], "Good. Now click on a treee to remove it.");
				strcpy(message[1], "(CUtting trees yield resources but creates");
				strcpy(message[2], "an unbalance in your ecosystem)");

				message_length = 3;
				image_index = 0;

				tf = treeCutCount;
			}
			break;
		case 13:
			/*
				liveTreeCount = 0;
				for (i = 0; i < ntrees; i++)
				if (map_trees[i].cutdown == 0) liveTreeCount ++;
				if (treeCount - liveTreeCount >= 1) {treeCount = liveTreeCount;goalcounter++; goaldisplayed = 0;}
				*/

			nextgoalindex = 14;

			if (treeCutCount - tf >= 1)
			{
				currgoalindex = nextgoalindex;
				strcpy(title, "~~TUTORIALS~~");
				strcpy(message[0], "Dont\'t cut too many trees.");
				strcpy(message[1], "Try to maintain the balance of");
				strcpy(message[2], "ecosystem");

				message_length = 3;
				image_index = 0;

				goaldisplayed = 0;
				f1 = f2 = 0 ;
			}

			break;
		case 14:
			nextgoalindex = 15;
			if (goaldisplayed) {
				if (originX + industry.industry_x > SCREEN_W-200) {originX -= 100; animate = 1;}
				else if (originX + industry.industry_x < 200) {originX += 100;animate = 1;}
				else f1 = 1;

				if (originY + industry.industry_y > SCREEN_H-200) {originY -= 100; animate = 1;}
				else if (originY + industry.industry_y < 200) {originY += 100; animate = 1;}
				else f2 = 1;
			}
			if (f2 && f1) 
			{
				currgoalindex = nextgoalindex;goaldisplayed = 0;
				strcpy(title, "~~TUTORIALS~~");
				strcpy(message[0], "This is the industry. ");
				strcpy(message[1], "You can use your resources to");
				strcpy(message[2], "get produce from here.");

				message_length = 3;
				image_index = 0;

				strcpy(tsstr, "Goal passed from panning!");
				tsval = 2;
			}
			break;
		case 15:
			nextgoalindex = 17;
			strcpy(tsstr, "It should work!");
			if (goaldisplayed) 
			{
				currgoalindex = nextgoalindex; goaldisplayed = 0; tf = treeCutCount;
				strcpy(title, "~~GOAL: NICE AND TIDY~~");
				strcpy(message[0], "Cut 5 trees to gain some");
				strcpy(message[1], "resources for Industry");

				message_length = 2;
				image_index = 0;
			}
			break;
		case 17:
			nextgoalindex = 18;
			strcpy(tsstr, "The final");

			if (treeCutCount - tf >= 5)
			{
				currgoalindex = nextgoalindex;
				strcpy(title, "~~GOAL: NICE AND TIDY~~");
				strcpy(message[0], "Now use the resources to collect produce");
				strcpy(message[1], "from the Industry. Go to create mode");
				strcpy(message[2], "and click on Industry.");

				message_length = 3;
				image_index = 0;

				goaldisplayed = 0;
			}

			break;
		case 18:
			nextgoalindex = 19;
			if (industry.industryIncome > 0) 
			{
				currgoalindex = nextgoalindex; goaldisplayed = 0;
				strcpy(title, "~~GOAL: ~~");
				strcpy(message[0], "Good. Now you have some produce");
				strcpy(message[1], "to sell.");

				message_length = 2;
				image_index = 0;
			} 
			break;
		case 19:
			nextgoalindex = 21;
			//panning towards the boat
			{
				int f1, f2;
				f1 = f2 = 0;
				if (goaldisplayed) {
					if (originX + boat.boat_x > SCREEN_W-200) {originX -= 100; animate = 1;}
					else if (originX + boat.boat_x < 200) {originX += 100;animate = 1;}
					else f1 = 1;

					if (originY + boat.boat_y > SCREEN_H-200) {originY -= 100; animate = 1;}
					else if (originY + boat.boat_y < 200) {originY += 100; animate = 1;}
					else f2 = 1;
				}
				if (f2 && f1 && goaldisplayed)
				{
					currgoalindex = nextgoalindex; goaldisplayed = 0;
					strcpy(title, "~~GOAL: ~~");
					strcpy(message[0], "This is the Boat.");
					strcpy(message[1], "Go to create mode and click on it");
					strcpy(message[2], "to trade some of the produce and");
					strcpy(message[3], "get some money.");

					message_length = 4;
					image_index = 0;

				} // next part
			}
			break;
		case 21:
			nextgoalindex = 22;
			if (boatIncome > 0) 
			{
				currgoalindex = nextgoalindex; goaldisplayed = 0;
				strcpy(title, "~~GOAL: ~~");
				strcpy(message[0], "Good money.");
				message_length = 1;
				image_index = 0;
			}
			break;
		case 22:
			nextgoalindex = 23;
			if (goaldisplayed)
			{
				currgoalindex = nextgoalindex; goaldisplayed = 0;
				strcpy(title, "~~GOAL: ~~");
				strcpy(message[0], "Now go build some houses with");
				strcpy(message[1], "the money you\'ve earned.");

				message_length = 2;
				image_index = 0;

				tf = houseBuiltCount;

				/*for (i = 0; i < nhouses; i++)
				  if (map_houses[i].level) liveHouseCount++;
				  houseCount = liveHouseCount;*/
			}
			break;
		case 23:
			/*liveHouseCount = 0;
			  for (i = 0; i < nhouses; i++)
			  if (map_houses[i].level) liveHouseCount++;
			  if (liveHouseCount - houseCount >= 3)
			  {
			  houseCount = liveHouseCount;
			  goalcounter++;
			  goaldisplayed = 0;

			  liveTreeCount = 0;
			  for (i = 0; i < ntrees; i++)
			  if (map_trees[i].cutdown == 0) liveTreeCount ++;

			  treeCount = liveTreeCount;

			  }*/
			nextgoalindex = 24;

			if (houseBuiltCount - tf >= 3)
			{
				currgoalindex = nextgoalindex;
				strcpy(title, "~~GOAL: ~~");
				strcpy(message[0], "You are out of resources!");
				strcpy(message[1], "Cut trees to gain some!");

				message_length = 2;
				image_index = 0;

				goaldisplayed = 0;
				tf = treeCutCount;
			}

			break;
		case 24:
			nextgoalindex = 25;

			//liveTreeCount = 0;
			//for (i = 0; i < ntrees; i++)
			if (ecoMeter <= 40 || treeCutCount - tf >= 2)
			{
				currgoalindex = nextgoalindex;
				strcpy(title, "~~GOAL: ~~");
				strcpy(message[0], "I guess you\'ve cut too many");
				strcpy(message[1], "trees. The ecosystem of your");
				strcpy(message[2], "kingdom is out of balance.");
				strcpy(message[3], "Plant some trees. This ecobar");
				strcpy(message[4], "will give you an alert, if the");
				strcpy(message[5], "ecosystem is out of balance.");

				message_length = 6;
				image_index = 0;

				goaldisplayed = 0;
			}
			break;
		case 25:
			nextgoalindex = 26;
			if (goaldisplayed)
			{
				currgoalindex = nextgoalindex;
				strcpy(title, "~~GOAL: ~~");
				strcpy(message[0], "Use the well in the South West");
				strcpy(message[1], "to collect some water to plant some");
				strcpy(message[2], "trees and replenish your ecosystem.");
				strcpy(message[3], "After collecting water click on a");
				strcpy(message[4], "fallen tree in create mode to");
				strcpy(message[5], "replenish it.");

				message_length = 6;
				image_index =  10;


				goaldisplayed = 0;

				tf = treeCutCount;

				/*
					liveTreeCount = 0;
					for (i = 0; i < ntrees; i++)
					if (map_trees[i].cutdown == 0) liveTreeCount ++;

					treeCount = liveTreeCount;*/
			}
			break;
		case 26:
			nextgoalindex = 27;
			/*
				liveTreeCount = 0;
				for (i = 0; i < ntrees; i++)
				if (map_trees[i].cutdown == 0) liveTreeCount ++;
				if (liveTreeCount - treeCount >= 5) {treeCount = liveTreeCount; goalcounter++; goaldisplayed = 0;}*/

			if (treeCutCount - tf <= -5)
			{
				currgoalindex = nextgoalindex;
				strcpy(title, "~~GOAL: ~~");
				strcpy(message[0], "Good. Never let your ecobar reach");
				strcpy(message[1], "Zero or else your kingdom may be in");
				strcpy(message[2], "extreme danger.");

				message_length = 3;
				image_index = 0;

				goaldisplayed = 0;
			}

			break;
		case 27:
			nextgoalindex = 28; 
			if (goaldisplayed)
			{
				currgoalindex = nextgoalindex;
				strcpy(title, "~~GOAL: LEVEL UP~~");
				strcpy(message[0], "Now it\'s time for you to level up!");

				message_length =1;
				image_index = 0;

				goaldisplayed = 0;
			}
			break;
		case 28:
			nextgoalindex = 30;
			if (player.getplayerLevel() == 2)
			{
				player.setmoney(player.getmoney()+ 2000);
				player.setwood(player.getwood()+ 2000);
				player.setwater(player.getwater()+ 25);
				goaldisplayed = 0;

				currgoalindex = nextgoalindex;
				strcpy(title, "~~GOAL: LEVEL UP~~");
				strcpy(message[0], "Congrats you\'ve levelled up!");
				strcpy(message[1], "Here are some resources to help");
				strcpy(message[2], "you with your kingdom\'s development.");

				message_length = 3;
				image_index = 0;
			}
			break;
		case 30:
			nextgoalindex = 31;
			if (goaldisplayed)
			{
				currgoalindex = nextgoalindex;
				strcpy(title, "~~GOAL: LEVEL UP~~");
				strcpy(message[0], "Now you can upgrade your houses to the");
				strcpy(message[1], "next storey.");

				message_length = 2;
				image_index = 0;

				goaldisplayed = 0;
			}
			break;
		case 31:
			nextgoalindex = 32;
			if (goaldisplayed)
			{
				currgoalindex = nextgoalindex;
				strcpy(title, "~~GOAL: LEVEL UP~~");
				strcpy(message[0], "Now try to develop your kingdom.");
				strcpy(message[1], "Good luck!");

				message_length = 2;
				image_index = 0;

				goaldisplayed = 0;
			}
			break;
	}




}


/* Goals have been made much more efficent by writing every message and details into switch casae construct making it memory efficient on the vaiables side */

#endif
