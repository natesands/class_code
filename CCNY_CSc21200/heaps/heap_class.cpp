#include <cstdlib>
#include <iostream>
using namespace std;

#define left(i) = 2*i+1
#define right(i) = 2*i +2
#define parent(i) = (i-1)/2

class heap {
public:
  const static int CAPACITY = 50;
  heap();
  /* maintain min_heap property at index i */
  void  min_heapify(size_t i);
  /* maintain max_heap property at index i */
  void max_heapify(size_t i);
  void build_max_heap();
  void build_min_heap();
  void min2max_sort();
  void max2min_sort();
  void input();
  void insert();
  void print();

private:
  int* data;
  size_t size;
  bool max_heap;
};

heap::heap()
{
  data = new int[CAPACITY];
  size = 0;
}

void heap::input()
{
  while ( cin >> num && num >=0 && size < CAPACITY)
    data[size++] = num;
}
/* do not forget recursive call at end */
void min_heapify(size_t i)
{
  if (i >= n) return;
  size_t l = left(i);
  size_t r = right(i);
  size_t smallest = i;
  if (l < n && data[l] < data[i])
    smallest = l;
  if (r < n && data[r] < data[smallest])
    smallest = r;
  if (smallest != i)
  {
    int temp = data[i];
    data[i] = data[smallest];
    data[smallest] = temp;
  }
  min_heapify(smallest);
}
 
  
  
