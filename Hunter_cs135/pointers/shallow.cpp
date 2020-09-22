#include <iostream>
using namespace std;

class Student {
public:
  string name;
  int *id;
};

int main() {

  Student a, b;

  b.id = new int(757575);
  a = b;
  a.name = "sam";
  b.name = "george";

  cout << "sam's id: " << *b.id << endl;
  cout << "george's id: " << *a.id << endl;
  
  *(b.id) = 454545;


  cout << "sam's id: " << *b.id << endl;
  cout << "george's id: " << *a.id << endl;

  *a.id = 77777;


  cout << b.name << "'s id: " << *b.id << endl;
  cout << a.name << "'s id: " << *a.id << endl;
}
  
