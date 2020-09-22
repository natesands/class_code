/* computes n! */

#include <iostream>
using namespace std;

int nfac(int n);
int main() {
  int num;
  cout << "enter integer: ";
  cin >> num;

  cout << nfac(num) << endl;

  return(0);
}

//pre: pos int n, 0 <= n
//post: f = n!
int nfac(int n) {
  int f = 1;
  int k = 0;
  // inv: f = k!
  // f = (k-1)!*k
  while (k < n) {
    k++;
    f = f*k;
    
  }
  return (f);
}

