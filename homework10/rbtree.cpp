#include <iostream>
using namespace std;
class RBTree
{
  public:
    RBTree():root(NULL){}
    ~RBTree() { dispose(root); }
    void insert(int k);
    void erase(int k);
    void output() { display(root); }
  private:
    struct Node
    {
      bool col;//color
      int key;  
      Node * lc;
      Node * rc;
      Node * par;
      //constructors
      Node(int k): key(k), col(true), lc(0), rc(0), par(0) {}
      Node(const Node & other): key(other.key), col(other.col), lc(0), rc(0), par(0) {}
    };
    Node * root;
    //link two node (the child can be NULL)
    void link_as_lc(Node * p, Node * c)
    {
      p->lc = c;
      if (c)
        c->par = p;
    }
    void link_as_rc(Node * p, Node * c)
    {
      p->rc = c;
      if(c)
        c->par = p;
    }
    //rotation
    void rotL(Node * x);
    void rotR(Node * x);
    bool is_red(Node * p) const { return (p && p->col); }
    bool is2node(Node * p) const;
    void rebuild(Node * p);
    Node * min(Node * x) const
    {
      if(x)
        while(x->lc) //keep go left
          x = x->lc;
      return x;
    }
    Node * max(Node * x) const
    {
      if(x)
        while(x->rc)  //keep go right
          x = x->rc;
      return x;
    }
    void recolor(Node * x)
    {
      x->col = false;
      x->lc->col = true;
      x->rc->col = true;
    }
    Node * succ(Node * x) const; //find successor
    void dispose(Node * x);
    void display(Node * x);
};
void RBTree::insert(int k)
{
  Node * p = NULL;
  Node * x = root;
  //adjusting while searching
  while(x){
    if (is_red(x->lc) && is_red(x->rc)){
      x->lc->col = false;
      x->rc->col = false;
      if (x != root){
        x->col = true;
        if (is_red(x->par)){
          rebuild(x);
        }
      }
    }
    if (k < x->key){
      p = x;
      x = x->lc;
    }else{
      p = x;
      x = x->rc;
    }
  }
  //insert
  if (p == NULL){
    root = new Node(k);
    root->col = false;
  }else{
    Node * t = new Node(k);
    if (k < p->key){
      link_as_lc(p, t);
    }else{
      link_as_rc(p, t);
    }
    if (is_red(p)){
      rebuild(t);
    }
  }
}
void RBTree::rebuild(Node * x)
{
  //Note fix the case the p, x are red
  Node * p = x->par;
  Node * g = p->par;
  if (p == g->lc){
    if (x == p->rc){  //let p, x at the same side
      rotL(p);
      p = g->lc;
    }
    rotR(g);
  }else{
    if (x == p->lc){  //let p, x at the same side
      rotR(p);
      p = g->rc;
    }
    rotL(g);
  }
  recolor(p);
}
void RBTree::rotL(Node * x)
{
  Node * p = x->par;
  Node * y = x->rc;
  link_as_rc(x, y->lc);
  link_as_lc(y, x);
  //fix the link to par
  if (p){
    if (x == p->lc){
      link_as_lc(p, y);
    }else{
      link_as_rc(p, y);
    }
  }else{
    root = y;
    y->par = NULL;
  }
}
void RBTree::rotR(Node * x)
{
  Node * p = x->par;
  Node * y = x->lc;
  link_as_lc(x, y->rc);
  link_as_rc(y, x);
  //fix the link to par
  if (p){
    if (x == p->lc){
      link_as_lc(p, y);
    }else{
      link_as_rc(p, y);
    }
  }else{
    root = y;
    y->par = NULL;
  }
}
//find successor
RBTree::Node * RBTree::succ(RBTree::Node * x) const
{
  if (x->rc){ //has right subtree?
    return min(x->rc);
  }else{  //go upward
    Node * p = x->par;
    while(p && p->rc == x){
      x = p;
      p = p->par;
    }
    return p;
  }
}
//Note: to judge if a node is black and all its children are black
bool RBTree::is2node(Node * x) const
{
  if (is_red(x)) return false;
  if (x)
    if (is_red(x->rc) || is_red(x->lc)) return false;
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
    p->col = true;
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
        if (p->lc && p->rc){
          Node * t = min(p->rc);
          p->key = t->key;
          k = t->key;
          go_left = false;
        }else{
          //can delete
          Node * t = (p->lc)?(p->lc):(p->rc);
          if (is_red(t)) t->col = false; //recolor
          if (p->par){
            if (p->par->lc == p){
              link_as_lc(p->par, t);
            }else{
              link_as_rc(p->par, t);
            }
          }else{
            root = t;
            if (t){
              t->par = NULL;
            }
          }
          delete p;
          break;
        }
      }
    }
    //move down
    if(go_left){
      if (p->lc == NULL) break;//Not found
      if (is2node(p->lc)){  //adjust needed
        //reduce to the case when p is red
        if (!is_red(p)) rotL(p);
        if(is2node(p->rc)){ //case 2a1
          recolor(p);
        }else{
          if(is_red(p->rc->lc)){ //case 2a2
            rotR(p->rc);
            rotL(p);
          }else{  //case 2a3
            p->rc->rc->col = false;
            p->rc->col = true;
            rotL(p);
          }
          p->col = false;
          p->lc->col = true;
        }
      }
      p = p->lc;
    }else{
      if (p->rc == NULL) break;//Not found
      if (is2node(p->rc)){ //adjust needed
        //reduce to the case that p is red
        if (!is_red(p)) rotR(p);
        if(is2node(p->lc)){  //case 2a1
          recolor(p);
        }else{
          if(is_red(p->lc->rc)){ //case 2a2
            rotL(p->lc);
            rotR(p);
          }else{ //case 2a3
            p->lc->lc->col = false;
            p->lc->col = true;
            rotR(p);
          }
          p->col = false;
          p->rc->col = true;
        }
      }
      p = p->rc;
    }
  }
  if (is_red(root)) root->col = false; //fix root
}
//dispose a subtree
void RBTree::dispose(Node * p)
{
  if(p){
    dispose(p->lc);
    dispose(p->rc);
    delete p;
  }
}
void RBTree::display(Node * p)
{
  if(p){
    display(p->lc);
    cout << p->key << " ";
    display(p->rc);
  }
}
int main()
{
  RBTree rbt;
  int n,m,target,t;
  cin >> n >> m;
  for (int i = 1; i <= n; ++i){
    cin >> t;
    rbt.insert(t);
    if (i == m) target = t;
  }
  rbt.erase(target);
  rbt.output();
  cout <<endl;
  return 0;
}

