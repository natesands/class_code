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
  int w, k, z;
  z = 0;
  k = y;
  w = x;
  //inv: z + wk = xy and k >= 0
  while ( k!=0 ) {
    if (k % 2 == 1) {
      //z + wk = xy and k > 0 and k odd
      k = k-1;
      z = z + x;
      //z + wk = xy and k >= 0 and k even
    }
    else {
      //z + wk = xy and k >= 2 and k even
      k = (k/2);
      w = w*2;
      z =z+ w;
      k = k -1;
     // if (k == 1 || k ==2) k = k - 1;
    //  else k = k -2;
    }
  }
  //z = xy
  return (z);
}

      
