#include <iostream>
#include <cctype>
#include <string>
using namespace std;

void splitOnSpace(string s, string & before, string & after);
int main() {
//case 1 check!
//  string w = "A B C"; //user word
//  string s = "A B X C"; //dictonary item
//case 2
//  string w = "A B C"; //user word
 // string s = "A B X C X"; //dictonary item

  string w, s;
  cout << "Enter string 1: ";
  getline(cin, w);
  cout << "Enter string 2: ";
  getline(cin,s);

  string wb,wa,sb,sa; 

  if (w != s) {
    do {
    splitOnSpace(w,wb,wa);
    splitOnSpace(s,sb,sa);
    w = wa;
    s = sa;
    } while(wb == sb && wa != "");

    splitOnSpace(s,sb,sa);
    if (wa == sa) cout << "Identical w one additon" << endl;
    else cout << "not identical" << endl;

}

//if w = s, they are identical
//if not identical
//CHECK IF ADD PHONEME
//split on space
//if wb = sb
//split on space
//if wb != sb
//split s on space
//if wa = sa
//then wa and sa are diff by one additional
//if wa != sa
//then not additional

//if not identitical, split on space
//if wb = sb
//split on spac



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


