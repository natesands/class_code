/*

sorts an array 

*/

#include <iostream>
using namespace std;


void sort(int arr[], int size);

int main() {

  int a[] = {3,5,20,-1,2,-8,1};
  int size = 7;
  for (int i=0; i < size; i++) {
    cout << a[i] << " " ;
  }
  cout << endl;
   
  sort(a,size);
   
  for (int i=0; i < size; i++) {
    cout << a[i] << " " ;
  }
}

void sort(int arr[], int size) {

  //inv arr[0....i-1] is sorted; 
  int ind = 0;
  int min = 99999;
  int temp;
  for (int i = 0; i < size-1; i++) {
    ind = i+1;
    min = arr[i+1];
    for (int j = i+1; j < size; j++) {
      //inv min = smallest num in arr[i+1...j]; ind has index of min
      if (arr[j] < min) {
        min = arr[j];
        ind = j;
      } 
    } //assert: min = smallest num in arr[i+1...j]; ind has index of min;
    if (min < arr[i]) {
      temp = arr[i];
      arr[i] = min;
      arr[ind]= temp;
    }
  }
}  
