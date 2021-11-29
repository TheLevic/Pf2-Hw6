#include "helpers/Expression.h"
#include "helpers/Token.h"


//Structure for my binary tree
class Node
{
private:
    int data;
    Node *leftchild;
    Node *rightchild;
public:
    //Constructors and Destructors
    Node();
    Node(int key, Node *left, Node *right);
    ~Node();
    
    //Methods
    Node *inorder(Node *root);
    Node *preorder(Node *root);
    Node *postorder(Node *root);
    Node *clear(Node *root);
    Node *search(Node *root, int key); //Search for binary tree traversal
    Node *newNode(int key);
};
