#include <iostream>
using namespace std;

enum Operation {ADD, SUBTRACT};

int arith(Operation op, int a, int b) {

  switch (op) {
    case ADD : return (a+b);
    case SUBTRACT : return (a-b);
  }
}

int main () {
  int a,b;
  cout << "Enter two numbers: ";
  cin >> a >> b;

  cout << arith(ADD, a, b) << endl;
  cout << arith(SUBTRACT, a,b) << endl;
return 0;
}


