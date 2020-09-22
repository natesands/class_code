/*draws a line with a give slope m over r lines*/
#include <iostream>
using namespace std;

int main () {
  int m, r;

  cout << "enter slope and rows: " ; 
  cin >> m >> r; 

  for (int row = r; row >= 0; row--) {
    for (int col =0; col <= r*m; col++){
      if (row == m*col) cout << "*";
      else cout << " ";
    }
    cout << endl;
  }
return 0;
}

