#ifndef INC_21F_SRCH_NGN_CULLENW_TREE_H
#define INC_21F_SRCH_NGN_CULLENW_TREE_H

#include <iostream>
using namespace std;
template<typename T>
class Tree {
private:
    class Node{
    public:
        T element;
        Node *left;
        Node *right;
        int height;
        Node(const T& theElement,Node *lt=nullptr,Node *rt=nullptr,int h = 0 ):
                element( theElement ), left( lt ), right( rt ), height( h ) { }
    };
    Node *root;
    // get height of -1 if nullptr
    int height(Node* v){
        if(v==nullptr)
            return -1;
        return v->height;
    }
    // get max two num
    int max(int a, int b){
        return a > b ? a : b;
    }

    T& insert(const T& x, Node*& curr){
        if(curr==nullptr)
            curr = new Node(x); // add node
        else if(x < curr->element)
            return insert(x, curr->left); // descend left child
        else if(curr->element < x)
            return insert(x, curr->right); // descend right child
        else if(x == curr->element)
            return curr->element;
        balance(curr);
        return curr->element;
    }
    void balance(Node*& t){
        if(t==nullptr)
            return;
        // case 1 or 2 rotation
        if(height(t->left)-height(t->right)>1){
            if(height(t->left->left)>=height(t->left->right))
                rotateWithLeftChild(t); //c1
            else
                doubleWithLeftChild(t); //c2
        }
        else if(height(t->right)-height(t->left)>1){
            if(height(t->right->right)>=height(t->right->left))
                rotateWithRightChild(t); // c4
            else
                doubleWithRightChild(t); //c3
        }
        t->height = max(height(t->left),height(t->right))+1;
    }
    // rotations
    void rotateWithLeftChild(Node*& k2){
        Node* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max(height(k2->left),height(k2->right))+1;
        k1->height = max(height(k1->left),k2->height)+1;
        k2=k1;
    }
    void rotateWithRightChild(Node*& k1){
        Node* k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max(height(k1->left),height(k1->right))+1;
        k2->height = max(height(k2->right),k1->height)+1;
        k1 = k2;
    }
    void doubleWithLeftChild(Node*& k3){
        rotateWithRightChild(k3->left);
        rotateWithLeftChild(k3);
    }
    void doubleWithRightChild(Node*& k1){
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }

    T* getElement(const T& x, Node*& curr){
        if(curr==nullptr)
            return nullptr; // doesn't exist
        if(x < curr->element)
            return getElement(x, curr->left); // descend left child
        else if(curr->element < x)
            return getElement(x, curr->right); // descend right child
        else if(curr->element == x)
            return &curr->element; // exists
        else    return nullptr;
    }
    // check if copy is called
    Tree(const Tree &rhs): root(nullptr) { *this = rhs; }
    // to clear tree
    void emptyTree(Node* n){
        if(n!=nullptr){
            emptyTree(n->left);
            emptyTree(n->right);
            delete n;
        }
    }
    void output(Node* n){
        if(n!=nullptr){
            output(n->left);
            cout<<n->element<<endl;
            output(n->right);
        }
    }

public:
    // default constructor
    Tree(): root(nullptr) {}
    // destructor
    ~Tree() {
        emptyTree(root);
    }

    // public interface functions
    T& insert(const T &x) {
        return insert(x, root);
    }
    T* getElement(const T &x) {
        return getElement(x, root);
    }
    void output(){
        output(root);
    }

};

#endif //INC_21F_SRCH_NGN_CULLENW_TREE_H
