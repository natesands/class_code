#include <iostream>
#include <cstdlib>
using namespace std;

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

void insert_sort(int *A, int size)
{
  int i, key;
  for (int j=1; j < size; j++)
    // A[0...j-1] is a sorted array
  {
    key = A[j];
    i = j-1;
    while (i >= 0 && A[i] > key) {
      A[i+1] = A[i];
      i = i -1;
    }
    A[i+1] = key;
  }
}
     
int main(int argc, char **argv)
{
  int A[12];
  int size = argc - 1;
  get_args(argc, argv, A);
  insert_sort(A, size);
  print_results(A, size);

  return 0;
}


