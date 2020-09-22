
#include <iostream>
using namespace std;

int main() {
  
  int n, largestK=0;
  cin >> n;

  for (int i = 1, k=1; i <= n; i++, k=i){ 
    while (k != 1) {
      cout << k << " "; 
      if (k % 2 == 0) k = k/2;
      else k = 3*k +1;
    }
    cout << endl;
  }

  cout << "\nSuccess!" <<  endl;
  cout << "Largest K: " << largestK << endl;
return 0;
}

