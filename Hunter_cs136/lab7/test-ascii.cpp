/*

Author: Nathaniel Sands
Course: CSCI-136
Instructor: Gwenael Gatto
Assignment: Lab7A

Takes a line of input and returns each character 
followed by its ASCII code.

*/
#include <iostream>
#include <string>
using namespace std;

int main () {

  string line; 
  cout << "Input: ";
  getline(cin,line);

  for (int i = 0 ; i < line.length(); i++) {
    cout << line[i] << " " << (int) line[i] << endl;
  }
return 0;
}
 
