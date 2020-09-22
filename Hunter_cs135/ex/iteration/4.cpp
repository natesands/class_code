/* Collatz loop */

#include <iostream>
using namespace std;

int main() {
  
  int k, iterations=0, largestK=0;
  cin >> k;
  
  while (k != 1) {
    if (k > largestK) largestK = k;
    if (k % 2 == 0) k = k/2;
    else k = 3*k +1;
    iterations++;
    cout << k << " "; 
  }

  cout << "\nSuccess! Number of iterations: " << iterations <<
    endl;
  cout << "Largest K: " << largestK << endl;
return 0;
}


