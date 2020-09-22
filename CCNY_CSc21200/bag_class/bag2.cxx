// FILE: bag2.cxx
// class implemented: bag2


#include <algorithm>
#include <cassert>
#include "bag2.h"
using namespace std;

namespace bag_2h
{
  const bag::size_type bag::DEFAULT_CAPACITY;

  bag::bag(size_type initial_capacity)
  {
    data = new value_type[initial_capacity];
    used = 0;
    capacity = initial_capacity;
  }

  bag::bag(const bag& source)
  {
    data = new value_type[source.capacity];
    used = source.used;
    capacity = source.capacity;
    copy(source.data, source.data + used, data);
  }

  bag::~bag()
  {
    delete [] data;
  }
  
  void bag::reserve(size_type new_capacity)
  {
    if (capacity == new_capacity)
      return;
    if (new_capacity < used)
      new_capacity = used;

    value_type* larger_array;
    larger_array = new value_type[new_capacity]
    copy(data, data + used, larger_array);
    capacity = new_capacity;
    delete [] data;
    data = larger_array;
  }

  bool bag::erase_one(const value_type& target)
  {
    size_type i;
    //data[k] != target 0<=k<i, i != used-1,  
    while (i < used)
    {
      if (data[i] == target)
      {
        --used;
        data[i] = data[used];
        return true;
      }
      i++;
    }
    return false;
  }
  
  size_type bag::erase(const value_type& target)
  {
    size_type erased, index;
    index = 0;
    erased = 0;

    while(index < used)
    {
      if (data[index] = target)
      {
        --used;
        data[index] = data[used];
        ++erased;
      }
      else 
        i++;
    }
    return erased;
  }



    
