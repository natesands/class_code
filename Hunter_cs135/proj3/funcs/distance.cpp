/*
Computes the distance between two points 
on a grid
*/


#include <iostream>
using namespace std;


struct Loc {
  int r;
  int c;
};

int abVal(int x);
int distance(Loc a, Loc b);

int main() {
  Loc pointA, pointB;

  cout << "Enter row and column for point a: ";
  cin >> pointA.r >> pointA.c;
  cout << "Enter row and column for point b: ";
  cin >> pointB.r >> pointB.c;

  cout << "The distance between A and B is " << 
        distance(pointA, pointB) << endl;

  return 0;
}

int abVal(int x) {
    if (x < 0)  x  = -1*x;
    return(x);
}

int distance(Loc a, Loc b) {
  int distr, distc;
  distr = abVal(a.r - b.r);
  distc = abVal(a.c - b.c);
  return(distr + distc);
}
 
