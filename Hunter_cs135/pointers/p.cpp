#include <iostream>
using namespace std;


int main() {

  int *p, r, *s;

  int *t = new int [10];

  r = 10;
  s = new int;

  *s = 6;
  
  p = &r;

  cout << p << endl;
  cout << *p << endl;

  cout << s << endl;
  cout << *s << endl;

  p = s;
  
  cout << p << endl;
  cout << *p << endl;

  t[0] = 4;
  t[1] = 7;
  t[2] = *p;

  for (int i=0; i < 3; i++) {
    cout << t[i] << endl;
    cout << *(t + i-1) << endl;
  }

  p = t;

  p++;
  cout << t[0] << endl;
  cout << p[0] << endl;

  

}
  




