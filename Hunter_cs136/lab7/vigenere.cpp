
/*

Author: Nathaniel Sands
Course: CSCI-136
Instructor: Gwenael Gatto
Assignment: Lab7C

Takes a line of input from the user and a keyword
and encodes the line using Vigenere Cipher method.

*/

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

char shiftChar(char c, int rshift);
string encryptVigenere(string plaintext, string keyword);
int nextShift(string keyword);

int main () {

  string line, keyword;
  
  cout << "Enter plaintext: ";
  getline(cin,line);
  cout << "Enter keyword  : ";
  cin >> keyword;
  
  cout << "Ciphertext     : " + encryptVigenere(line, keyword) << endl;

return 0;
}
//takes string of characters and a keyword
//and returns the string encrypted using
//Vigenere method
string encryptVigenere(string plaintext, string keyword) {

  string mess="";
  
  for (int i = 0; i < plaintext.length(); i++) {
    if (isalpha(plaintext[i])) {
      mess += shiftChar(plaintext[i],nextShift(keyword));
    }
    else {
      mess += plaintext[i];
    }
  }
  return (mess);
}
//takes keyword and returns amount by which the
//next character in the string should be shifted
int nextShift(string keyword) {

  static int index = 0;
  int shift;

  shift = (keyword[index % keyword.length()] - 'a');
  index++;

return (shift);
}

//takes a character and a integer and shifts
//the character along the alphabet by that amount
char shiftChar(char c, int rshift) {

  char j;
  int distance, wrap;
  
  if ( (int) c >= 'A' && (int) c <= 'Z') {
    distance = (int) c - (int) 'A';
    wrap = (distance + rshift) % 26;
    j = 'A' + wrap;
  }
  else {
    distance = (int) c - (int) 'a';
    wrap = (distance + rshift) % 26;
    j = 'a' + wrap;
  }
return(j);
}

