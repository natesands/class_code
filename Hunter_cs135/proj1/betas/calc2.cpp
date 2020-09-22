/*

Author: Nathaniel Sands
Course: CSCI-135
Instructor: Subash Shankar
Assignment: Project 1C

Takes a sequence of non-negative integers separated by '+' or '-' from
the standard input.  When a ';' is read, evaluates the sum to
that point and outputs the result.  Continues in this manner
until EOF.

Each number is multiplied by 1 or -1 based on the operator that
precedes it, and is added to the sum.  So A - B + C - D is
totaled as (1)*A + (-1)*B + (1)*C + (-1)*D.

*/

#include <iostream>
using namespace std;

int main() {

  int number, sum, sign;
  char op; //to store '+', '-', or ';'

  sum = 0;
  sign = 1; //default sign for first number

  while ( cin >> number) {
    number = number * sign;
    sum += number;
   
    if (cin >> op) {
      if (op == '+') sign = 1;
      if (op == '-') sign = -1;
      if (op == ';') {
        cout << sum << endl;
        sum = 0;
        sign = 1;
      }
    }
  }
return (0);
}
