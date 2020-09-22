#include <iostream>
using namespace std;


void ast(int num) {

  if (num ==1) {
    cout << "*";
  }
  else {
    ast(num-1);
    cout << "*";
  }
}

int main() {

  int num = 4;
  ast(num);
  cout << endl;
}


