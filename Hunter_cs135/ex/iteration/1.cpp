/* Input sequence of non negative numbers using cin
terminated with -1.  
Output average of the even-indexed and odd-indexed ones.
*/

#include <iostream>
using namespace std;
int main(){
  int num, oddCount, evenCount, index;
  num=oddCount=evenCount=index=0;
  double sumOdd, sumEven;
  sumOdd=sumEven=0;
  while(cin>>num && num != -1){
    if (index % 2 == 0) {
      sumEven += num;
      evenCount++;
    } 
    else {
      sumOdd += num;
      oddCount++;
    }
    index++;
  }
  cout << sumEven/evenCount << " " << sumOdd/oddCount << endl;
return 0;
}
