
#include <cstdlib>
#include <iostream>
#include "bot.h"

using namespace std;
/* FUNCTIONS */
int abVal(int x);
int distance(Loc a, Loc b);
Action moveTo(Loc botLoc, Loc mapLoc);
Loc nearestDebris(Loc botLoc, Area area);

const int MAX_ROBOT_NUM = 50;

int NUM;          // to remember number or robots
int ROWS, COLS;   // map dimensions

/* Initialization procedure, called when the game starts: */
void onStart(int num, int rows, int cols, double mpr,
             Area &area, ostream &log)
{
	NUM = num;   // save the number of robots and the map dimensions
	ROWS = rows;
	COLS = cols;
	
  log << "Start!" << endl;
}

/* Deciding robot's next move */
Action onRobotAction(int id, Loc loc, Area &area, ostream &log) {
	int row = loc.r; // current row and column
	int col = loc.c;
  Loc jobSite;
  
	if (area.inspect(row, col) == DEBRIS)
		return COLLECT;
	else {
    jobSite = nearestDebris(loc,area);
    return(moveTo(loc,jobSite));
	}
}

void onRobotMalfunction(int id, Loc loc, Area &area, ostream &log) {
	log << "Robot " << id << " is damaged." << endl;
}

void onClockTick(int time, ostream &log) {
	if (time % 100 == 0) log << time << " ";
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

Loc nearestDebris(Loc botLoc, Area area) {
  int minDist, dist;
  Loc nearest;
  Loc mapLoc;
  minDist = ROWS + COLS + 1;
  for (int r = 0; r < ROWS; r++) {
    for (int c = 0; c < COLS; c++){
      mapLoc.r = r;
      mapLoc.c = c;
      dist = distance(botLoc,mapLoc);
      if (area.inspect(r,c) == DEBRIS){
        if ( dist < minDist) {
          minDist = dist;
          nearest = mapLoc;
        }
      }
    }
  }
  return(nearest);
}

//returns next move needed to reach
//a map location
Action moveTo(Loc botLoc, Loc mapLoc) {
  Action nextMove=COLLECT;
  if (botLoc.r > mapLoc.r) nextMove = UP;
  else if (botLoc.r < mapLoc.r) nextMove = DOWN;
  else if (botLoc.c > mapLoc.c) nextMove = LEFT;
  else if (botLoc.c < mapLoc.c) nextMove = RIGHT;
  return(nextMove);
}  






 




