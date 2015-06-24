//Splay bottom-up version
#include <iostream>
struct Node
{
    int val;
    Node * lc;
    Node * rc;
    Node * father;
    Node(int x):val(x), lc(nullptr), rc(nullptr), father(nullptr) {}
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
        void link_as_lchild(Node * p, Node * x);
        void link_as_rchild(Node * p, Node * x);
        void splay(int x);
        void dispose(Node * p);
        void display(Node * p);
};

void Splay::link_as_lchild(Node * p, Node * x)
{
    p->lc = x;
    if (x){
        x->father = p;
    }
}

void Splay::link_as_rchild(Node * p, Node * x)
{
    p->rc = x;
    if (x){
        x->father = p;
    }
}

void Splay::rot_left(Node * p)
{
    Node * x = p->rc;
    link_as_rchild(p, x->lc);
    link_as_lchild(x, p);
}

void Splay::rot_right(Node * p)
{
    Node * x = p->lc;
    link_as_lchild(p, x->rc);
    link_as_rchild(x, p);
}

void Splay::splay(int x)
{
    if (root == nullptr) return;
    Node * pre = nullptr;
    Node * cur = root;
    while (cur){
        if (cur->val == x)
            break;
        pre = cur;
        if (cur->val > x){
            cur = cur->lc;
        }else{
            cur = cur->rc;
        }
    }
    if (cur == nullptr){
        cur = pre;
    }
    while(cur->father){
        Node * p = cur->father;
        if (p->father){
            Node * g = p->father;
            Node * gg = g->father;
            if (gg){
                if (gg->lc == g){
                    gg->lc = cur;
                }else{
                    gg->rc = cur;
                }
            }
            if (g->lc == p){
                if (p->lc == cur){
                    rot_right(g);
                    rot_right(p);
                }else{
                    rot_left(p);
                    rot_right(g);
                }
            }else{
                if (p->lc == cur){
                    rot_right(p);
                    rot_left(g);
                }else{
                    rot_left(g);
                    rot_left(p);
                }
            }
            if (gg){
                cur->father = gg;
            }else{
                cur->father = nullptr;
                root = cur;
            }
        }else{
            if (cur == p->lc){
                rot_right(p);
            }else{
                rot_left(p);
            }
            cur->father = nullptr;
            root = cur;
        }
    }
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
            link_as_rchild(p, root->rc);
            root->rc = nullptr;
            link_as_lchild(p, root);
            root = p;
        }else{
            Node * p = new Node(x);
            link_as_lchild(p, root->lc);
            root->lc = nullptr;
            link_as_rchild(p, root);
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
                rc->father = nullptr;
                root = rc;
                splay(x);
                link_as_lchild(root, lc);
            }else{
                if (lc)
                    lc->father = nullptr;
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
