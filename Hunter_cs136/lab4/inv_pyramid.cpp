/* Asks the user for a height and prints a pyramid
using '#' */

#include <iostream>
using namespace std;

int main() {

  int h;
  cout << "Enter height: ";
  cin >> h;

  for (int m=h-1; m >=0; m--) {
    for (int n=0;n <=(2*(h-1));n++) {
      if ((m >= n) && ( m >= (-1*n + 2*(h-1)))){
        cout << "#";
      }
      else {
        cout << " ";
      }
    }
      cout << endl;
  }
return 0;
}


