#include <iostream>
using namespace std;

int main () {
  int oddCount, evenCount;
  double oddSum, evenSum;
  int num;
  
  oddCount=evenCount=oddSum=evenSum=0;
  cin >> num;
  do {
    if (num % 2 == 0) {
      evenSum += num;
      evenCount++;
    }
    else {
      oddSum += num;
      oddCount++;
    }
    cin >> num;
  } while (num != -1);

  cout << (evenSum/evenCount) << " " << (oddSum/oddCount) <<
    endl;
return 0;
}
 
