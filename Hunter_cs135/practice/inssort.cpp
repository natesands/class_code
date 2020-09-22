#include <iostream>
using namespace std;

/* insert an element into a non-decreasing sorted array, keeping
it sorted */


void insertElem(int data[], int maxSize, 
                int &cursize, int elem);

int main() {
  int maxSize = 10;
  int data[maxSize];
  
  data[0] = 1;
  data[1] = 4;
  data[2] = 7;
  data[3] = 15;

  int cursize = 4;
  insertElem(data,maxSize, cursize, 5);
  for (int i=0; i < cursize; i++) {
    cout << data[i] << " " ;
  }
  cout << endl;
  insertElem(data, maxSize, cursize, 6);
  insertElem(data, maxSize, cursize, 16);
  insertElem(data, maxSize, cursize,-1);
  for (int i=0; i < cursize; i++) {
    cout << data[i] << " " ;
  }
  cout << endl;
}
void insertElem(int data[], int maxSize, 
                int &cursize, int elem) {
  int ind = 0;
  //elem is > ints in pos 0 through ind-1;
  while (elem > data[ind] && ind < cursize) ind++;
  //shift all elements one array pos to the right, starting at cursize;
  //insert elem at ind
  for (int i = cursize; i > ind; i--) {
     data[i] = data[i-1];
  }
  data[ind] = elem;
  cursize++;
} 
