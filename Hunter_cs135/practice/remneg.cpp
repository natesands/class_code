#include <iostream>
using namespace std;

void removeNegs(int data[],int &size, int neg[],int &negSize);
int main () {

  int data[] = {1,5,-3,4,12,-19,6};
  int neg[10];
  int size = 7;
  int negSize = 10;
  for (int i = 0; i < size; i++) {
    cout << data[i] << " ";
  }
  cout << endl;
  removeNegs(data, size, neg, negSize);

  for (int i = 0; i < size; i++) {
    cout << data[i] << " ";
  }
  cout << endl;
  for (int i = 0; i < negSize; i++) {
    cout << neg[i] << " ";
  }
  cout << endl;
}
//remove all neg from data and put in array neg
//update size and negsize
void removeNegs(int data[],int &size, int neg[],int &negSize) {
  negSize = 0; 
  //arr through index i-1 contains all pos; size = num elements in array; 
  for (int i=0; i < size; i++) {
    if (data[i] < 0) {
      neg[negSize] = data[i];
      negSize++;
      for (int j = i; j < size -1; j++) {
        data[j] = data[j+1];
      }
      size--;
     }
  }
} 
