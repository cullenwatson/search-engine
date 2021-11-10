#ifndef INC_21F_FINAL_PROJ_TEMPLATE_AVLTREE_H
#define INC_21F_FINAL_PROJ_TEMPLATE_AVLTREE_H

template<typename T>
class AvlTree {
private:
    class AvlNode{
    public:
        T element;
        AvlNode *left;
        AvlNode *right;
        int height;
        AvlNode(const int & theElement,AvlNode *lt,AvlNode *rt,int h = 0 ):
        element( theElement ), left( lt ), right( rt ), height( h ) { }
    };
    void insert(T& x, AvlNode* node){
        if(t==nullptr)
            t = AvlNode(x, nullptr, nullptr);
        else if(x < t->element)
            insert(x, t->left);
        else if(t->element < x)
            insert(x, t->right);
        balance(t);
    }
    void balance(AvlNode*& t){
        if(t==nullptr)
            return;
        if(height(t->left)-height(t->right)>1)
            if(height(t->left->left)>=height(t->left->right))
                rotateWithLeftChild(t);
            else
                doubleWithLeftChild(t);
    }
    void rotateWithLeftChild(AvlNode*& t){

    }
    void rotateWithRightChild(AvlNode*& t){

    }
    void doubleWithLeftChild(AvlNode*& t){

    }
    void doubleWithRightChild(AvlNode*& t){

    }
    int height(AvlNode* v){
        if(v==nullptr)
            return -1;
        return v->height;
    }

    AvlNode *root;
public:
    AvlTree(): root(NULL) {}

    AvlTree(const AvlTree &rhs): root(NULL) { *this = rhs; }

    ~AvlTree() { makeEmpty(); }

//Other functions that you’d typically find in a BST
    void insert(const T &x) {
        insert(x, root);
    }
};

#endif
