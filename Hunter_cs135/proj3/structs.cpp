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
//THEORY:  
//All bots get a turn, even bots that are broken.
//Bots only break during COLLECT action or when action
//returned by function is not understood.
//One succesfull repair action fixes a broken bot.
//One succesfull COLLECT clears tile of debris.
//Bots will not break if they bump into walls or into
//each other.

//APPROACH:
//ALL bots, including broken ones, will execute COLLECT action
//on turn if there IS DEBRIS at location, EXCEPT IF BOT IS ASSIGNED REPAIR JOB or 
//THERE ARE UNASSIGNED BROKEN BOTS.
//This will prevent situation in which all bots are broken
//with no one to fix them.
//OnRobotMalfunction will assign repair job to bot that is
//closest to broken bot (that is not itself broken or already
//assigned to a repair job). If there are no available bots at
//the time, (i.e., all bots are either broken or assigned a 
//repair job), then ORM function will increment UNASSIGNED_BROKEN_BOTS.
//So here, ORA will check counter and if it is greater than zero
//it will assign a bot to the repair and decrement the counter.
//If there is NO DEBRIS at bots location then bot 1) has either completed an assigned
//debris job at loc, or 2) is on the way to an assigned debris job or 3) needs an assignement.
//In case 1, unassign bot and give new assignment.  return next move to new assignment.
//In case 2, return next move to assignment.  In case 3, give new assignment, return
//next move to assignment. IF there are NO UNASSIGNED DEBRIS jobs, then assign bot
//a random move.
//Refresh map function will count the number of UNASSIGNED_DEBRIS
