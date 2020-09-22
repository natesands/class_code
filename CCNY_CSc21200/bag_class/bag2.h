#ifndef BAG_2H
#define BAG_2H
#include <cstdlib> // provides size_t

namespace bag_2h
{
  class bag
  {
  public:
    typedef int value_type;
    typedef std::size_t size_type;
    static const size_type DEFAULT_CAPACITY = 30;
    
    bag(size_type initial_capacity = DEFAULT_CAPACITY);
    bag(const bag& source);
    ~bag();
    
    void reserve(size_type new_capacity);
    bool erase_one(const value_type& target);
    size_type erase(const value_type& target);
    void insert(const value_type& entry);
    void operator+=(const bag& addend);
    void operator=(const bag& source);
    
    size_type size() const { return used; }
    size_type count(const value_type& target) const;

  private:
    value_type *data;
    size_type used;
    size_type capacity;
  };
  
  bag operator+(const bag& b1, const bag& b2);
}

#endif
 
