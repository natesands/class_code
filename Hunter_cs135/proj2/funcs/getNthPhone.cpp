#include <iostream>
#include <cctype>
#include <string>
#include <cstdlib>
using namespace std;

int countPhones(string s);
string getNthPhone(string s,int n);
void splitOnSpace(string s, string& before, string& after);
bool hasReplacedPhone(string s1, string s2);

int main() {
/* for testing getNthPhone
  string line;
  int n;

  cout << "Enter phone string: ";
  getline(cin,line);
  cout << "Which phoneme do you want?: ";
  cin >> n;
  cout << "Returned with: " + getNthPhone(line,n) << endl;
*/

  string s1, s2;
  cout << "Enter first string: ";
  getline(cin,s1);
  cout << "Enter second string: ";
  getline(cin,s2);

  if (countPhones(s1) == countPhones(s2)) {
    if (hasReplacedPhone(s1,s2)) cout << "Hit." << endl;
  }
  else cout << "No hit." << endl;
  
return 0;
}

bool hasReplacedPhone(string s1, string s2) {

  bool hit = false;
  int diffs = 0;
  int numPhones = countPhones(s1);

  for (int i = 1; i <= numPhones; i++) {
    if (getNthPhone(s1,i) != getNthPhone(s2,i)) {
      diffs++;
    }
  }
  if (diffs == 1) hit = true;
return(hit);
}


string getNthPhone(string s, int n) {

  string nthPhone = "";
  string after = "";

  if (n > countPhones(s)) return(nthPhone);

  for (int i = 1; i <= n; i++) {
    splitOnSpace(s, nthPhone, after);
    s = after;
  }
return(nthPhone);  
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
