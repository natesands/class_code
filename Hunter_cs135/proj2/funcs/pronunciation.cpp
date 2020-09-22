#include <iostream>
#include <cctype>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

string pronounce(ifstream& dict, string w, bool& found);
void splitOnSpace(string s, string & before, string & after);
void allCaps(string& s); 
int main() {

  bool inDictionary;
  string word;
  string pronunciation;

//open dictionary
  ifstream dictionary;
  dictionary.open("cmudict.0.7a");
  if (dictionary.fail()) {
    cerr << "file open failed" << endl;
    exit(1);
  }

//prompt user for word
  cout << "Enter word: ";
  cin >> word;
  allCaps(word); 
//search dictionary
  pronunciation = pronounce(dictionary, word, inDictionary);
//output results
  if(inDictionary) {
    cout << "Pronunciation     : " + pronunciation << endl;
    }
  else {
    cout << "Not found." << endl;
  }
  dictionary.close();
return 0;
}
    
string pronounce(ifstream& dict, string w, bool& found) {

  string line;
  found = false;
  string entry, pron;
//skip header lines beginning with ';;;'
  do {
    getline(dict,line);
  } while(line[0] == ';');
//go through entries
//split words into spelling and pronunciation
//check if there is match
  while(!found && !dict.eof()) {
    splitOnSpace(line, entry, pron);
    if (w == entry) {
      found = true;
    }
    getline(dict,line);
  }
  if (found) return(pron);
  else return("not found");
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


void allCaps(string& s) {
  for (int i = 0; i < s.size(); i++) {
    if (s[i] >= 'a' && s[i] <= 'z') {
      s[i] = (char) ((int) s[i] - 32);
    }
  }
return;
}




















