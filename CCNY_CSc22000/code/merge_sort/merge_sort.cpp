#include <iostream>
#include <cstdlib> // for atoi
#include <climits> // for sentinel value INT_MAX
#include <cmath> // suplies floor function
using namespace std;

void get_args(int argc, char** argv, int* A) 
{
  for (int i=0; i < argc-1; i++)
    A[i] = atoi(argv[i+1]);
}

void merge(int* A, int p, int q, int r)
/* pre: A[p..q] and A[q+1..r] are sorted 
sub-arrays 
   post: A[p..r] is a sorted array */
{
  int n1 = q - p +1; // # elem first sub-array
  int n2 = r - q; // # elem second sub-array
  int L[n1+1];
  int R[n2+1];
  L[n1] = INT_MAX;
  R[n2] = INT_MAX;
  for (int i=0; i<n1; i++)
    L[i] = A[p + i];
  for (int i=0; i<n2; i++)
    R[i] = A[q+1+i];
  int i = 0;
  int j = 0;
  for (int k=p; k <= r; k++)
  {
    if (L[i] <= R[j]) {
      A[k] = L[i];
      i++;
    }
    else {
      A[k] = R[j];
      j++;
    }
  }
}

void merge_sort(int* A, int p, int r)
/* A array to be sorted, p = first index
 r = last index */
{
  if (r > p) {
    int q = floor ((p + r) / 2.0);
    merge_sort(A, p, q);
    merge_sort(A, q+1, r);
    merge(A, p, q, r);
  }
}

void print_results(int* A, int size)
{
  for (int i = 0; i < size; i++)
    cout << A[i] << " ";
  cout << endl;
}
int main(int argc, char **argv)
{
  int size = argc -1; // size of array to be sorted
  int A[size];
  get_args(argc, argv, A);
  merge_sort(A,0, size-1);
  print_results(A, size);

  return 0;
}
