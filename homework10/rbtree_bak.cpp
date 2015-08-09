/*
 * Description: A top-down red black tree.
 */
#include <iostream>
#include <stdexcept>
using namespace std;

//The red black tree class
class RBTree
{
    //Node definition
    private:
        struct Node
        {
            bool is_red;  //color
            int key;  
            Node * lchild;
            Node * rchild;
            Node * parent;
            //constructors
            Node(int k): key(k), is_red(true), lchild(NULL), rchild(NULL), parent(NULL) {}
            Node(const Node & other): key(other.key), is_red(other.is_red), lchild(NULL), rchild(NULL), parent(NULL) {}
        };

    //public interface
    public:
        //the simple iterator
        class iterator
        {
            public:
                //constructor
                iterator(RBTree * rbt, Node * x): tree(rbt), p(x) {}

                //next
                iterator operator++()
                {
                    p = tree->succ(p);
                    return *this;
                }

                //comparers
                bool operator==(const iterator & rhs)
                {
                    return (rhs.p == p);
                }

                bool operator!=(const iterator & rhs)
                {
                    return (rhs.p != p);
                }

                //dereference
                int operator*()
                {
                    return p->key;
                }

            private:
                Node * p;
                RBTree * tree;
        };

        //constructors
        RBTree();
        RBTree(const RBTree & other);
        //copy assignment
        RBTree & operator=(const RBTree & other);
        //destructors
        ~RBTree();

        void insert(int k); //insert a key
        void erase(int k);  //erase a key
        int min() const;
        int max() const;

        iterator begin()
        {
            return iterator(this, min(root));
        }

        iterator end()
        {
            return iterator(this, NULL);
        }

    private:
        //The root
        Node * root;

        //link two node (the child can be NULL)
        void link_as_lchild(Node * p, Node * c);
        void link_as_rchild(Node * p, Node * c);

        //rotation
        void rot_left(Node * x);
        void rot_right(Node * x);

        //helpers
        bool is_red(Node * p) const;
        bool is2node(Node * p) const;
        void rebuild(Node * p);

        Node * min(Node * x) const;
        Node * max(Node * x) const;

        //find successor
        Node * succ(Node * x) const;
        //dispose a subtree
        void dispose(Node * x);
        //copy a subtree
        Node * copy(Node * x);
};

//constructor for an empty tree
RBTree::RBTree()
{
    root = NULL;
}

//copy constructor
RBTree::RBTree(const RBTree & other): root(copy(other.root)) {}

//destructor
RBTree::~RBTree()
{
    dispose(root);
}

//copy assignment
RBTree & RBTree::operator=(const RBTree & other)
{
    Node * p = copy(other.root);
    dispose(root);
    root = p;
    return *this;
}

void RBTree::link_as_lchild(Node * p, Node * c)
{
    p->lchild = c;
    if (c){
        c->parent = p;
    }
}

void RBTree::link_as_rchild(Node * p, Node * c)
{
    p->rchild = c;
    if(c){
        c->parent = p;
    }
}

bool RBTree::is_red(Node * p) const
{
    return (p && p->is_red);
}

void RBTree::insert(int k)
{
    Node * p = NULL;
    Node * x = root;
    //adjusting while searching
    while(x){
        if (is_red(x->lchild) && is_red(x->rchild)){
            x->lchild->is_red = false;
            x->rchild->is_red = false;
            if (x != root){
                x->is_red = true;
                if (is_red(x->parent)){
                    rebuild(x);
                }
            }
        }
        if (k < x->key){
            p = x;
            x = x->lchild;
        }else{
            p = x;
            x = x->rchild;
        }
    }

    //insert
    if (p == NULL){
        root = new Node(k);
        root->is_red = false;
    }else{
        Node * t = new Node(k);
        if (k < p->key){
            link_as_lchild(p, t);
        }else{
            link_as_rchild(p, t);
        }
        if (is_red(p)){
            rebuild(t);
        }
    }
}

void RBTree::rebuild(Node * x)
{
    //Note fix the case the p, x are red
    Node * p = x->parent;
    Node * g = p->parent;
    if (p == g->lchild){
        if (x == p->rchild){  //let p, x at the same side
            rot_left(p);
            p = g->lchild;
        }
        rot_right(g);
    }else{
        if (x == p->lchild){  //let p, x at the same side
            rot_right(p);
            p = g->rchild;
        }
        rot_left(g);
    }
    //recolor
    p->is_red = false;
    p->lchild->is_red = true;
    p->rchild->is_red = true;
}

void RBTree::rot_left(Node * x)
{
    Node * p = x->parent;
    Node * y = x->rchild;
    link_as_rchild(x, y->lchild);
    link_as_lchild(y, x);
    //fix the link to parent
    if (p){
        if (x == p->lchild){
            link_as_lchild(p, y);
        }else{
            link_as_rchild(p, y);
        }
    }else{
        root = y;
        y->parent = NULL;
    }
}

void RBTree::rot_right(Node * x)
{
    Node * p = x->parent;
    Node * y = x->lchild;
    link_as_lchild(x, y->rchild);
    link_as_rchild(y, x);
    //fix the link to parent
    if (p){
        if (x == p->lchild){
            link_as_lchild(p, y);
        }else{
            link_as_rchild(p, y);
        }
    }else{
        root = y;
        y->parent = NULL;
    }
}

RBTree::Node * RBTree::min(RBTree::Node * x) const
{
    if(x){
        while(x->lchild){  //keep go left
            x = x->lchild;
        }
    }
    return x;
}

int RBTree::min() const
{
    Node * p = min(root);
    if(p){
        return p->key;
    }else{
        throw std::runtime_error("finding min in an empty tree");
    }
}
    
RBTree::Node * RBTree::max(RBTree::Node * x) const
{
    if(x){
        while(x->rchild){  //keep go right
            x = x->rchild;
        }
    }
    return x;
}

int RBTree::max() const
{
    Node * p = max(root);
    if (p){
        return p->key;
    }else{
        throw std::runtime_error("finding max in an empty tree");
    }
}

//find successor
RBTree::Node * RBTree::succ(RBTree::Node * x) const
{
    if (x->rchild){ //has right subtree?
        return min(x->rchild);
    }else{  //go upward
        Node * p = x->parent;
        while(p && p->rchild == x){
            x = p;
            p = p->parent;
        }
        return p;
    }
}

//Note: to judge if a node is black and all its children are black
bool RBTree::is2node(Node * x) const
{
    if (is_red(x)){
        return false;
    }
    if (x){
        if (is_red(x->rchild)){
            return false;
        }
        if (is_red(x->lchild)){
            return false;
        }
    }
    return true;
}

//Too long, need to split
void RBTree::erase(int k)
{
    //prevent empty tree
    if(root == NULL){
        return;
    }

    //root case
    Node * p = root;
    if (is2node(p)){
        p->is_red = true;
    }

    while(p){
        bool go_left; //direction

        if (k < p->key){
            go_left = true;
        }else{
            if (k > p->key){
                go_left = false;
            }else{
                //2 children, find a replacement
                if (p->lchild && p->rchild){
                    Node * t = min(p->rchild);
                    p->key = t->key;
                    k = t->key;
                    go_left = false;
                }else{
                    //can delete
                    Node * t;
                    if (p->lchild){
                        t = p->lchild;
                    }else{
                        t = p->rchild;
                    }
                    //recolor
                    if (is_red(t)){
                        t->is_red = false;
                    }

                    if (p->parent){
                        if (p->parent->lchild == p){
                            link_as_lchild(p->parent, t);
                        }else{
                            link_as_rchild(p->parent, t);
                        }
                    }else{
                        root = t;
                        if (t){
                            t->parent = NULL;
                        }
                    }
                    delete p;
                    break;
                }
            }
        }

        //move down
        if(go_left){
            if (p->lchild == NULL){
                break;              //Not found
            }
            if (is2node(p->lchild)){  //adjust needed
                //reduce to the case when p is red
                if (!is_red(p)){
                    rot_left(p);
                }
                if(is2node(p->rchild)){ //case 2a1
                    p->is_red = false;
                    p->lchild->is_red = true;
                    p->rchild->is_red = true;
                }else{
                    if(is_red(p->rchild->lchild)){ //case 2a2
                        rot_right(p->rchild);
                        rot_left(p);
                        p->is_red = false;
                        p->lchild->is_red = true;
                    }else{  //case 2a3
                        p->rchild->rchild->is_red = false;
                        p->rchild->is_red = true;
                        rot_left(p);
                        p->is_red = false;
                        p->lchild->is_red = true;
                    }
                }
            }
            p = p->lchild;
        }else{
            if (p->rchild == NULL){
                break;             //Not found
            }
            if (is2node(p->rchild)){ //adjust needed
                //reduce to the case that p is red
                if (!is_red(p)){
                    rot_right(p);
                }

                if(is2node(p->lchild)){  //case 2a1
                    p->is_red = false;
                    p->lchild->is_red = true;
                    p->rchild->is_red = true;
                }else{
                    if(is_red(p->lchild->rchild)){ //case 2a2
                        rot_left(p->lchild);
                        rot_right(p);
                        p->is_red = false;
                        p->rchild->is_red = true;
                    }else{                         //case 2a3
                        p->lchild->lchild->is_red = false;
                        p->lchild->is_red = true;
                        rot_right(p);
                        p->is_red = false;
                        p->rchild->is_red = true;
                    }
                }
            }
            p = p->rchild;
        }
    }

    //fix root
    if (is_red(root)){
        root->is_red = false;
    }
}

//dispose a subtree
void RBTree::dispose(Node * p)
{
    if(p){
        dispose(p->lchild);
        dispose(p->rchild);
        delete p;
    }
}

//copy a subtree
RBTree::Node * RBTree::copy(Node * p)
{
    if(p){
        Node * res = new Node(*p);
        link_as_lchild(res, copy(p->lchild));
        link_as_rchild(res, copy(p->rchild));
        return res;
    }else{
        return NULL;
    }
}

int main()
{
    RBTree rbt;
    int n,m;
    //input
    cin >> n >> m;
    int target;
    for (int i = 1; i <= n; ++i){
        int t;
        cin >> t;
        rbt.insert(t);
        if (i == m){
            target = t;
        }
    }

    rbt.erase(target);

    //output
    bool is_first = true;
    for(RBTree::iterator iter = rbt.begin(); iter != rbt.end(); ++iter){
        if (is_first){
            cout << *iter;
            is_first = false;
        }else{
            cout << " " << *iter;
        }
    }
    cout <<endl;

    return 0;
}




