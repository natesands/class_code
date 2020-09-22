#include <iostream>
using namespace std;

int exp(int x, int n);
int main() {

  int base, ex; 
  cout << "Enter base and exponent : ";
  cin >> base >> ex;
  cout << exp(base,ex) << endl;
}

//pre: x >= 0, n >=0;  
int exp(int x, int n) {

  int y, k;
  y = 1;
  k = 0;

  //whileinv: y=x^k and 0<= k <= n
  while (k != n) {
   k++;
   //y = x^(k-1) and 0<= k <=n
   y = y*x;
  }
  //y = x*k

  return(y);
}
  
