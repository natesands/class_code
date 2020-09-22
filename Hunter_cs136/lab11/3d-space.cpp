
/*

Author: Nathaniel Sands
Course: CSCI-136
Instructor: Gwenael Gatto
Assignment: Lab11C

computes the position of a particle after 10 seconds
using dynamically created memory objects
*/

#include <iostream> 
#include <cmath>
using namespace std;

struct Coord3D {
  double x;
  double y;
  double z; 
};

double length(Coord3D *p) {
  double answer;
  double xcoord, ycoord,zcoord;
  xcoord = p -> x; ycoord= p-> y; zcoord = p->z;
  answer = (sqrt(pow(xcoord,2) + pow(ycoord,2) + pow(zcoord,2)));
  return(answer);
}
//returns pointer to Coord3D struct variable
Coord3D * fartherFromOrigin(Coord3D *p1, Coord3D *p2) {
  double dist1, dist2;
  
  dist1 = length(p1);
  dist2 = length(p2);

  if(dist1 > dist2) return(p1);
  return(p2);
}

//gets position and the velocity of an object
//and computes the object;s new coordinates after
//the time interval dt.

void move(Coord3D *ppos, Coord3D *pvel, double dt) {
  double dx = dt * (pvel->x);
  double dy = dt * (pvel->y);
  double dz = dt * (pvel->z);
 
  ppos->x += dx;
  ppos->y +=dy;
  ppos->z +=dz;
     
}

Coord3D * createCoord3D(double x, double y, double z) {

  Coord3D *c3d = new Coord3D;
  
  (c3d->x) = x;
  (c3d->y) = y;
  (c3d->z) = z;

  return c3d;
}

void deleteCoord3D(Coord3D *p) {
  delete p;
}

int main() {
  double x,y,z;
  cout << "Enter position: ";
  cin >> x >> y >> z;
  Coord3D *ppos = createCoord3D(x,y,z);
  
  cout << "Enter velocity: ";
  cin >> x >> y >> z;
  Coord3D *pvel = createCoord3D(x,y,z);

  move(ppos,pvel,10.0);

  cout << "Coordinates after 10 seconds: "
      << (*ppos).x << " " << (*ppos).y << " " << (*ppos).z << endl;

  deleteCoord3D(ppos);
  deleteCoord3D(pvel);
}



