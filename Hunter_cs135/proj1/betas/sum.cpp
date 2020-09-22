/*

Author: Nathaniel Sands
Course: CSCI-135
Instructor: Subash Shankar
Assignment: Project 1A

Takes a sequence of integers from the standard input stream
and computes their sum.

*/

#include <iostream>
using namespace std;


int main() {

  int number, sum;

  sum = 0;

  while (cin >> number) {
    sum += number;
  }

  cout << sum << endl;

return 0;
}
