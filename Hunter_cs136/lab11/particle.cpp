/*

Author: Nathaniel Sands
Course: CSCI-136
Instructor: Gwenael Gatto
Assignment: Lab11E

computes the position of a particle
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
//particle with 3 pos coords, 3 vel coords
struct Particle {
  Coord3D pos;
  Coord3D vel;
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
Particle *createParticle(double x, double y, double z,
     double vx,double vy, double vz) {
  Particle *p = new Particle;
  (*p).pos.x = x; (*p).pos.y = y; (*p).pos.z = z;
  (*p).vel.x = vx; (*p).vel.y=vy; (*p).vel.z=vz;
  return p;
}
void setVelocity(Particle *p, double vx, double vy, 
      double vz) {
  (*p).vel.x = vx; (*p).vel.y = vy; (*p).vel.z = vz;
}

Coord3D getPosition(Particle *p) {
  Coord3D pp;
  pp.x = (*p).pos.x; pp.y = (*p).pos.y; pp.z = (*p).pos.z;
  return pp;
}
void move(Particle *p, double dt) { 
   
  double dx = dt * (p->vel.x);
  double dy = dt * (p->vel.y);
  double dz = dt * (p->vel.z);
 
  p->pos.x +=dx;
  p->pos.y +=dy;
  p->pos.z +=dz;
}
void deleteParticle(Particle *p) {
  delete p;
}
int main() {
    // make new particle
    Particle *p = createParticle(1.0, 1.5, 2.0, 0.1, 0.2, 0.3);
    double time = 0.0;
    double dt = 0.1;
    while(time < 3.0) {
        // update its velocity
        setVelocity(p, 10.0 * time, 0.3, 0.1);

        // move the particle
        move(p, dt);
        time += dt;

        // reporting its coordinates
        cout << "Time: " << time << " \t";
        cout << "Position: "
             << getPosition(p).x << ", "
             << getPosition(p).y << ", "
             << getPosition(p).z << endl;
    }
    // remove the particle, deallocating its memory
    deleteParticle(p);
}


