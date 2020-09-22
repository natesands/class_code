#include <iostream>
#include "counting_sort.h"
using std::cout;
using std::endl;
int* counting_sort(int* A, int size, int k) {
  // assert: max elem of A  <= k
  int* B = new int[size];
  int* C = new int[k+1];

  for (int i=0; i <= k; i++) 
    C[i] = 0;

  for (int j = 0; j < size; j++) 
    C[A[j]] += 1;

  for (int i=1; i < k; i++)
    C[i] = C[i] + C[i-1];

  for (int j = size-1; j >= 0; j--) {
    B[C[A[j]]] = A[j];
    C[A[j]] -= 1;
  }

  return B;
}  

void get_args(int* A, int size, char** argv)
{
  for (int i=0; i < size; i++)
    A[i] = atoi(argv[i+1]);
}

void print_results(int* A, int size)
{
  for (int i=0; i < size; i++)
    cout << A[i] << " ";
  cout << endl;
}


int max(int* A, int size) {
// assert: A contains only non-neg integers
  int k = 0;
  for (int i=0; i<size; i++) {
    if (A[i] > k)
      k = A[i];
  }
  return k;
}
