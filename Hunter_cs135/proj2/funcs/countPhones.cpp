#include <iostream>
#include <cctype>
#include <string>
#include <cstdlib>
using namespace std;

int countPhones(string s);

int main() {

  string line;
  char ans;

//  do {  
    cout << "Enter phoneme string: ";
    getline(cin,line);

    cout << "Phoneme count: " <<  countPhones(line) << endl;
  //  cout << "Again?";
  //  cin >> ans;
//  } while (ans == 'y');

return 0;
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

