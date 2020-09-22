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
  void copy(const node* source); 
  bool search(int x);
  void chop(node* p);
  void inorder();
  void preorder();
};

class tree {
public:
  tree(){ root = NULL; }
  ~tree();
  tree(const tree& source);
  bool search(int x);
  void inorder();
  void preorder();
  void insert(int x); 
  int max();
  int min();
  bool rsearch(int x);
private:
  node* root;
};

void node::copy(const node* source)
{
  if (source->left != NULL)
  {
    left = new node(source->left->data);
    left->copy(source->left);
  }
  if (source->right != NULL)
  {
    right = new node(source->right->data);
    right->copy(source->right);
  } 
}

tree::tree(const tree& source)
{
  if (source.root != NULL)
  root = new node(source.root->data);
  root->copy(source.root);
}

void node::inorder()
{
  if (left != NULL) left->inorder();
  cout << data << " ";
  if (right != NULL) right->inorder();
}

void node::preorder()
{
  cout << data << " ";
  if (left != NULL) left->preorder();
  if (right != NULL) right->preorder();
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

void node::chop(node* p)
{
  if (p->left != NULL)
    chop(p->left);
  if (p->right != NULL)
    chop(p->right);
  delete p;
}

tree::~tree()
{
  if (root != NULL)
  {
    node* p = root;
    root->chop(p);
  }
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

void tree::preorder()
{
  if (root != NULL)
    root->preorder();
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
void dummyfunc(const tree& source)
{
  tree H(source);
}
int main()
{
  tree T;
  T.insert(5);
  T.insert(2);
  T.insert(4);
  T.insert(883);
  T.insert(55);
  tree T2(T);
  /* test destructor */
  dummyfunc(T);
  cout << "In Order: " << endl;
  T2.inorder();
  cout <<endl;
  cout << "Pre-Order: " << endl;
  T2.preorder();
  cout << endl;
  int z = 883; 
  /* iterative search */
  if (T.search(z))
    cout << z << " found" << endl;
  else cout << z << " not found" << endl;
  /* recursive search */
  if (T.rsearch(z))
    cout << z << " found" << endl;
  else cout << z << " not found" << endl;
  cout << "max: " << T.max() << endl;
  cout << "min: " << T.min() << endl;
  return 0;
}  
