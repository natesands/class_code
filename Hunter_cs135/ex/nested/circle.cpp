/* draws a circle */

#include <iostream>
using namespace std;

int main() { 
  int radius;
  cout << "enter radius: ";
  cin >> radius;

  for (int row=radius*-1; row <= radius; row++){
    for (int col = radius; col >=-1*radius; col--){
      if (row*row+col*col <= radius*radius){
        cout << "*";
      }
      else {
        cout << " ";
      }
    }
  cout << endl;
  }
return 0;
}
