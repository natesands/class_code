#include <iostream>
#include <cstdlib>
using namespace std;

void merge(int* A, int* B, size_t nA, size_t nB, int* S)
{
  size_t iA=0;
  size_t iB=0;
  size_t iS=0;

  while (iA < nA && iB < nB) {
    if (A[iA] < B[iB])
      S[iS++] = A[iA++];
    else
      S[iS++] = B[iB++];
  }
  while( iA < nA ) S[iS++] = A[iA++];
  while( iB < nB ) S[iS++] = B[iB++];
}

void mergesort(int* A, size_t n, int* aux)
{
  if (n < 2) return;
  mergesort(A, n/2, aux);
  mergesort(A+n/2, n-(n/2), aux);
  merge(A, A+n/2, n/2, n-(n/2), aux);
  for (size_t i=0; i<n; i++)
    A[i] = aux[i];
}

void selectionSort(int* A, size_t n)
{
  size_t min;
  for (size_t i=0; i < n-1; i++)
  {
    min = i;
    for (size_t j = i+1; j < n; j++)
    {
      if (A[j] < A[i]) min = j;
    }
    if (min != i) 
    {
      int temp = A[i];
      A[i] = A[min];
      A[min] = temp;
    }
  }
} 

size_t partition(int* A, size_t n)
{
  int x = A[n-1];  //all values will be compared to x
  size_t i = -1;
  // 0 <= k <= i, A[k] < x
  // i+1 <= k <= j-1, A[k] > x
  for (size_t j=0; j < n; j++)
  {
    if (A[j] <= x) 
    {
      i = i+1;
      int temp = A[i];
      A[i] = A[j];
      A[j] = temp;
    }
  }
  int temp = A[i+1];
  A[i+1] = A[n-1];
  A[n-1] = temp;
  
  return i+1;
}

void quicksort(int* A, size_t n)
{
  if (n < 2) return;
  size_t p = partition(A,n);
  quicksort(A,p+1);
  quicksort(A+p+1, n-p-1);
}

void insertionSort(int* A, size_t n)
{
  size_t i = 1;
  size_t j; 

  while ( i < n )
  {
    j = i;
    while (j > 0 && A[j-1] > A[j]) {
      int temp = A[j-1];
      A[j-1] = A[j];
      A[j] = temp;
      j--;
    }
  i++;
  }
}

void countingSort(int* A, int* B, size_t k, size_t n)
{
  int* C = new int[k];
  for (size_t i=0; i < k; i++) 
    C[i] = 0;
  for (size_t j=0; j < n; j++) 
    C[A[j]] = C[A[j]] + 1;  //C now contains freq of values in A
  for (size_t j=1; j < k; j++)
    C[j] = C[j] + C[j-1];
  for (size_t i=n-1; i != (size_t)-1; i--)
  {
    B[C[A[i]]] = A[i];
  }
  delete [] C;
}
      

int main()
{

  int A[]= {123, 425, 656, 222, 718, 455, 843, 782};
  int aux[10];
  for (size_t i=0; i < 8; i++)
    cout << A[i] << " ";
  cout << endl;
   
  cout << "merge sort: " << endl;
  mergesort(A, 8, aux);
  
  for (size_t i=0; i < 8; i++)
    cout << A[i] << " ";
  cout << endl;

 
  int B[]= {2, 4, 2, 5, 3, 9, 1, 2,6,8};
  int C[10];
  cout << "insertion sort: " << endl;
  insertionSort(B, 10);
  
  for (size_t i=0; i < 10; i++)
    cout << B[i] << " ";
  cout << endl;

  return 0;

}
