#include <iostream>
#include <cctype>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

bool inDictionary(string w);
void splitOnSpace(string s, string& before, string& after);
void allCaps(string& s);
bool ignoreWord(string s);
string pronounce(string w);

int main() {

  string word;

//prompt user for word
  cout << "Enter word: ";
  cin >> word;

//convert input word to all caps
  allCaps(word);

//check if word is in dictionary
//If not, exit
  if (!inDictionary(word)) {
    cout << "Not found." << endl;
    exit(1);  
  }

  cout << "Pronunciation   : " + pronounce(word) << endl;

return 0;
}

//takes a legal dictionary word
//returns pronunciation as string
//with any leading spaces removed
string pronounce(string w) {
  
  string line;
  bool found = false;
  string word, entry;

//open dictionary
  ifstream dictionary;
  dictionary.open("cmudict.0.7a");
  if (dictionary.fail()) {
    cerr << "file open failed" << endl;
    exit(1);
  }

//skip header lines beginning with
//';;;'
  do {
    getline(dictionary,line);
  } while (line[0] == ';');

//go through entries
  while(!found && !dictionary.eof()) {
    splitOnSpace(line, word, entry);
    if (w == word) {
      found = true;
    }
    getline(dictionary,line);
  }
  dictionary.close();
 return(entry);
}

//string entered by user
//true if in dictionary, false if not. also
//false if contains non-alpha characters 
//(except for apostrophe)
bool inDictionary(string w) { 

//if word contains non-alpha besides apostrophe,
//return false
  if(ignoreWord(w)) return(false);

  string line;
  bool found = false;
  string word, entry;

//open dictionary
  ifstream dictionary;
  dictionary.open("cmudict.0.7a");
  if (dictionary.fail()) {
    cerr << "file open failed" << endl;
    exit(1);
  }

//skip header lines beginning with
//';;;'
  do {
    getline(dictionary,line);
  } while (line[0] == ';');

//go through entries
  while(!found && !dictionary.eof()) {
    splitOnSpace(line, word, entry);
    if (w == word) {
      found = true;
    }
    getline(dictionary,line);
  }
  dictionary.close();
  return (found);
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

void allCaps(string& s) {
  for (int i = 0; i < s.size(); i++) {
    if (s[i] >= 'a' && s[i] <= 'z') {
      s[i] = (char) ((int) s[i] - 32);
    }
  }
return;
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
