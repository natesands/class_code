#include <iostream>
using namespace std;

int fibbn(int n);
int main() {
  int num;

  cout << "Which fibbonaci number do you seek? ";
  cin >> num;
  cout << fibbn(num) << endl;
  
  return(0);
}
int fibbn(int n) {

  int fa, fb, fk;
  fa = 1;
  fb = 0;
  fk = 1;

  if (n == 1) fk = fb;
  else if (n == 2) fk = fa;


  else {
    //assr n >= 3, fa = 1, fb =0, fk = 1
    //inv: fa = fibk-1, fb=fibk-2
    //inv: fk = fa + fb
    for (int k= 3; k <= n; k++) {
      fk = fa + fb; 
      fb = fa;
      fa = fk;
    }
  }
  return(fk);
} 


