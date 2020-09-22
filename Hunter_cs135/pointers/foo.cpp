#include <iostream>
using namespace std;


void foo (int *xval, int *&xref) {
  cout << "ADDRESS of xval in memory is " << &xval << endl;
  cout << "VALUE stored in xval is ths memory address " << xval << endl;

  cout << "ADDRESS of xref in memory is " << &xref << endl;
  cout << "VALUE stored in xref is ths memory address " << xref << endl;

  xval = new int(1);
  xref = new int(2);
}
int main() {

  int *p1, *p2;
  p1 = new int(5);
  p2 = new int(6);
  cout << "ADDRESS of p1 in memory is " << &p1 << endl;
  cout << "VALUE stored in p1 is then memory address is " << p1 << endl;
  cout << "VALUE stored in that memory address is " << *p1 << endl << endl;


  cout << "ADDRESS of p2 in memory is " << &p2 << endl;
  cout << "VALUE stored in p2 is then memory address is " << p2 << endl;
  cout << "VALUE stored in that memory address is " << *p2 << endl << endl;
  foo(p1,p2);
  cout << *p1 << " " << *p2 << endl;
}

