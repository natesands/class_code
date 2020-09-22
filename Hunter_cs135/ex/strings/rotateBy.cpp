#include <iostream>
#include <string>
using namespace std;

string rotateBy(string s, int n);

int main() {
  string s;
  int n;
  cout << "Enter string: ";
  getline(cin,s);
  cout << "Enter right-shift value: ";
  cin >> n;

  cout << rotateBy(s,n) << endl;
return(0);
}
//string s, int n
//returns s shifted to the right by n
string rotateBy(string s, int n) {

  char c;
  int newPos;
  string copy = s;

  for (int pos = 0; pos < s.length(); pos++) {
    c = s[pos];
    newPos = (pos + n) % s.length();
    copy[newPos] = c;
  }
return(copy);
}
