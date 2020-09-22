#include <iostream>
#include <cctype>
#include <string>
using namespace std;

bool ignoreWord(string s);

int main() {

  string arr[]=
{"progress(1)","program","'bout","push-up","&ampersand"};

  for (int i=0; i < 5; i++) {
    if (ignoreWord(arr[i])) {
      cout << arr[i] << " -- ignore it!" << endl;
    }
    if (!ignoreWord(arr[i])) {
      cout << arr[i] << " -- don't ignore it!" << endl;
    }
  }

return 0;
}

bool ignoreWord(string s) {
    bool ignore = false;
    int i = 0;
  
    while (i < s.length() && !ignore) {
      if (s[i] != '\'' && !isalpha(s[i])) {
        ignore = true;
      }
      i++;
    }
return(ignore);
}

