// Nate Sands
// CSc21200
// Prof. Crupi
// Fall 2019
// Assignment 2
//
// FILE: sequence.cxx
// IMPLEMENTS: functions of the sequence class
// INVARIANT:  
// 1. Items are stored in a linked list in their sequence order.
//  
// 2. The variable many_nodes stores the number of nodes in the list.
// 
// 3. The head and tail pointers are stored in head_ptr and
// tail_ptr.  If the sequence is empty, both point to NULL.
//
// 4. The pointer cursor points to the current item.  If
// there is no current item or if the sequence is empty it
// points to NULL.
//
// 5.  The pointer precursor points to the node before the
// current item.  If the current item is the head of the
// sequence, or if the sequence is empty, it points to NULL.


#include <cassert>
#include <cstdlib>
#include "node.h"
#include "sequence.h"
using namespace std;

namespace ccny_fall19_2
{
    
  sequence::sequence()
  {
    head_ptr = tail_ptr = NULL;
    cursor = precursor = NULL;
    many_nodes = 0;
  }
  
  sequence::sequence(const sequence& source)
  {
    // Case:  source sequence has no current item
    if (source.cursor == NULL)
    {
      list_copy(source.head_ptr, head_ptr, tail_ptr);
      many_nodes = source.many_nodes;
      cursor = precursor = NULL;
    }
    // Case: current item of source is first item
    else if (source.cursor == source.head_ptr)
    {
      list_copy(source.head_ptr, head_ptr, tail_ptr);
      many_nodes = source.many_nodes;
      precursor = NULL;
      cursor = head_ptr;
    }
    // Case:  current item of source is after first item
    else
    {
      assert(source.precursor != NULL);
      assert(source.head_ptr != NULL);
      head_ptr = NULL;
      tail_ptr = NULL;
      many_nodes = source.many_nodes;

      node* source_ptr = source.head_ptr;
      // make head node of new list 
      list_head_insert(head_ptr, source_ptr->data());
      precursor = head_ptr;
      //copy up to and including source.precursor
      //loop should finish source_ptr = source.cursor
      //
      for (source_ptr = source_ptr->link(); source_ptr != source.cursor;
           source_ptr = source_ptr->link())
      {
        list_insert(precursor, source_ptr->data());
        precursor = precursor->link();
      }
      // create new node equal to source.cursor
      list_insert(precursor, source_ptr->data());
      cursor = precursor->link(); 
      tail_ptr = cursor;
     // copy from source.cursor to end
      for (source_ptr = source_ptr->link(); source_ptr != NULL;
           source_ptr = source_ptr->link())
      {
        list_insert(tail_ptr, source_ptr->data());
        tail_ptr = tail_ptr->link();
      }
    }
  }

  sequence::~sequence()
  {
    list_clear(head_ptr);
    tail_ptr = cursor = precursor = NULL;
    many_nodes = 0;
  }

  void sequence::start()
  {
    cursor = head_ptr;
    precursor = NULL;
  }

  void sequence::advance()
  {
    assert( is_item() ); 
    if ( cursor->link() == NULL)
      cursor = precursor = NULL;
    else
    { 
      precursor = cursor; 
      cursor = cursor->link();
    }
  }

  void sequence::insert(const value_type& entry)
  {
    //Case:  sequence is empty
    if (many_nodes == 0) 
    {
      list_head_insert(head_ptr, entry);
      tail_ptr = head_ptr;
      cursor = head_ptr;
      many_nodes++;
    }
    // Case:  precursor == NULL
    // i.e. cursor == NULL or
    // cursor == head_ptr
    else if ( precursor == NULL)
    {
      list_head_insert(head_ptr, entry);
      cursor = head_ptr;
      many_nodes++;
    }
    // Case: precursor !=NULL 
    // cursor != NULL != head_ptr
    else
    {
      list_insert( precursor, entry);
      cursor = precursor->link();
      many_nodes++;
    }
  }

  void sequence::attach(const value_type& entry)
  {
    // Case:  empty sequence
    if (many_nodes == 0)
    {
      list_head_insert(head_ptr, entry);
      tail_ptr = head_ptr;
      cursor = head_ptr;
      many_nodes++;
    }
    // Case: is_item is true
    else if (is_item())
    {
      list_insert(cursor, entry);
      advance();
      // make sure cursor hasn't
      // advanced past tail_ptr
      if ( tail_ptr == precursor)
        tail_ptr = cursor;
      many_nodes++;
    } 
    // Case: no current item
    else
    {
      list_insert(tail_ptr, entry);
      precursor = tail_ptr;
      tail_ptr = tail_ptr->link();
      cursor = tail_ptr;
      many_nodes++;
    }
  }
        
  void sequence::operator=(const sequence& source)
  {
    if (this == &source)
      return;
    list_clear(head_ptr);
    many_nodes = 0;
  
    // Case:  source sequence has no current item
    if (source.cursor == NULL)
    {
      list_copy(source.head_ptr, head_ptr, tail_ptr);
      many_nodes = source.many_nodes;
      cursor = precursor = NULL;
    }
    // Case: current item of source is first item
    else if (source.cursor == source.head_ptr)
    {
      list_copy(source.head_ptr, head_ptr, tail_ptr);
      many_nodes = source.many_nodes;
      precursor = NULL;
      cursor = head_ptr;
    }
    // Case:  current item of source is after first item
    else
    {
      assert(source.precursor != NULL);
      assert(source.head_ptr != NULL);
      head_ptr = NULL;
      tail_ptr = NULL;
      many_nodes = source.many_nodes;

      node* source_ptr = source.head_ptr;
      // make head node of new list 
      list_head_insert(head_ptr, source_ptr->data());
      precursor = head_ptr;
      //copy up to and including source.precursor
      //loop should finish source_ptr = source.cursor
      //
      for (source_ptr = source_ptr->link(); source_ptr != source.cursor;
           source_ptr = source_ptr->link())
      {
        list_insert(precursor, source_ptr->data());
        precursor = precursor->link();
      }
      // create new node equal to source.cursor
      list_insert(precursor, source_ptr->data());
      cursor = precursor->link(); 
      tail_ptr = cursor;
     // copy from source.cursor to end
      for (source_ptr = source_ptr->link(); source_ptr != NULL;
           source_ptr = source_ptr->link())
      {
        list_insert(tail_ptr, source_ptr->data());
        tail_ptr = tail_ptr->link();
      }
    }
  }
  
  void sequence::remove_current()
  {
    assert(is_item());
    //Case: single node
    if (many_nodes == 1)
    {
      list_head_remove(head_ptr);
      cursor = tail_ptr = NULL;
      many_nodes = 0;
    }
    // Case: nodes > 1, cursor = head_ptr
    else if (cursor == head_ptr)
    {
      list_head_remove(head_ptr);
      cursor = head_ptr;
      many_nodes--;
    }
    // Case: nodes > 1, cursor != head_ptr, 
    // cursor = tail_ptr
    else if (cursor == tail_ptr)
    {
      tail_ptr = precursor;
      list_remove(precursor);
      cursor = precursor = NULL;
      many_nodes--;
    }
    // Case:  nodes > 1, cursor != head_ptr,
    // cursor != tail_ptr;
    else 
    {
      list_remove(precursor);
      cursor = precursor->link();
      many_nodes--;
    }
  }
  
  sequence::value_type sequence::current() const
  {
    assert(is_item());
    return cursor->data();
  }  
       
}
