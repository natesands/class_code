/* 
Author: Nathaniel J. Sands
Course: CSCI-135
Instructor: Prof. Subash Shankar
Assignment: Project 2

User enters word.  Program searchs CMU Pronouncing Dictionary
and returns the word's pronunciation and list of words with:
  1) identical pronunciations;
  2) pronunciations with one additional phoneme;
  3) pronunciations with one less phoneme;
  4) ponunciations with one phoneme replaced.
*/

#include <iostream>
#include <cctype>
#include <string>
#include <fstream>
#include <cstdlib>
using namespace std;

void lookup(string w,bool& inDict,string& pron); 
void getNextEntry(ifstream& dict,string& w,string& pron,bool& dictOpen);
bool ignoreWord(string s);
void allCaps(string& s);
void splitOnSpace(string s, string& before, string& after);
string trimLeadingSpace(string s);
int countPhones(string s);
string removePhone(string s, int n);
bool hasAddPhone(string s1, string s2);
string getNthPhone(string s,int n);
bool hasReplacedPhone(string s1, string s2);

int main() {
 
  string userWord,dictWord;
  string userWordPron,dictWordPron;
  bool dictIsOpen,inDictionary;
  int numUserWordPhones;
  int numDictWordPhones;
  string identical, additional;
  string removeOne, replaceOne;
  ifstream dictionary; 
  string line;

  //prompt user for word
  cout << "Enter word: ";
  cin >> userWord;
  //convert userWord to all Caps
  allCaps(userWord);
  //lookup userWord and get 
  //pronunciation 
  lookup(userWord,inDictionary,userWordPron);

  //exit if word not found
  if(!inDictionary) {
    cout << endl;
    cout << "Not found." << endl;
    exit(1);
  }

  //open dictionary and skip header lines;
  //declare dictionary open
  dictionary.open("cmudict.0.7a");
  if (dictionary.fail()) {
    cerr << "file open failed" << endl;
  exit(1);
  }
  do {
    getline(dictionary,line);
  } while (line[0] == ';');
  dictIsOpen = true;

  //compare userWord to dictionary
  //entries...
  while(dictIsOpen) {
    //fetch a word
    getNextEntry(dictionary,dictWord,dictWordPron,dictIsOpen);  
    //...check for identical pronunciations...
    if (userWordPron == dictWordPron && userWord != dictWord &&
        !ignoreWord(dictWord)) 
      identical += dictWord + " "; 
    //...check if dict word differs by one additional
    //phoneme...
    if (countPhones(dictWordPron) == countPhones(userWordPron) + 1) {
      if (hasAddPhone(dictWordPron, userWordPron) && !ignoreWord(dictWord))
        additional += dictWord + " ";
    }
    //...check if dict word is user word with one phoneme
    //removed...
    if (countPhones(dictWordPron) == countPhones(userWordPron) - 1) {
      if (hasAddPhone(userWordPron, dictWordPron) && !ignoreWord(dictWord))
        removeOne += dictWord + " ";
    }        
    //...check if dict word is user word with one phoneme
    //replaced.
    if (countPhones(dictWordPron) == countPhones(userWordPron)) {
      if (hasReplacedPhone(dictWordPron,userWordPron) && !ignoreWord(dictWord))
        replaceOne += dictWord + " ";
    }  
  }


  //output results
  cout << endl;
  cout << "Pronunciation   : " + userWordPron << endl << endl;
  cout << "Identical       : " + identical << endl;
  cout << "Add phoneme     : " + additional << endl;
  cout << "Remove phoneme  : " + removeOne << endl;
  cout << "Replace phoneme : " + replaceOne << endl;
return 0;
}
//takes word w
//checks if legal word, and if in dictionary
//sets pron to its pronunciation
//and inDict to true 
 
void lookup(string w,bool& inDict,string& pron) {
  ifstream dict;
  string line,word,entry;
  bool found = false;
  pron = "";        

  //check if w is in dictionary
  if (ignoreWord(w)) inDict = false;
  else {  
    //open dictionary
    dict.open("cmudict.0.7a");
    if (dict.fail()) {
      cerr << "file open failed" << endl;
    exit(1);
    }
    //skip lines beginning with ';'
    do {
      getline(dict,line);
    } while (line[0]==';');
    //go through entries
    while(!found && !dict.eof()) {
      splitOnSpace(line, word,entry);
      if (w == word) found = true;
      else getline(dict,line);
    }
    if(found) {
      inDict = true;
      pron = trimLeadingSpace(entry);
    }
    dict.close();
  }
return;
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

//grabs next entry in dictionary
//splits it into dictWord and pron
 
void getNextEntry(ifstream& dict,string& w,string& pron,bool& dictOpen) {

  string line;
  string before, after;
  //grab line 
  getline(dict,line);
  //split it and set w to before
  splitOnSpace(line,before,after);
  w = before;
  //if after has leading space, trim it
  //set pron to after
  pron = trimLeadingSpace(after);
  //if at EOF declare dictionary closed
  if (dict.eof()) dictOpen = false; 
}

//takes string.  if it has a leading space
//returns string with the space removed
string trimLeadingSpace(string s) {

  string trimmedS="";

  if (s[0] == ' ') {
    for (int i=1; i < s.length(); i++) {
        trimmedS += s[i];
    }
  return(trimmedS);
  }
  else return(s);
}
//returns number of phonemes in string
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

//takes two strings s1 and s2 and
//returns true if s1 is identical to
//s2 except for having an extra phoneme 
bool hasAddPhone(string s1, string s2) {

  bool match = false;
  int len = countPhones(s1);
  int i = 1;
  //remove phones one by one from s1 and check against s2
  while (i <= len && !match) {
    if (removePhone(s1,i) == s2) match = true;
    else i++;
  }
return(match);
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

