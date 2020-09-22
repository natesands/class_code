#include <iostream>
#include <cctype>
#include <string>

using namespace std;
string shiftWord(string s, int n);
int main () {
  string instr;
  int n;
  cout << "enter string: ";
  getline(cin, instr);
  cout << "enter shift: ";
  cin >> n;
  cout << shiftWord(instr,n) << endl;
  return(0);
}


//pre: s a string of length l,  n >= 0
//post: s_0 = s shifted to the right by n
string shiftWord(string s, int n) {
  
  string shifted = s;
  int l = s.length();
  int i = 0;

  shifted[(i+n) % l] = s[i];
//inv: shifted[(i+n) % l] = s[i]
  while (i < l-1) {
    i++;
    shifted[(i+n) % l] = s[i];
  } 
//asser: i = l-1
//asser: shfted[(L-1 + n) % l] = s[L-1]
  return(shifted);
}
