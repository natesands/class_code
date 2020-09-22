/*

Author: Nathaniel Sands
Course: CSCI-135
Instructor: Subash Shankar
Assignment: Project 1D

Takes a sequence of non-negative integers separated by '+','-','^' or ';' from
the standard input.  When a '^' is read after a number, the number is
squared.  The sum is evaluated and output when a ';' is read.

Numbers are multiplied by 1 or -1 depending on the whether they are to be added
or subtracted from the sum. So A - B + C is summed as 1*A + -1*B + 1*C.  

*/

#include <iostream>
using namespace std;

int main() {

  int number, sum, sign;
  char op; //to store '+', '-', or ';'

  sum = 0;
  sign = 1; //default sign for first number

  while ( cin >> number) {
    
    cin >> op;

    if (op == '^') {  //square operation
      number = number*number;
      cin >> op; 
    }
      
    number = number * sign;  //number is added to sum
    sum += number;
    
    if (op == '+') sign = 1; //sign is prepared for next number 
    if (op == '-') sign = -1;
    if (op == ';') {  //signal to output sum and reset values
      cout << sum << endl;
      sum = 0;
      sign = 1;
    }
  }
 
return (0);
}
