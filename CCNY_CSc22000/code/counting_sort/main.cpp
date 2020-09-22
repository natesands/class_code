#include "counting_sort.h"
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

int main(int argc, char* argv[])
{ 
  size = argc-1;
  int* A = new int[size];

  get_args(A, size, argv); // fill array A
  
  int k = 0;
  k = max(A, size);
  int* B = counting_sort(A, size, k);
  print_results(B, size);
  
  return 0;
}
