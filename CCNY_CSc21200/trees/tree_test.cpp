#include <cstdlib>
#include <cassert>
#include <iostream>
using namespace std;

struct node {
  int data;
  node* left;
  node* right;
  node(int d, node* l=NULL, node* r=NULL)
  {
    data = d;
    right = r;
    left  = l;
   } 
  bool search(int x);
  void inorder();
};

class tree {
public:
  tree(){ root = NULL; }
  bool search(int x);
  void inorder();
  void insert(int x); 
  int max();
  int min();
  bool rsearch(int x);
private:
  node* root;
};

void node::inorder()
{
  if (left != NULL) left->inorder();
  cout << data << " ";
  if (right != NULL) right->inorder();
}

/* node recursive search */
bool node::search(int x)
{
  if (data == x) return true;
  if (x < data && left != NULL)
    return left->search(x);
  if (x > data && right != NULL)
    return right->search(x);
  return false;
}

/* tree iterative search */
bool tree::search(int x)
{
  node* p = root;
  while (p != NULL)
  {
    if (p-> data == x) return true;
    if (x < p->data) p=p->left;
    else p = p->right;
  }
  return false;
}

/* tree recursive search */
bool tree::rsearch(int x)
{
  return root->search(x);
}

#if 0
/* nope! do not need to make comparison
  if we assume that binary tree condition
  is true! */
int tree::max()
{
  assert(root != NULL);
  node* p = root;
  while (p->right != NULL && p->data < p->right->data)
    p = p->right;
  return p->data;
}

int tree::min()
{
  assert(root != NULL);
  node* p = root;
  while (p->left != NULL && p->data > p->left->data)
    p = p->left;
  return p->data;
}

#else
int tree::max()
{
  assert(root != NULL);
  node* p = root;
  while (p->right != NULL)
    p = p->right;
  return p->data;
}

int tree::min()
{
  assert(root != NULL);
  node* p = root;
  while (p->left != NULL)
    p = p->left;
  return p->data;
}

#endif 
void tree::inorder()
{
  if (root != NULL)
    root->inorder();
}

void tree::insert(int x)
{
  node* y = NULL;
  node* z = root;

  while(z != NULL)
  {
    y = z;
    if (x < z->data)
      z = z->left;
    else z = z->right;
  } 
  if (y == NULL)
    root = new node(x);
  else if (x < y->data)
    y->left = new node(x);
  else y->right = new node(x);
}

int main()
{
  tree T;
  T.insert(5);
  T.insert(2);
  T.insert(4);
  T.insert(883);
  T.inorder();
  cout << endl;
  int z = 7; 
  /* iterative search */
  if (T.search(z))
    cout << z << " found" << endl;
  else cout << z << " not found" << endl;
  /* recursive search */
  if (T.search(z))
    cout << z << " found" << endl;
  else cout << z << " not found" << endl;
  cout << "max: " << T.max() << endl;
  cout << "min: " << T.min() << endl;
  return 0;
}  
