#include <iostream>
#include <cstdlib>
using namespace std;

class stack {
public:
  const static size_t CAPACITY = 50;
  stack(size_t init_size = CAPACITY) {
    size = init_size;
    data = new int[init_size];
    used = 0; }
  ~stack() { delete [] data; }
  stack(const stack& source) {
    data = new int[source.size];
    size = source.size;
    used = source.used;
    for (size_t i = 0; i < used; i++)
      data[i] = source.data[i];
  }
  bool stack_empty() { return used == 0; }
  void push(int x) { 
    assert(used < size);
    data[used++] = x; }
  void pop() { used--; }
  int top() { return data[used-1]; }
private:
  int* data;
  size_t size;
  size_t used; 
  
};

int main()
{
  stack s(10);
  stack t(s);
  t.push(2);
  t.push(7);
  t.pop();
  
  cout << t.top() << endl;

  return 0;
}

