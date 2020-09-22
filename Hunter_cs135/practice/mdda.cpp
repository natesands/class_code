/* create an nxm dynamic array */
#include <iostream>
using namespace std;

typedef int* IntArrPtr;

int main() {

  int n,m;
  IntArrPtr* mdda;

  cout << "enter dimensions n m: ";
  cin >> n >> m;

  mdda = new IntArrPtr[n];

  for (int i = 0; i < n; i++) {
    mdda[i] = new int[m];
  }
  int num = 0; 
  for (int i = 0; i < n; i++){
    for (int j = 0; j < m; j++) {
      mdda[i][j] = num;
      num++;
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j=0; j < m; j++) {
      cout << mdda[i][j] << " ";
    }
    cout << endl;
  }
  
  for (int i = 0; i < n; i++) 
    delete [] mdda[i];

  delete [] mdda;

}
  
