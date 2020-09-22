#include <cstdlib>
#include <iostream>
using namespace std;


#define left(i) 2*i+1
#define right(i) 2*i+2
#define parent(i) (i-1)/2

void max_heapify(int* A, size_t i, size_t n);
void build_max_heap(int* A, size_t n);
void heapsort(int* A, size_t n);
int main()
{
  int* A = new int [50];
  size_t i = 0;
  int num;
  cout << "enter numbers: ";
  // i is the number of entries in A
  while ( cin >> num  && num >= 0 && i < 50)
  {
    A[i] = num;
    i++;
  }
  size_t count = i;
  cout << "count is: " << count << endl;
  cout << "pre-heap: " << endl;
  for (size_t ind = 0; ind < count; ind++)
    cout << A[ind] << " ";
  cout << endl;

  build_max_heap(A, count);
  cout << "max-heap: " << endl; 
  for (size_t ind = 0; ind < count; ind++)
    cout << A[ind] << " ";
  cout << endl;

  heapsort(A, count);
  cout << "sorted: " << endl; 
  for (size_t ind = 0; ind < count; ind++)
    cout << A[ind] << " ";
  cout << endl;
  return 0; 
}
   
void max_heapify(int* A, size_t i, size_t n)
{ 
size_t largest;
  size_t l = left(i);
  size_t r = right(i);
  if (l < n && A[l] > A[i])
    largest = l;
  else largest = i;
  if (r < n && A[r] > A[largest])
    largest = r;
  if (largest != i)
  {
    int temp = A[i];
    A[i] = A[largest];
    A[largest] = temp;
    max_heapify(A, largest, n);
  }
}

void build_max_heap(int* A, size_t n)
{
  for (size_t i = parent(n-1); i != (size_t)-1; i--)
    max_heapify(A, i, n);
}
/* pre: A is an unsorted array *
   post: A is sorted in ascending order */
void heapsort(int* A, size_t n)
{
  build_max_heap(A, n);
  for ( size_t i=n-1; i > 0; i--)
  {
    int temp = A[0];
    A[0] = A[i];
    A[i] = temp;
    max_heapify(A,0,i);
}
}
  








    
