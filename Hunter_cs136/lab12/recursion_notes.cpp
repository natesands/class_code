:or_eq:or_eq
/*

Author: Nathaniel Sands
Course: CSCI-136
Instructor: Gwenael Gatto
Assignment: Lab12B

Print numbers is range recursively;
Sums numbers in range recursively

*/
#include <iostream>
using namespace std;
//takes two ints, prints range of integers
//between them
void printRange(int left, int right) {
  if (left <= right) {
    cout << left << " ";
  
    if (left != right) {
      printRange(left+1,right);
    } 
    else cout << endl;
  }
}

//sums numbers in range between two ints
int sumRange(int left, int right) {
  if (left <= right) {
    int sum;
    sum = left + sumRange(left+1,right);;
    return sum;
  }
  else return 0;

}

      

 two recursive calls at every level
base case end of array
or fail case if sum is more than 86
can i reach 86 at the end
go until each gets 86
or one gets more than 86
or you're at end of array


int main() {
  int left, right;
 
  cout << "Enter two numbers: ";
  cin >> left >> right;

  if (left <= right)  printRange(left,right);
  cout << endl;
  if (left <= right)  cout << sumRange(left,right) << endl;
return 0;
}

