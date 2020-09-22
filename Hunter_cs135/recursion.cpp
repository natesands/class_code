//
//  recursion.cpp
//  
//
//  Created by Nathaniel Sands on 5/8/18.
//

#include <iostream>
#include <cstdlib>
#include <cctype>
#include <string>
using namespace std;

string uc(string s) {
    if (s.length() == 1) {
        char c = s[0];
        if (isupper(c)) return "UC";
        else return s;
    }
    char c = s[0];
    if (isupper(c)) return ("UC" + uc(s.substr(1)));
    else return (c + uc(s.substr(1)));
}
int main() {
    string s;
    cout << "Enter string: ";
    getline(cin,s);
    
    cout << uc(s) << endl;
}
