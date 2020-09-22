#include <iostream>
using namespace std;

int main() {

  int number, sum, sign;
  char op;
  sum = 0;
  sign = 1;

  while ( cin >> number) {
    if (cin >> op) {
      if (op == '^') {
        number = number*number;
        cin >> op;
      }
      number = number * sign;
      sum += number;
      if (op == '+') sign = 1;
      if (op == '-') sign = -1;
    }
    else {
     number = number * sign;
     sum += number;
    }
  }
  cout << sum << endl;
return (0);
}
 
