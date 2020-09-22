#include <iostream>
#include <cstdlib>

class node {
public:
  node(const int& init_data = 0, 
    node* init_link = NULL, node* init_prev)
    { data = init_data; link = init_link; }
  void set_data(const int& value) { data = value;}
  void set_link(node* new_link) {link = new_link;}
  int data() const { return data; }
  const node* link() const {return link;}
  node* link() const {return link;}

private:
  int data;
  node* link;
  node* previous;
};

class list {
public:
  list() { 
    headptr=tailptr=cursor=precusor=NULL;
  }
  
private:
  node* headptr;
  node* tailptr;
  node* cursor;
  node* precursor;
  
};
