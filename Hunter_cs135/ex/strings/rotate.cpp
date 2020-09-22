#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
using namespace std;

string rotate(string s);
int main() {
  string s;
  cout << "Enter string: ";
  getline(cin, s);

  cout << rotate(s) << endl;

return(0);
}
//takes string
//returns string rotated to the right by 1
string rotate(string s) {

  char c;
  string copy;
  int len;
  //make copy of string
  copy = s;
  int newPos;


  //get string length
  len = s.length();

//iterate through s until end of string
//record char at each pos, and assign new pos
  for (int pos = 0; pos < len; pos++) {
    //record char at each pos
    c = s[pos];
    //assign new pos
    newPos = (pos + 1) % len;
    //write over copy at newPos with char
    copy[newPos] = c;
  }
return(copy);
}

