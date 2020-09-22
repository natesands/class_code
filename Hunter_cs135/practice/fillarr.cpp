#include <iostream>
using namespace std;

typedef int* IntPtr;


void fillArray(int a[], int size);

int search(int a[], int size, int target);


int main() {
  int index; 
  int target;
  int size;
  IntPtr a;

  cout << "how many numbers? " << endl;
  cin >> size;

  a = new int[size];

  fillArray(a,size);

  cout << "enter target number: " << endl;
  cin >> target;
  index = search(a,size,target);
  
  delete [] a;

  if (index  == -1)
    cout << "number not found" << endl;
  else 
    cout << "index is " << index << endl;

return 0;
}

void fillArray(int a[],int size) {
  cout << "enter " << size << " numbers: ";

  for (int i=0; i < size; i++)
    cin >> a[i];
}
int search(int a[], int size, int target) {
  for (int i=0; i < size; i++) {
    if (a[i] == target) return i;
  }
  return -1;
}

