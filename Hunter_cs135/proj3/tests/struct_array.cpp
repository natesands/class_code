#include <iostream>
using namespace std;

struct Bot {
  string name;
  string model;
};
bool nameIsJoe(string n) {
  return (n == "Joe");
}

Bot bot[2];

int main() {
  bot[0].name = "Joe";
  bot[1].name = "Murray";
  for (int i=0; i < 2; i++) {
    cout << bot[i].name << endl;
    if (nameIsJoe(bot[i].name)) cout << "His name is Joe." << endl;
    else cout << "His name is not Joe." << endl; 
  }
return 0;
}

