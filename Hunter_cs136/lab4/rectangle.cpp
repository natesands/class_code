/* Draws a rectangle from the dimensions specified by
the user using '#' */

#include <iostream>
using namespace std;

int main(){

  int m,n;

  cout << "Enter height: ";
  cin >> m;
  cout << "Enter width: ";
  cin >> n;

  for (int i=m; i > 0; i--){
    for (int j=0;j<n;j++){
      cout << "#";
    }
    cout << endl;
  }
return 0;
}
