#include <iostream>
using namespace std;

int main (){

  int oddCount, evenCount;
  double oddSum, evenSum;
  int num;

  oddCount = evenCount = oddSum = evenSum = 0;
  cin >> num;
  for (int i=0; num != -1; i++,cin>>num) {
    if (i % 2 == 0) {
      evenSum += num;
      evenCount++;
    }
    else {
      oddSum += num;
      oddCount++;
    }
  }
  cout << (evenSum/evenCount) << " " <<
    (oddSum/oddCount) << endl;
return 0;
}


      
     
