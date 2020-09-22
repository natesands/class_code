/* Draws a pyramid according to dimensions given by user
using character '#'*/

#include <iostream>
using namespace std;

int main() {

  int m,n;
  
  cout << "Enter height: ";
  cin >> m;
  cout << "Enter width: ";
  cin >> n;

  for (int i=(m-1); i>=0; i--) {
    for (int j=0; j<n; j++) {
      if (
//        if (i<=j && i<=(-1*j)+m){
//      if (i<= (2*m/n*j) && i<=(-2*m*j/n+2*m)){
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


