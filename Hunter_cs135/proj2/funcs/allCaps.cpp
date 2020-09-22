#include <iostream>
#include <cctype>
#include <string>
using namespace std;

void allCaps(string& s); 

int main() {
  string s = "hElLo!";
  allCaps(s);
  cout << s << endl;
return 0;
}

void allCaps(string& s) {
  for (int i = 0; i < s.size(); i++) {
    if (s[i] >= 'a' && s[i] <= 'z') {
      s[i] = (char) ((int) s[i] - 32);
    }
  }
return;
}

