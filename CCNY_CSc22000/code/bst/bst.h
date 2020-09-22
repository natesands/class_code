class Node {
public:
  void inorder();

private:
  node* left;
  node* right;
  node* p;
  int data;
};

class BST {
public:
  inorder(node* ndptr); // left-root-right
  preorder(node* ndptr); // root-left-right
  postorder(node* ndptr); // left-right-root

private:
  int size;
  node* root;
};

void Node::inorder()
{
  if (left != NULL) left->inorder();
  cout << data;
  if (right != NULL) right -> inorder();
}

void Node::preorder()
{
  cout << data;
  if (left != NULL) left->preorder();
  if (right != NULL) right->preorder();
}

void Node::postorder()
{
  if (left != NULL) left->postorder();
  if (right != NULL) right->postorder();
  cout << data;
}

