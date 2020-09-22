/*

Author: Nathaniel Sands
Course: CSCI-136
Instructor: Gwenael Gatto
Assignment: Lab7D

Takes a line of input from the user and a keyword.
Encrypts the line using the Caesar shift and Vigenere methods.
Decrypts the line for each method using different functions.

*/

#include <iostream>
#include <cctype>
#include <string>
using namespace std;

char shiftCharC(char c, int rshift);
char shiftCharV(char c, int rshift);
string encryptCaesar(string plaintext, int rshift);
string encryptVigenere(string plaintext, string keyword);
int nextShift(string keyword);
string decryptCaesar(string ciphertext, int rshift);
char lshiftCharC(char c, int lshift);
string decryptVigenere(string ciphertext, string keyword);
char lshiftCharV(char c, int lshift);
int nextShiftD(string keyword);
int main () {

  string line, keyword, ciphertext;
  int shift;

  cout << "Enter plaintext: ";
  getline(cin, line);
  cout << "\n";
//Caesar 
  cout << "= Caesar =\n";
  cout << "Enter shift    : ";
  cin >> shift; 
  ciphertext = encryptCaesar(line,shift);
  cout << "Ciphertext     : " + ciphertext + "\n";
  cout << "Decrypted      : " + decryptCaesar(ciphertext, shift);
  cout << "\n\n";
//Vigenere
  cout << "= Vigenere =\n";
  cout << "Enter keyword  : ";
  cin >> keyword;
  ciphertext = encryptVigenere(line,keyword);
  cout << "Ciphertext     : " + ciphertext + "\n";
  cout << "Decrypted      : " + decryptVigenere(ciphertext,keyword);
  cout << endl;

return 0;
}
//takes a string and an integer and returns the
//string Caesar-shifted by that integer
string encryptCaesar(string plaintext, int rshift) {

  string mess = ""; 
  for ( int i = 0; i < plaintext.length(); i++) {
   mess += shiftCharC(plaintext[i], rshift);
  }

return (mess);
}
//takes char c and int rshift and returns char j
//which has been caesar shifted to the
// right by rshift
char shiftCharC(char c, int rshift) {
  
  char j;  
  int distance, wrap;
  if (isalpha(c)) {
    if ( (int) c >= 'A' && (int) c <= 'Z') {
      distance = (int) c - (int) 'A';
      wrap = (distance + rshift) % 26;
      j = 'A' + wrap;
      return(j);
    }
    else if ( (int) c >= 'a' && (int) c <= 'z') {
      distance = (int) c - (int) 'a';
      wrap = (distance + rshift) % 26;
      j = 'a' + wrap;
      return(j);
    }
  }
return(c);
}
//Decrypts Caesar

string decryptCaesar(string ciphertext, int rshift) {

  string mess = ""; 
  for ( int i = 0; i < ciphertext.length(); i++) {
   mess += lshiftCharC(ciphertext[i], rshift);
  }

return (mess);
}

//Shifts chars to the left
char lshiftCharC(char c, int lshift) {

  char j;  
  int distance, wrap;
  if (isalpha(c)) {
    if ( (int) c >= 'A' && (int) c <= 'Z') {
      distance = (int) c - (int) 'A';
      wrap = (distance + (26 - lshift)) % 26;
      j = 'A' + wrap;
      return(j);
    }
    else if ( (int) c >= 'a' && (int) c <= 'z') {
      distance = (int) c - (int) 'a';
      wrap = (distance + (26 - lshift)) % 26;
      j = 'a' + wrap;
      return(j);
    }
  }
return(c);
}


//encrypts using vigenere method
string encryptVigenere(string plaintext, string keyword) {


  string mess="";
  
  for (int i = 0; i < plaintext.length(); i++) {
    if (isalpha(plaintext[i])) {
      mess += shiftCharV(plaintext[i],nextShift(keyword));
    }
    else {
      mess += plaintext[i];
    }
  }
  return (mess);
}
//shifts char to right
char shiftCharV(char c, int rshift) {

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
//decrypts text encoded using vigenere method
string decryptVigenere(string ciphertext, string keyword) {

  string mess="";
  
  for (int i = 0; i < ciphertext.length(); i++) {
    if (isalpha(ciphertext[i])) {
      mess += lshiftCharV(ciphertext[i],nextShiftD(keyword));
    }
    else {
      mess += ciphertext[i];
    }
  }
  return (mess);
}
//gets next shift value for vigenere encryption
int nextShift(string keyword) {

  static int index = 0;
  int shift;

  shift = (keyword[index % keyword.length()] - 'a');
  index++;

return (shift);
}
//gets next shift value for vigenere decryption
int nextShiftD(string keyword) {

  static int index = 0;
  int shift;

  shift = (keyword[index % keyword.length()] - 'a');
  index++;

return (shift);
}

char lshiftCharV(char c, int lshift) {

  char j;
  int distance, wrap;
  
  if ( (int) c >= 'A' && (int) c <= 'Z') {
    distance = (int) c - (int) 'A';
    wrap = (distance + (26-lshift)) % 26;
    j = 'A' + wrap;
  }
  else {
    distance = (int) c - (int) 'a';
    wrap = (distance + (26-lshift)) % 26;
    j = 'a' + wrap;
  }
return(j);
}
