/*Gets value of n from user. Makes a "graph" of y <= x for x in [0,n] */

#include <iostream>
using namespace std;

int main(){

  int x;
  cout << "Enter max value of x: ";
  cin >> x; 

  for (int m = x; m >= 0; m--){
    for (int n=0; n <= x; n++){
      if (m <= n) {
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
