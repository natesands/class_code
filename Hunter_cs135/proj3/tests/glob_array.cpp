#include <iostream>
using namespace std;

int NUM_COL = 5;
int NUM_ROW = 5;
int arr[10][10];

void flipArray(int arr[][10]) {
  int count = 0;
  for (int i = 0; i < NUM_ROW; i++) {
    for (int j = 0; j < NUM_COL; j++) {
        arr[i][j]= count;
        count++;
    }
  }
  return;
}
int main() {
  //set array cells all to zero
  for (int row=0; row<NUM_ROW; row++) {
    for (int col=0; col<NUM_COL; col++) {
      arr[row][col]= 0;
    }
  }
  //change values by function
  flipArray(arr);
  
  //print array
  for(int row=0; row<NUM_ROW; row++){
    for (int col=0; col < NUM_COL; col++) {
      cout << arr[row][col] << " ";
    }
    cout << endl;
  }
  return(0);
} 

  
