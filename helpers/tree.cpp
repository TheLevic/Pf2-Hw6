#include "tree.h"
/*These are my methods for my binary tree. I should be able to search through, return inorder, prefix,
and postfix.*/

//Constructors
Node::Node(){
    int data;
    Node *leftchild, *rightchild;
}

Node::Node(int key, Node *left, Node *right){
    data = key;
    leftchild = left;
    rightchild = right;
}

//Methods

//Creat a new node
Node * Node::newNode(int data){
    Node *tmp = new Node();
    tmp->data = data;
    tmp->leftchild = tmp->rightchild = NULL;
    return tmp;
}

//Search through a tree. Returns pointer to the location of key you searched for
Node *Node::search(Node *root, int key){
    if(root == NULL || root->data == key){
        return root;
    }
    else if (root->data < key){
        return search(root->rightchild,key);
    }
    else if (root->data > key){
        return search(root->leftchild,key);
    }
}



/*Node Node::postorder(Node *t){ I don't really know how to implement this
    if (t != NULL){
        postorder(t->leftchild);
        postorder(t->rightchild);


    }
}*/

Node * Node::inorder(Node *t){
    //Need to fill this in. I'm confused on the implementaions of the in,pre,and posterder traversals.
}
