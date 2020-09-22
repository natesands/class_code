
#include <iostream>
using namespace std;

int multiply(int x, int y);

int main() {

  int x, y;
  cout << "enter two integers to multiply : ";
  cin >> x >> y;
  cout << multiply(x,y) << endl;
  return(0);
}

int multiply(int x, int y) {

//y >= 0 ^ y <0
  int z = 0;
  int k = 0;

  //inv: z = x * k and y >= 0 and k <= y
  while (k != y && y >= 0) {
    k++;
    //z = x * (k-1)
    z = z + x;
  }
  //inv; z = x * k and y < 0 and k >= y
  while ( k != y and y < 0) { 
    k--;
    //z = x*(k+1)
    z = z - x;
  }
  return(z);
}
 
