
#include <cstdlib>
#include <iostream>
#include "bot.h"

using namespace std;

/* DATA TYPES */

enum JobType {COLLECT_DEBRIS, REPAIR_BOT, UNASSIGNED};

/* STRUCTS */

struct Job {
  Loc loc;
  JobType type;
};

struct MapSquare {
  bool hasDebris;
  bool debrisAssigned;
  bool hasBot;
  bool hasBrokenBot;
  bool repairBotAssigned;
};

struct Robot {
  Job job;
  bool isBroken;
};

/* CONSTS */

const int MAX_ROBOT_NUM = 50;
const int MAX_COLS = 40;
const int MAX_ROWS = 40;
const int NONE = 999;

/* GLOBALS */

int NUM;          // to remember number of robots
int ROWS, COLS;   // map dimensions
Robot bot[MAX_ROBOT_NUM];
MapSquare map[MAX_ROWS][MAX_COLS];
int UNASSIGNED_BROKEN_BOTS = 0;
int UNASSIGNED_DEBRIS;

/* FUNCTIONS */
int distance(Loc a, Loc b);
int abVal(int x);
Action nextRepairAction(int id,Loc botLoc);
Action moveFromTo(Loc a,Loc b);
Action randomMove();
void unassign(int botId);
void assign(int id, JobType jobType, Loc jobLoc);
Loc findBrokenBot();
Loc nearestDebris(Loc loc, Area area);
void getUDLR(Loc loc,Loc &up,Loc &down,Loc &left,Loc &right);
void refreshMap(Area area);
int findNearestBot(JobType jobtype,Loc loc,Area area);


/* Initialization procedure, called when the game starts: */
void onStart(int num, int rows, int cols, double mpr,
             Area &area, ostream &log)
{
	NUM = num;   // save the number of robots and the map dimensions
	ROWS = rows;
	COLS = cols;

  //initialize bots
  for (int id = 0; id < NUM; id++) {
    bot[id].job.type = UNASSIGNED;
    bot[id].isBroken = false;
  }

  for (int r=0; r < ROWS; r++) {
    for (int c=0; c < COLS; c++) {
      map[r][c].hasDebris = false;
      map[r][c].debrisAssigned = false;
      map[r][c].hasBot = false;
      map[r][c].hasBrokenBot = false;
      map[r][c].repairBotAssigned = false;
    }
  }
      
	log << "Start!" << endl;
}

/* Deciding robot's next move */
Action onRobotAction(int id, Loc loc, Area &area, ostream &log) {

	int row = loc.r; // current row and column
	int col = loc.c;

  refreshMap(area); 

  //if bot is assigned repair job
  //return next repair action
  if (bot[id].job.type == REPAIR_BOT) {
    return nextRepairAction(id,loc);
  }
  //if there are unassigned broken bots
  if (UNASSIGNED_BROKEN_BOTS > 0 && !bot[id].isBroken) {
    unassign(id);
    Loc brokenBotLoc = findBrokenBot(); 
    assign(id,REPAIR_BOT,brokenBotLoc);
    UNASSIGNED_BROKEN_BOTS--;
    return nextRepairAction(id,loc);
  }
  
  //if there is debris at bots current location
  //return COLLECT
  if (area.inspect(row,col) == DEBRIS)
    return COLLECT;

  //Assert: There is no debris at location
  
  //if bot had collect job here, job is finished
  //so unassign
  if (bot[id].job.loc.r == loc.r &&
        bot[id].job.loc.c == loc.c) {
    unassign(id);
  }
  //Assert: if bot has job, it is at another location
  if (bot[id].job.type == COLLECT_DEBRIS) {
    return moveFromTo(loc,bot[id].job.loc);
  }
  //Assert: bot has no job assigned.
  //if there are unassigned debris fields
  //assign debris job
  if (UNASSIGNED_DEBRIS > 0) {
    Loc debrisLoc = nearestDebris(loc,area);
    assign(id,COLLECT_DEBRIS,debrisLoc);
    return moveFromTo(loc,bot[id].job.loc);
  }
  //Assert: bot is unassigned and there is no job
  //to be done 
  //return random move
  return randomMove();
}

//if robot breaks
//set isBroken flag
//assign nearest unassigned bot, or if there are none,
//assign nearest debris collecting bot.
//if none is found, increment UNASSIGNED_BROKEN_BOTS counter
void onRobotMalfunction(int id, Loc loc, Area &area, ostream &log) {
	log << "Robot " << id << " is damaged." << endl;

  bot[id].isBroken = true;

  int repairBot;
  repairBot = findNearestBot(UNASSIGNED, loc, area);

  if (repairBot == NONE) 
    repairBot = findNearestBot(COLLECT_DEBRIS, loc,area);
    
  if (repairBot == NONE)
    UNASSIGNED_BROKEN_BOTS++;

  if (repairBot != NONE) {
    unassign(repairBot);
    assign(repairBot, REPAIR_BOT, loc);
  }
}

void onClockTick(int time, ostream &log) {
	if (time % 100 == 0) log << time << " ";
}
//locates debris and robots on map
//totals how many debris locations
//are unassigned
//updates UNASSIGNED_DEBRIS
void refreshMap(Area area) {
  UNASSIGNED_DEBRIS = 0;

  for (int r = 0; r < ROWS; r++) {
    for (int c = 0; c < COLS; c++) {
      map[r][c].hasBot = false;
      map[r][c].hasBrokenBot = false;
      if (area.inspect(r,c) == DEBRIS) {
        map[r][c].hasDebris = true;
        if (!map[r][c].debrisAssigned) {
           UNASSIGNED_DEBRIS++;
        }
      }
      else {
        map[r][c].hasDebris = false;
      }
    }
  }

  for (int b = 0; b < NUM; b++) {
    map[area.locate(b).r][area.locate(b).c].hasBot = true;
    if (bot[b].isBroken) {
      map[area.locate(b).r][area.locate(b).c].hasBrokenBot = true;
    }
  }
}

//takes id of bot who is assigned repair
//job and returns next move
Action nextRepairAction(int id,Loc botLoc) {
  //assert: bot has been assigned to the location
  //of the broken bot
  //if the repair bot is farther than 1 square away
  //move one step closer
  if (distance(botLoc,bot[id].job.loc) > 1)
    return moveFromTo(botLoc,bot[id].job.loc);

  //if bot is 1 square away, 
  //return repair move aimed at broken bot's square
  Loc up,down,left,right;
  Action repairAction;
  getUDLR(botLoc,up,down,left,right);
  if (bot[id].job.loc.r == up.r &&
        bot[id].job.loc.c == up.c) repairAction = REPAIR_UP;

  if (bot[id].job.loc.r == down.r &&
      bot[id].job.loc.c == down.c) repairAction = REPAIR_DOWN;
  if (bot[id].job.loc.r == left.r &&
      bot[id].job.loc.c == left.c) repairAction = REPAIR_LEFT;
  if (bot[id].job.loc.r == right.r &&
      bot[id].job.loc.c == right.c) repairAction = REPAIR_RIGHT;

  unassign(id);
  return repairAction;
}

//takes int, returns abs value
int abVal(int x) {
    if (x < 0)  x  = -1*x;
    return(x);
}

//takes Loc a and Loc b and
//computes distance btw them
int distance(Loc a, Loc b) {
  int distr, distc;
  distr = abVal(a.r - b.r);
  distc = abVal(a.c - b.c);
  return(distr + distc);
}

//returns next best move to get from
//loc a to loc b
Action moveFromTo(Loc a,Loc b) {
  Action nextStep;
  Loc up,down,left,right;
  int good = 0;
  int ok = 0;
  int bad = 0;
  int worst = 0;

  Action goodMoves[4];
  Action okMoves[4];
  Action badMoves[4];
  Action worstMoves[4];
  
  getUDLR(a,up,down,left,right);
  //evaluate UP 

  if (up.r < 0 ) { //up is a wall
    badMoves[bad] = UP;
    bad++;
  }
  else if (map[up.r][up.c].hasBot) {
    worstMoves[worst] = UP;
    worst++;
  }
  else if ((distance(up,b) < distance(a,b)) &&
     !map[up.r][up.c].hasBot) {
    good[goodMoves] = UP;
    good++;
  }
  else if ((distance(up,b) > distance(a,b)) &&
     !map[up.r][up.c].hasBot) {
    ok[okMoves] = UP;
    ok++;
  }
  
  //evaluate DOWN
  if (down.r > ROWS) { //down is a wall
    badMoves[bad] = DOWN;
    bad++;
  }
  else if (map[down.r][down.c].hasBot) {
    worstMoves[worst] = DOWN;
    worst++;
  }
  else if ((distance(down,b) < distance(a,b)) &&
     !map[down.r][down.c].hasBot) {
    good[goodMoves] = DOWN;
    good++;
  }
  else if ((distance(down,b) > distance(a,b)) &&
     !map[down.r][down.c].hasBot) {
    ok[okMoves] = DOWN;
    ok++;
  }

  //evaluate RIGHT
  if (right.c > COLS) { //right is a wall
    badMoves[bad] = RIGHT;
    bad++;
  }
  else if (map[right.r][right.c].hasBot) {
    worstMoves[worst] = RIGHT;
    worst++;
  }
  else if ((distance(right,b) < distance(a,b)) &&
     !map[right.r][right.c].hasBot) {
    good[goodMoves] = RIGHT;
    good++;
  }
  else if ((distance(right,b) > distance(a,b)) &&
     !map[right.r][right.c].hasBot) {
    ok[okMoves] = RIGHT;
    ok++;
  }
  
  //evaluate LEFT
  if (left.c < 0) { //left is a wall
    badMoves[bad]=LEFT ;
    bad++;
  }
  else if (map[left.r][left.c].hasBot) {
    worstMoves[worst] = LEFT;
    worst++;
  }
  else if ((distance(left,b) < distance(a,b)) &&
     !map[left.r][left.c].hasBot) {
    good[goodMoves] = LEFT;
    good++;
  }
  else if ((distance(left,b) > distance(a,b)) &&
     !map[left.r][left.c].hasBot) {
    ok[okMoves] = LEFT;
    ok++;
  }

  if (good > 0) {
    nextStep = goodMoves[rand() % good];
  }
  else if (ok > 0) {
    nextStep = okMoves[rand() % ok];
  }
  else if (bad > 0) {
    nextStep = badMoves[rand() % bad];
  }
  else if (worst > 0) {
    nextStep = worstMoves[rand() % worst];
  }
  else nextStep = randomMove();

  return(nextStep);
}

//changes job type to unassigned
//removes assignment from map square
void unassign(int botId) {
  int row, col;
  row = bot[botId].job.loc.r;
  col = bot[botId].job.loc.c;

  switch (bot[botId].job.type) {
    case COLLECT_DEBRIS: 
      map[row][col].debrisAssigned = false;
      bot[botId].job.type = UNASSIGNED;
      break;
    case REPAIR_BOT:
      map[row][col].repairBotAssigned = false;
      bot[botId].job.type = UNASSIGNED;
      break;
    case UNASSIGNED:
      break;
  } 
}

//assigns a bot a job at a location
//updates bot's job.type, job.loc
//and updates map square's assigned flag
void assign(int id, JobType jobType, Loc jobLoc) {
  switch (jobType) {
    case COLLECT_DEBRIS:
      bot[id].job.type = jobType;
      bot[id].job.loc.r = jobLoc.r;
      bot[id].job.loc.c = jobLoc.c;
      map[jobLoc.r][jobLoc.c].debrisAssigned = true;
      break;
    case REPAIR_BOT: 
      bot[id].job.type = jobType;
      bot[id].job.loc.r = jobLoc.r;
      bot[id].job.loc.c = jobLoc.c;
      map[jobLoc.r][jobLoc.c].repairBotAssigned = true;
      break;
    case UNASSIGNED:
      break;
  }
}
//assigns four loc variables the coordinates
//of four squares surrounding a loc
void getUDLR(Loc loc,Loc &up,Loc &down,Loc &left,Loc &right){
  up.r = loc.r - 1; 
  up.c = loc.c;
  down.r = loc.r +1; 
  down.c = loc.c;
  left.r = loc.r; 
  left.c = loc.c -1;
  right.r = loc.r; 
  right.c = loc.c +1;
}

//returns random move
Action randomMove() {

		switch(rand() % 4) {
		case 0:
			return LEFT;
		case 1:
			return RIGHT;
		case 2:
			return UP;
		default:
			return DOWN;
		}
}
//called if there are unassigned broken bots
//finds unassigned broken bots and returns location
//otherwise returns {0,0};
Loc findBrokenBot() {
  Loc botLoc;
  for (int row = 0; row < ROWS; row++) {
    for (int col = 0; col < COLS; col++) {
      if (map[row][col].hasBrokenBot && 
        map[row][col].repairBotAssigned == false) {
        botLoc.r = row;
        botLoc.c = col;
        return botLoc;
      }
    }
  }
  //error case
  botLoc.r = 0;
  botLoc.c = 0;
  return botLoc;
} 
//locate nearest unassigned debris
Loc nearestDebris(Loc loc, Area area) {
  int minDist, dist;
  Loc nearest;
  Loc mapLoc;
  minDist = ROWS + COLS + 1;
  for (int r = 0; r < ROWS; r++) {
    for (int c = 0; c < COLS; c++) {
      mapLoc.r = r;
      mapLoc.c = c;
      dist = distance(loc, mapLoc);
      if (area.inspect(r,c) == DEBRIS && !map[r][c].debrisAssigned) {
        if (dist < minDist) {
          minDist = dist;
          nearest = mapLoc;
        }
      }
    }
  }
  return(nearest);
}
//finds closest bot with specified job type
//returns bot's id number
int findNearestBot(JobType jobtype,Loc loc,Area area) {

  int minDist, dist;
  int nearestBot = NONE;
  Loc botLoc;
  minDist = ROWS + COLS + 1;
  
  for (int id = 0; id < NUM; id++) {
    botLoc.r = area.locate(id).r;
    botLoc.c = area.locate(id).c;
    dist = distance(loc, botLoc);
    if (bot[id].job.type == jobtype && dist < minDist && 
          !bot[id].isBroken) {
      minDist = dist;
      nearestBot = id;
    }
  }
  return nearestBot;
}
