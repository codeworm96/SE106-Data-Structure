//An AVLTree implementation
#include <iostream>
using std::max;

struct Node
{
    int val;
    Node * lc;
    Node * rc;
    int h;
    Node(int x) :val(x), lc(nullptr), rc(nullptr), h(0) {}
};

class AVLTree
{
    public:
        AVLTree() :root(nullptr) {}
        ~AVLTree() { dispose(root); }
        void insert(int x) { _insert(root, x); }
        void remove(int x) { _remove(root, x); }
        void inspect();
    private:
        Node * root;
        int height(Node * p);
        void rot_left(Node * & x);
        void rot_right(Node * & x);
        void dispose(Node * p);
        void display(Node * p);
        void _insert(Node * & p, int x);
        void _remove(Node * & p, int x);
        void balance(Node * & p);
        int find_min(Node * p);
};

int AVLTree::height(Node * p)
{
    if (p){
        return p->h;
    }else{
        return 0;
    }
}

void AVLTree::rot_left(Node * & x)
{
    Node * y = x->rc;
    x->rc = y->lc;
    x->h = max(height(x->lc), height(x->rc)) + 1;
    y->lc = x;
    y->h = max(height(y->lc), height(y->rc)) + 1;
    x = y;
}

void AVLTree::rot_right(Node * & x)
{
    Node * y = x->lc;
    x->lc = y->rc;
    x->h = max(height(x->lc), height(x->rc)) + 1;
    y->rc = x;
    y->h = max(height(y->lc), height(y->rc)) + 1;
    x = y;
}

void AVLTree::dispose(Node * p)
{
    if (p){
        dispose(p->lc);
        dispose(p->rc);
        delete p;
    }
}

void AVLTree::display(Node * p)
{
    if (p){
        display(p->lc);
        std::cout << p->val << " ";
        display(p->rc);
    }
}

void AVLTree::inspect()
{
    std::cout << "=====================" << std::endl;
    display(root);
    std::cout << std::endl;
    std::cout << "=====================" << std::endl;
}

void AVLTree::_insert(Node * & p, int x)
{
    if (p){
        if (x <= p->val){
            _insert(p->lc, x);
        }else{
            _insert(p->rc, x);
        }
    }else{
        p = new Node(x);
    }
    balance(p);
}

void AVLTree::_remove(Node * &  p, int x)
{
    if (p){
        if (x == p->val){
            if (p->lc && p->rc){
                p->val = find_min(p->rc);
                _remove(p->rc, p->val);
            }else{
                Node * t = p;
                if(p->lc){
                    p = p->lc;
                }else{
                    p = p->rc;
                }
                delete t;
            }
        }else if (x < p->val){
            _remove(p->lc, x);
        }else{
            _remove(p->rc, x);
        }
        balance(p);
    }
}

void AVLTree::balance(Node * & p)
{
    if (p == nullptr){
        return;
    }
    if (height(p->lc) - height(p->rc) > 1){
        if (height(p->lc->rc) > height(p->lc->lc)){
             rot_left(p->lc);
        }
        rot_right(p);
    }
    if (height(p->rc) - height(p->lc) > 1){
        if (height(p->rc->lc) > height(p->rc->rc)){
             rot_right(p->rc);
        }
        rot_left(p);
    }
    p->h = max(height(p->lc), height(p->rc)) + 1;
}

int AVLTree::find_min(Node * p)
{
    while(p->lc){
        p = p->lc;
    }
    return p->val;
}

int main()
{
    int x;
    AVLTree avl;
    std::cin >> x;
    while(x){
        if (x > 0){
            avl.insert(x);
        }else{
            avl.remove(-x);
        }
        avl.inspect();
        std::cin >> x;
    }
    return 0;
}

