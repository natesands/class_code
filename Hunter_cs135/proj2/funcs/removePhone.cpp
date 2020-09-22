#include <iostream>
#include <cctype>
#include <string>
#include <cstdlib>
using namespace std;

int countPhones(string s);
string removePhone(string s, int n);
void splitOnSpace(string s, string& before, string& after);

int main() {

  string line;
  int n;
  cout << "Enter phoneme string: ";
  getline(cin,line);
  cout << "Enter number of phoneme to delete: ";
  cin >> n;
  cout << "Modified string: " + removePhone(line,n);
  cout << endl;

return 0;
}
//takes string of phonemes with no leading space
//and integer n
//returns string with nth phoneme removed
string removePhone(string s, int n) {

  string newString = "";
  string before, after;
  string temp = s;
 
  for ( int i = 0; i < n-1 && i < countPhones(s); i++) {
    splitOnSpace(temp, before, after);
    newString += before + " ";
    temp = after;
  }
  splitOnSpace(temp,before,after);
  newString = newString + after;
  //remove any trailing space
  if (isspace(newString[newString.length()-1])) {
    temp = newString;
    newString = "";
    for (int i = 0; i < temp.length() -1; i++) {
      newString += temp[i];
    }
  }
return(newString);
}

int countPhones(string s) {

  int count = 0;
  int i = 0;

  while ( i < s.length()) {
    count++;
    while (!isspace(s[i]) && i < s.length()) i++;
    while (isspace(s[i]) && i < s.length()) i++;
  }
return (count);
}

void splitOnSpace(string s, string & before, string & after) {

//reset strings
  before = "";
  after = "";
//accumulate before space
  int i=0;
  while (i < s.size() && not isspace(s[i])) {
    before += s[i];
    i++;
  }
    i++;
  while (i < s.size()) {
    after +=s[i];
    i++;
  }
return;
}
