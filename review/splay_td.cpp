//Splay top-down version
#include <iostream>
struct Node
{
    int val;
    Node * lc;
    Node * rc;
    Node(int x):val(x), lc(nullptr), rc(nullptr) {}
};

class Splay
{
    public:
        Splay() : root(nullptr) {}
        ~Splay() { dispose(root); }
        void insert(int x);
        void remove(int x);
        void inspect();

    private:
        Node * root;

        void rot_left(Node * p);
        void rot_right(Node *p);
        void splay(int x);
        void dispose(Node * p);
        void display(Node * p);
};

void Splay::rot_left(Node * p)
{
    Node * x = p->rc;
    p->rc = x->lc;
    x->lc = p;
}

void Splay::rot_right(Node * p)
{
    Node * x = p->lc;
    p->lc = x->rc;
    x->rc = p;
}

void Splay::splay(int x)
{
    if (root == nullptr) return;
    Node * less = nullptr;
    Node * greater = nullptr;
    Node * lp = nullptr;
    Node * rp = nullptr;
    Node * cur = root;
    while(true){
        if(x < cur->val){
            if(cur->lc){
                if (cur->lc->lc && x < cur->lc->val){
                    rp = cur->lc;
                    if (!greater)
                        greater = cur->lc;
                    Node * t = cur;
                    cur = cur->lc->lc;
                    rot_right(t);
                }else{
                    rp = cur;
                    if (!greater)
                        greater = cur;
                    cur = cur->lc;
                }
            }else{
                break;
            }
        }else if(x > cur->val){
            if (cur->rc){
                if (cur->rc->rc && x > cur->rc->val){
                    lp = cur->rc;
                    if (!less)
                        less = cur->rc;
                    Node * t =cur;
                    cur = cur->rc->rc;
                    rot_left(t);
                }else{
                    lp = cur;
                    if (!less)
                        less = cur;
                    cur = cur->rc;
                }
            }else{
                break;
            }
        }else{
             break;
        }
    }
    if (less){
        lp->rc = cur->lc;
        cur->lc = less;
    }
    if (greater){
        rp->lc = cur->rc;
        cur->rc = greater;
    }
    root = cur;
}

void Splay::dispose(Node * p)
{
    if (p){
        dispose(p->lc);
        dispose(p->rc);
        delete p;
    }
}

void Splay::display(Node * p)
{
    if (p){
        display(p->lc);
        std::cout << p->val << " ";
        display(p->rc);
    }
}

void Splay::inspect()
{
    std::cout << "========================" << std::endl;
    display(root);
    std::cout << std::endl; 
    std::cout << "========================" << std::endl;
}

void Splay::insert(int x)
{
    if (root){
        splay(x);
        if (root->val <= x){
            Node * p = new Node(x);
            p->rc = root->rc;
            root->rc = nullptr;
            p->lc = root;
            root = p;
        }else{
            Node * p = new Node(x);
            p->lc = root->lc;
            root->lc = nullptr;
            p->rc = root;
            root = p;
        }
    }else{
        root = new Node(x);
    }
}

void Splay::remove(int x)
{
    if(root){
        splay(x);
        if (root->val == x){
            Node * lc = root->lc;
            Node * rc = root->rc;
            delete root;
            if (rc){
                root = rc;
                splay(x);
                root->lc = lc;
            }else{
                root = lc;
            }
        }
    }
}

int main()
{
    int x;
    std::cin >> x;
    Splay splay;
    while( x != 0 ){
        if (x >0){
            splay.insert(x);
        }else{
            splay.remove(-x);
        };
        splay.inspect();
        std::cin >> x;
    }
    return 0;
}
