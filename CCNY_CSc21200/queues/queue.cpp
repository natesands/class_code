#include <iostream>
#include <cstdlib>
using namespace std;


class queue {
public:
  queue() { 
    data = new int[10];
    head = tail = 0 ; // queue is empty
   }
  void enqueue(int x) {
   // TODO: check if queue is full
    data[tail] = x;
    if (tail = length - 1)
      tail = 0;
    else tail++;
  }
  void dequeue() {
    // TODO: check if stack is empty
    if (head = length - 1)
      head = 0;
    else 
      head++;
  }
   
private:
  int* data;
  size_t head;
  size_t tail;
  size_t length = 10; 
};


