
/*

Author: Nathaniel Sands
Course: CSCI-136
Instructor: Gwenael Gatto
Assignment: Lab12E

Print numbers is range recursively;
Sums range of numbers recursively;
sums elements of array recursively.
determines if a string of characters is alphanumeric;
checks for nested parens recursively

*/
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

//sums the elements of an array

int sumArray(int *arr, int size) {

  int sum;
  
  if (size == 0) return 0;
  else {
    sum = arr[size-1] + sumArray(arr, size-1);
    return sum;
  }    
}


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
int sumRange(int left, int right) {
  int sum;
  if (left <= right) {
    sum = left + sumRange(left+1,right);
    return sum;  
  }
  else return 0;
}    

bool isAlphanumeric(string s) {
  int len = s.length();
 
  if (len == 1) return (isalnum(s[0]));
  else {
    return isalnum(s[0]) && isAlphanumeric(s.substr(1));
  }
}    
//checks for correctly nested parens     
bool nestedParens(string s) {

  int len = s.length();
  
  if (len == 0 ) return true;
  else {
    return (s[0]=='(' && s[len-1] == ')' and nestedParens(s.substr(1,len-2))); 
  }
}
bool divisible(int *prices,int size) {

  int alice, bob;

  if (size == 0 ) return true; 
  else {
    
       
int main() {
 /* 
  int left, right;
 
  cout << "Enter two numbers: ";
  cin >> left >> right;

  printRange(left,right);
  cout << sumRange(left,right) << endl;

  int size = 10;
  int *arr = new int[size];
  arr[0]=12;
  arr[1]=17;
  arr[2] =-5;
  arr[3]=3;
  arr[4]=7;
  arr[5]=-15;
  arr[6]=27;
  arr[7]=5;
  arr[8]=13;
  arr[9]=-21;

  int sum = sumArray(arr,size);
  cout << "Sum of array is " << sum << endl;

  delete [] arr;
  
  cout << "Is Alphanumeric" << endl;
  cout << isAlphanumeric("ABCD") << endl;        // true (1)
  cout << isAlphanumeric("Abc2343dxyz") << endl; // true (1)
  cout << isAlphanumeric("KLMN 8-7-6") << endl;  // false (0)
*/


  cout << nestedParens("((()))") << endl;      // true (1)
  cout << nestedParens("()") << endl;          // true (1)
  cout << nestedParens("") << endl;            // true (1)

  cout << nestedParens("(((") << endl;         // false (0)
  cout << nestedParens("(()") << endl;         // false (0)
  cout << nestedParens(")(") << endl;          // false (0)
  cout << nestedParens("a(b)c") << endl;       // false (0)

return 0;
}

