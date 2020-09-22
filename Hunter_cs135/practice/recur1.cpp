#include <iostream>
#include <cstdlib>
#include <cctype>
#include <string>
using namespace std;

string evother(string s) {

  if (s.length() == 1) return s;
  else return(s[0] + evother(s.substr(2)));

}

string uc(string s) {
  if (s.length() == 1) {
    char c = s[0];
    if (isupper(c)) { return "UC";}
    else return s;
  }
  char c = s[0];
  if (isupper(c)) return ("UC" + uc(s.substr(1,s.length()-1)));
  else return (c + uc(s.substr(1,s.length()-1)));
}
int main() {

  string s;

  cout << "Enter string:";

  getline(cin,s);

  cout << evother(s) << endl;
  cout << uc(s) << endl;
}
