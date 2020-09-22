
#include <cstdlib>
#include <iostream>
#include "bot.h"

using namespace std;

/* DATA TYPES */

enum JobType {FIND_DEBRIS,REPAIR_BOT,RANDOM_WALK};
/* STRUCTS */

struct Job {
  Loc loc;
  JobType type;
};  

struct MapSquare {
  bool hasDebris;
  bool assigned;
  int  botAssigned;
  float localDensity;
  bool hasBrokenBot;
  bool hasBot;
};

struct Robot {
  bool hasJob;
  Job  job;
  bool broken;
}; 


/* CONSTS */
const int MAX_ROBOT_NUM = 50;
const int MAX_COLS = 40;
const int MAX_ROWS = 40;
const int NONE = 999;

/* GLOBALS */
int NUM;          // to remember number or robots
int ROWS, COLS;   // map dimensions
Robot bot[MAX_ROBOT_NUM];    //bot data
MapSquare map[MAX_ROWS][MAX_COLS]; //map data
int UNASSIGNED_DEBRIS; //unassigned debris sites

/* FUNCTIONS */
void refreshMap(Area area);
Loc findJob(int botId,Loc botLoc, Area area);
void unassign(int id);
Action nextMove(int id);
void assignJob(int id, Loc botloc, Area area);
Loc nearestDebris(Loc loc, Area area);
int distance(Loc a, Loc b);
int abVal(int x);
Action nextMove(int id,Loc botLoc);
Action stepFromTo(Loc fromLoc, Loc toLoc);
Action randomMove();
void  getUDLR(Loc loc,Loc &up,Loc &down,Loc &left,Loc &right);

/* Initialization procedure, called when the game starts: */
void onStart(int num, int rows, int cols, double mpr,
             Area &area, ostream &log)
{
	NUM = num;   // save the number of robots and the map dimensions
	ROWS = rows;
	COLS = cols;

  //initialize map
  for (int r = 0; r < ROWS; r++) {
    for (int c = 0; c < COLS; c++) {
      map[r][c].assigned = false;
      map[r][c].botAssigned = NONE;
    }
  }
  //initialize bots
  for (int id = 0; id < NUM; id++) {
    bot[id].hasJob = false;
    bot[id].broken = false;
  }
    	
  log << "Start!" << endl;
}

/* Deciding robot's next move */
Action onRobotAction(int id, Loc loc, Area &area, ostream &log) {
	int row = loc.r; // current row and column
	int col = loc.c;
 
  refreshMap(area);

  //if bot is in debris field, collect
	if (area.inspect(row, col) == DEBRIS)
		return COLLECT;
  //assert: there is no debris at bot location
  //if bot had job here, unassign job	
  if (bot[id].hasJob && 
      (bot[id].job.loc.r == loc.r && bot[id].job.loc.c == loc.c)) {
    unassign(id);
  } 

  if (bot[id].hasJob) 
    return(nextMove(id,loc));
  else {
    assignJob(id,loc, area);
    return(nextMove(id,loc));
  }
}

void onRobotMalfunction(int id, Loc loc, Area &area, ostream &log) {
	log << "Robot " << id << " is damaged." << endl;

}

void onClockTick(int time, ostream &log) {
	if (time % 100 == 0) log << time << " ";
}

void refreshMap(Area area) {
  UNASSIGNED_DEBRIS = 0; 
  //find debris and clear hasBot flag
  for (int r = 0; r < ROWS; r++) {
    for (int c = 0; c < COLS; c++) {
      map[r][c].hasBot = false;
      if (area.inspect(r,c) == DEBRIS) {
        map[r][c].hasDebris = true;
        if (!map[r][c].assigned) {
          UNASSIGNED_DEBRIS++;
        }
      }
      else { 
        map[r][c].hasDebris = false;
      }
    }
  }
  //find bots and reset hasBot flag
  for (int b = 0; b < NUM; b++) {
    map[area.locate(b).r][area.locate(b).c].hasBot = true;
  }
    
} 

void unassign(int id) {
  int row, col;
  row  = bot[id].job.loc.r;
  col = bot[id].job.loc.c;

 //unassign robot and map square
  bot[id].hasJob = false;
  map[row][col].assigned = false;
  map[row][col].botAssigned = NONE;
}

void assignJob(int id, Loc botloc, Area area) {
  if (UNASSIGNED_DEBRIS != 0) {
    Loc debrisLoc;
    //find closest, unassigned debris
    debrisLoc = nearestDebris(botloc,area);
    //assign to bot
    bot[id].job.loc = debrisLoc;
    bot[id].hasJob = true;
    bot[id].job.type = FIND_DEBRIS;
    //put assignment on map
    map[debrisLoc.r][debrisLoc.c].assigned = true;
    map[debrisLoc.r][debrisLoc.c].botAssigned = id;
  } 
  else {
    //if there are no jobs, move randomly
    //for one turn, hasJob remains false
    bot[id].job.type = RANDOM_WALK;
  }
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
      if (area.inspect(r,c) == DEBRIS && !map[r][c].assigned) {
        if (dist < minDist) {
          minDist = dist;
          nearest = mapLoc;
        }
      }
    }
  }
  return(nearest);
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
//gives next action depending on job assigned
Action nextMove(int id,Loc botLoc) {
  
  switch (bot[id].job.type) {
    case FIND_DEBRIS : 
      return(stepFromTo(botLoc,bot[id].job.loc));
    case RANDOM_WALK :
      return(randomMove());
    default:
      return(randomMove());
  } 

}
//gets you from one place to another step by step
Action stepFromTo(Loc fromLoc, Loc toLoc) {
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
  
  getUDLR(fromLoc,up,down,left,right);
  //evaluate UP 

  if (up.r < 0 ) { //up is a wall
    badMoves[bad] = UP;
    bad++;
  }
  else if (map[up.r][up.c].hasBot) {
    worstMoves[worst] = UP;
    worst++;
  }
  else if ((distance(up,toLoc) < distance(fromLoc,toLoc)) &&
     !map[up.r][up.c].hasBot) {
    good[goodMoves] = UP;
    good++;
  }
  else if ((distance(up,toLoc) > distance(fromLoc,toLoc)) &&
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
  else if ((distance(down,toLoc) < distance(fromLoc,toLoc)) &&
     !map[down.r][down.c].hasBot) {
    good[goodMoves] = DOWN;
    good++;
  }
  else if ((distance(down,toLoc) > distance(fromLoc,toLoc)) &&
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
  else if ((distance(right,toLoc) < distance(fromLoc,toLoc)) &&
     !map[right.r][right.c].hasBot) {
    good[goodMoves] = RIGHT;
    good++;
  }
  else if ((distance(right,toLoc) > distance(fromLoc,toLoc)) &&
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
  else if ((distance(left,toLoc) < distance(fromLoc,toLoc)) &&
     !map[left.r][left.c].hasBot) {
    good[goodMoves] = LEFT;
    good++;
  }
  else if ((distance(left,toLoc) > distance(fromLoc,toLoc)) &&
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

void  getUDLR(Loc loc,Loc &up,Loc &down,Loc &left,Loc &right) {
  up.r = loc.r - 1; 
  up.c = loc.c;
  down.r = loc.r +1; 
  down.c = loc.c;
  left.r = loc.r; 
  left.c = loc.c -1;
  right.r = loc.r; 
  right.c = loc.c +1;
}
