/* prints a diamond */


#include <iostream>
using namespace std;

int main(){


  int height;

  cout << "Enter height: ";
  cin >> height;
  for (int m = height-1; m >= 0; m--){
    for (int n=0; n < height; n++){
      if (m == (n + (height-1)/2)) {
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
 
