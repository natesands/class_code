#include <iostream>
using namespace std;

void writeVert(int num) {

  if (num < 10 ){
    cout << num << endl;
  }
  else {
    writeVert(num/10);
    cout << num%10 << endl;
  }
}
int main() {

  int num = 45954;

  writeVert(num);

}

