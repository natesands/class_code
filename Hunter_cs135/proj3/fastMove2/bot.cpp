/*

AUTHOR: Nathaniel J. Sands
COURSE: CSCI-135
Instructor: Prof. Shankar
Assignment: Project 3

Controls bot logic for MCC

*/
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
  float debrisDensity;
};

struct Robot {
  Job job;
  bool isBroken;
  int brokenBotAssigned;
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
int NUM_BROKEN_BOTS = 0;
double MPR;
float CRITICAL_CAPACITY;

/* FUNCTIONS */
int distance(Loc a, Loc b);
int abVal(int x);
Action nextRepairAction(int id,Loc botLoc, Area area);
Action moveFromTo(Loc a,Loc b);
Action randomMove();
void unassign(int botId);
void assignRepair(int id, Loc jobLoc, int brokenBot);
void assignDebris(int id, Loc jobLoc);
int findBrokenBot(Area area);
Loc nearestDebris(Loc loc, Area area);
void getUDLR(Loc loc,Loc &up,Loc &down,Loc &left,Loc &right);
void refreshMap(Area area, ostream &log);
int findNearestBot(JobType jobtype,Loc loc,Area area);
bool inRange(Loc loc);
//float calcDebrisDensity (Loc loc, Area area);
float calcDebrisDensity (Loc loc);
Action fastMoveFromTo(Loc a, Loc b);
/* Initialization procedure, called when the game starts: */
void onStart(int num, int rows, int cols, double mpr,
             Area &area, ostream &log)
{
	NUM = num;   // save the number of robots and the map dimensions
	ROWS = rows;
	COLS = cols;
  MPR = mpr;
  CRITICAL_CAPACITY = NUM * (1.0-MPR);
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

  refreshMap(area, log); 

  //if bot is assigned repair job
  //return next repair action
  if (bot[id].job.type == REPAIR_BOT) {
    return nextRepairAction(id,loc,area);
  }
  //if there are unassigned broken bots
  if (UNASSIGNED_BROKEN_BOTS > 0 && !bot[id].isBroken) {
    int brokenBot = findBrokenBot(area); 
    if (brokenBot != NONE) {
      unassign(id);
      Loc brokenBotLoc;
      brokenBotLoc.r = area.locate(brokenBot).r;
      brokenBotLoc.c = area.locate(brokenBot).c;
      assignRepair(id, brokenBotLoc, brokenBot);
      UNASSIGNED_BROKEN_BOTS--;
      return nextRepairAction(id,loc,area);
    }
  }
  if (bot[id].isBroken) return REPAIR_UP;

  //if there is debris at bots current location
  //return COLLECT
  if (area.inspect(row,col) == DEBRIS)
    return COLLECT;

  //Assert: There is no debris at location

  if (NUM_BROKEN_BOTS > (int) CRITICAL_CAPACITY) return REPAIR_UP;
  
  //if bot had collect job here, job is finished
  //so unassign
  if (bot[id].job.loc.r == loc.r &&
        bot[id].job.loc.c == loc.c) {
    unassign(id);
  }
  if (bot[id].job.type == COLLECT_DEBRIS) {
    if (area.inspect(bot[id].job.loc.r, bot[id].job.loc.c) != DEBRIS){
      unassign(id);
    }
    if (map[bot[id].job.loc.r][bot[id].job.loc.c].hasBrokenBot) {
      unassign(id);
    }
    if (map[bot[id].job.loc.r][bot[id].job.loc.c].hasBot) {
      unassign(id);
    }
  }
  //Assert: if bot has job, it is at another location
  if (bot[id].job.type == COLLECT_DEBRIS) {
    return fastMoveFromTo(loc,bot[id].job.loc);
  }
  //Assert: bot has no job assigned.
  //if there are unassigned debris fields
  //assign debris job
  if (UNASSIGNED_DEBRIS > 0) {
    Loc debrisLoc = nearestDebris(loc,area);
    assignDebris(id,debrisLoc);
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
  NUM_BROKEN_BOTS++;
  unassign(id);
  assignDebris(id,loc);

  int repairBot;
  repairBot = findNearestBot(UNASSIGNED, loc, area);
  
  if (repairBot == NONE) {
    log << "No unassigned Bot." << endl;
    repairBot = findNearestBot(COLLECT_DEBRIS, loc,area);
  }
    
  if (repairBot == NONE) {
    log << "No collection bot avail." << endl; 
    UNASSIGNED_BROKEN_BOTS++;
    log << "UNASSIGNED BROKEN BOTS = " << UNASSIGNED_BROKEN_BOTS << endl; 
  }
  
  if (repairBot != NONE) {
    unassign(repairBot);
  log << "Assigned bot " << repairBot << endl;
    assignRepair(repairBot, loc, id);
  }
}

void onClockTick(int time, ostream &log) {
	if (time % 100 == 0) log << time << " ";
}
//locates debris and robots on map
//totals how many debris locations
//are unassigned
//updates UNASSIGNED_DEBRIS
void refreshMap(Area area,ostream &log) {
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
Action nextRepairAction(int id,Loc botLoc,Area area) {
  //assert: bot has been assigned to the location
  //of the broken bot
  //if the repair bot is farther than 1 square away
  //move one step closer
  Loc repairBotLoc;
  repairBotLoc.r = area.locate(id).r;
  repairBotLoc.c = area.locate(id).c;
/*
  if (NUM_BROKEN_BOTS < (int) CRITICAL_CAPACITY) {
    if (area.inspect(repairBotLoc) == DEBRIS) return COLLECT;
  }*/
    
 
  if (distance(botLoc,bot[id].job.loc) > 1)
    return fastMoveFromTo(botLoc,bot[id].job.loc);

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
  NUM_BROKEN_BOTS--;

  int repairedBot = bot[id].brokenBotAssigned;
  bot[repairedBot].isBroken = false;
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
      bot[botId].brokenBotAssigned = NONE;
      break;
    case UNASSIGNED:
      break;
  } 
}

void assignRepair(int id, Loc jobLoc, int brokenBot) {
      bot[id].job.type = REPAIR_BOT;
      bot[id].job.loc.r = jobLoc.r;
      bot[id].job.loc.c = jobLoc.c;
      bot[id].brokenBotAssigned = brokenBot;
      map[jobLoc.r][jobLoc.c].repairBotAssigned = true;
}

void assignDebris(int id, Loc jobLoc) {
      bot[id].job.type = COLLECT_DEBRIS;
      bot[id].job.loc.r = jobLoc.r;
      bot[id].job.loc.c = jobLoc.c;
      map[jobLoc.r][jobLoc.c].debrisAssigned = true;
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
int findBrokenBot(Area area) {
  for (int id = 0; id < NUM; id++) {
    Loc botLoc;
    botLoc.r = area.locate(id).r;
    botLoc.c = area.locate(id).c;
    if (bot[id].isBroken && map[botLoc.r][botLoc.c].repairBotAssigned == false) {
      return id;
    }
  }
  return NONE;
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

bool inRange(Loc loc) {
  return(loc.r >=0 && loc.c >=0 && loc.r < ROWS && loc.c < COLS);
}


float calcDebrisDensity (Loc loc) {

  int numSquares = 0;
  int numDebris = 0;
  int rad = 2; //radius
  float density;
  Loc mapLoc;

  for (int row = loc.r - rad; row <= loc.r + rad; row++) {
    for (int col = loc.c - rad; col <= loc.c + rad; col++) {
      mapLoc.r = row; mapLoc.c = col;
      if (inRange(mapLoc)) {
        numSquares++;
        if (map[mapLoc.r][mapLoc.c].hasDebris) {
          numDebris++;
        }
      }
    }
  }

  density = (float) numDebris / (float) numSquares;
  return density;
}
Action fastMoveFromTo(Loc a, Loc b) {
  
  Loc up, down, left, right;
  getUDLR(a, up,down,left,right);
  Loc UDLR[4] = {up, down, left, right};

  int goodMoves = 0;
  int okMoves = 0;
  Loc good[4];
  Loc ok[4];

  for (int i = 0; i < 4; i++) {
    //if move is closer and has no debris and no bot, it is a good move
    if (distance(UDLR[i], b) < distance(a,b) && map[UDLR[i].r][UDLR[i].c].hasDebris == false 
        && map[UDLR[i].r][UDLR[i].c].hasBot == false) {
      good[goodMoves].r=UDLR[i].r;
      good[goodMoves].c=UDLR[i].c;
      goodMoves++;
    }
    //if move is closer but has debris but no bot, it is an ok move
    if (distance(UDLR[i], b) < distance(a,b) && map[UDLR[i].r][UDLR[i].c].hasDebris == true 
        && map[UDLR[i].r][UDLR[i].c].hasBot == false) {
      ok[okMoves].r=UDLR[i].r;
      ok[okMoves].c=UDLR[i].c;
      okMoves++;
    }
  }
  
  if (goodMoves > 0) {
    int index = 0;
    float density, minDensity;
    minDensity = 2.0;
    for (int k = 0; k < goodMoves; k++) {
      density = calcDebrisDensity(good[k]);
      if (density < minDensity) {
        index = k;
        minDensity = density;
      }
    }
    if (good[index].r == up.r && good[index].c == up.c) return UP;
    if (good[index].r == down.r && good[index].c == down.c) return DOWN;
    if (good[index].r == left.r && good[index].c == left.c) return LEFT;
    if (good[index].r == right.r && good[index].c == right.c) return RIGHT;
  }

  if (okMoves > 0) {
    int index = 0;
    float density, minDensity;
    minDensity = 2.0;
    for (int k = 0; k < okMoves; k++) {
      density = calcDebrisDensity(ok[k]);
      if (density < minDensity) {
        index = k;
        minDensity = density;
      }
    }
    if (ok[index].r == up.r && ok[index].c == up.c) return UP;
    if (ok[index].r == down.r && ok[index].c == down.c) return DOWN;
    if (ok[index].r == left.r && ok[index].c == left.c) return LEFT;
    if (ok[index].r == right.r && ok[index].c == right.c) return RIGHT;
  }

  return moveFromTo(a,b);
}   
 

