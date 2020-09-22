/* Prints r rows of a diagonal line with slope -1 */

#include <iostream>
using namespace std; 

int main() {

  int r;
  cout << "enter number of rows: ";
  cin >> r;

  for (int rows = 0; rows < r; rows++) {
    for (int col = 0; col < rows; col++) {
      cout << " ";
    }
    cout << "*" << endl;
  }

return 0;
}

