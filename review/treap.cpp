//A treap implementation
#include <cstdlib>
#include <ctime>
#include <iostream>

struct Node
{
    int val;
    Node * lc;
    Node * rc;
    int priority;
    Node(int x):val(x), lc(nullptr), rc(nullptr), priority(std::rand() % RAND_MAX) {}
};

class Treap
{
    public:
        Treap():root(nullptr) { std::srand(std::time(0)); }
        ~Treap() { dispose(root); }
        void inspect();
        void insert(int x) { _insert(root, x); }
        void remove(int x);
    private:
        Node * root;
        void dispose(Node * p);
        void rot_left(Node * & p);
        void rot_right(Node * & p);
        void display(Node * p);
        void _insert(Node * & p, int x);
};

void Treap::rot_left(Node * & p)
{
    Node * x = p->rc;
    p->rc = x->lc;
    x->lc = p;
    p = x;
}

void Treap::rot_right(Node * & p)
{
    Node * x = p->lc;
    p->lc = x->rc;
    x->rc = p;
    p = x;
}

void Treap::dispose(Node * p)
{
    if(p){
        dispose(p->lc);
        dispose(p->rc);
        delete(p);
    }
}

void Treap::display(Node * p)
{
    if(p){
        display(p->lc);
        std::cout << p->val << " ";
        display(p->rc);
    }
}

void Treap::inspect()
{
    std::cout << "========================" << std::endl;
    display(root);
    std::cout << std::endl;
    std::cout << "========================" << std::endl;
}

void Treap::_insert(Node * & p, int x)
{
    if(p){
        if (x <= p->val){
            _insert(p->lc, x);
        }else{
            _insert(p->rc, x);
        }
    }else{
        p = new Node(x);
    }
    if (p->lc && p->lc->priority > p->priority){
        rot_right(p);
    }
    if (p->rc && p->rc->priority > p->priority){
        rot_left(p);
    }
}

void Treap::remove(int x)
{
    Node ** cur = &root;
    while(true){
        if (*cur == nullptr)
            return;
        if ((*cur)->val == x)
            break;
        if ((*cur)->val > x){
            cur = &((*cur)->lc);
        }else{
            cur = &((*cur)->rc);
        }
    }
    while((*cur)->lc || (*cur)->rc){
        if ((*cur)->lc && (*cur)->rc){
            if ((*cur)->lc->priority > (*cur)->rc->priority){
                rot_right(*cur);
                cur = &((*cur)->rc);
            }else{
                rot_left(*cur);
                cur = &((*cur)->lc);
            }
        }else if ((*cur)->lc){
            rot_right(*cur);
            cur = &((*cur)->rc);
        }else{
            rot_left(*cur);
            cur = &((*cur)->lc);
        }
    }
    delete *cur;
    *cur = nullptr;
}

int main()
{
    Treap treap;
    int x;
    std::cin >> x;
    while(x){
        if (x > 0){
            treap.insert(x);
        }else{
            treap.remove(-x);
        }
        treap.inspect();
        std::cin >> x;
    }
    return 0;
}
