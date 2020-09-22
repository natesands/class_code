#include <iostream>
#include <cctype>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

// prototype addPhoneme function
bool inDictionary(string w);
void splitOnSpace(string s, string& before, string& after);
void allCaps(string& s);
bool ignoreWord(string s);

int main() {

  string word;
  string additional; 

//prompt user for word
  cout << "Enter word: ";
  cin >> word;
//check if word is in dictionary
//and invoke addPhoneme func
  if (!inDictionary(word)) {
    cout << "Not found." << endl;
  }
  else {
    cout << "Add phoneme   : " + addPhoneme(dictionary,word);
  }

return 0;
}
//takes string entered by user
//checks dictionary for entry
//return true if in dictionary,false if not
bool inDictionary(string w) { 

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
//convert input word to all caps
  w = allCaps(w);
//if word contains non-alpha besides apostrophe,
//return false
  if(ignoreWord(w)) return(false);
//otherwise search dictionary

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
  return (found)   
}


bool ignoreWord(string s);
