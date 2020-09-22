
/*

Author: Nathaniel Sands
Course: CSCI-136
Instructor: Gwenael Gatto
Assignment: Lab7B

Takes a line of input from user and an number and
returns the text Caesar-shifted by that number.
*/

#include <iostream>
#include <string>
#include <cctype>
using namespace std;

char shiftChar(char c,int rshift);
string encryptCaesar(string plaintext, int rshift);

int main() {

  string line;
  int shift; 

  cout << "Enter plaintext: ";
  getline(cin,line);
  cout << "Enter shift    : ";
  cin >> shift;

  cout << "Ciphertext     : " << encryptCaesar(line, shift) << endl;

return 0;

}
//takes a string and an integer and returns the
//string Caesar-shifted by that integer
string encryptCaesar(string plaintext, int rshift) {

  string mess = ""; 
  for ( int i = 0; i < plaintext.length(); i++) {
   mess += shiftChar(plaintext[i], rshift);
  }

return (mess);
}
//takes char c and int rshift and returns char j
//which has been caesar shifted to the
// right by rshift
char shiftChar(char c, int rshift) {
  
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

