#include <iostream>
using namespace std;

typedef double* DoublePtr;
double* doubleArr(double a[],int size);

int main() {
  DoublePtr a, aDub;
  int size;

  cout << "Enter size: ";
  cin >> size;

  a = new double[size];
  cout << "enter " << size << " doubles: ";

  for (int i = 0; i < size; i++) {
    cin >> a[i];
  }

  aDub = doubleArr(a,size);

  for (int i = 0; i < size; i++) {
    cout << a[i] << " ";
  }
  cout << endl;
  for (int i = 0; i < size; i++) {
    cout << aDub[i] << " ";
  }
  cout << endl;

  for (int i=0; i < size; i++) {
    cout << a+i << endl;
  }
  delete [] a; delete [] aDub;
  return 0;
}

double* doubleArr(double a[],int size) {
  double * newArr = new double[size];

  for (int i =0; i < size; i++) {
    newArr[i] = 2*a[i];
  }
  return newArr;
}
