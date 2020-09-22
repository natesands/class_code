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

// returns sum of max crossing subarry,  Updates values of
// i and j such that A[i..j] is max crossing subarray.
int find_max_crossing_subarray(int* A, int low, int mid,
                                int high, int &i, int &j)
{
  int left_sum = INT_MIN;
  int sum = 0;
  for (int index = mid; index >= 0; index--) {
    sum += A[index];
    if (sum > left_sum) {
      left_sum = sum;
      i = index;
    }
  }
  int right_sum = INT_MIN;
  sum = 0;
  for (int index = mid + 1; index <= high; index++) {
    sum += A[index];
    if (sum > right_sum) {
      right_sum = sum;
      j = index;
    }
  }
  return left_sum + right_sum;
}

void print_results(int* A, int i, int j, int sum)
{
  for (int index = i; index <= j; index++)
    cout << A[index] << " ";
  cout << endl;
  cout << "Sum = " << sum << endl;
}

int main(int argc, char **argv)
{
  int size = argc -1; // size of array to be sorted
  int A[size];
  get_args(argc, argv, A); // populate array
  
  int i, j; 
  int low = 0;
  int high = size - 1;
  int mid = (size / 2) ;
  int max_sum = find_max_crossing_subarray(A, low, mid, high, i, j);
    
  print_results(A, i,j, max_sum);

  return 0;
}
