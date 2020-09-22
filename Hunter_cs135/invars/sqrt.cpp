#include <iostream>
using namespace std;

int sqrt(int x);

int main() {

  int num;
  cout << "Enter number >= 0: ";
  cin >> num;

  cout << sqrt(num) << endl;
}

int sqrt(int x) { 

  int y = 0;
  int r = x;

  //inv: x = y^2+r and r >=0 and y >= 0
  while (r >= 2*y + 1) {
    r = r - (2*y +1);
    y = y + 1;
  }
  return(y);
}
 
