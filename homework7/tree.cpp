// headers
#include <iostream>
#include <vector>
using namespace std;

struct Node {
    int val;
    Node *left, *right, *next;
    Node(int x) : val(x), left(NULL), right(NULL), next(NULL) {}
};

// help functions, do not change them!
Node* readTree(istream& is);
void drawTree(ostream& os, Node* node, int depth=0, string prefix="");
void printResult(ostream& os, Node* root);


class Solution {
public:
    //solve the problem
    void connect(Node* root){
        //all extra space
        Node * next = NULL;  //begin of next level
        Node * cur = root;   //current node
        root->next = NULL;
        Node * last = NULL;  //last node in the next level
        while(true){
            //inital for next level
            next = NULL;
            last = NULL;
            //traversal of the current level
            while(cur){
                //test left
                if(cur->left){
                    if(next){
                        //linking nodes
                        last->next = cur->left;
                    }else{
                        //set next
                        next = cur->left;
                    }
                    //updating last
                    last = cur->left;
                }
                //test right
                if(cur->right){
                    if(next){
                        last->next = cur->right;
                    }else{
                        next = cur->right;
                    }
                    last = cur->right;
                }
                cur = cur->next;
            }
            if(next){
                //working on the last node
                last->next = NULL;
                //moving to next level
                cur = next;
            }else{
                //done!
                break;
            }
        }
    }
};

int main(int argc, char* argv[]){

    Solution sol;

    Node* tree = readTree(cin);

    // uncomment it to draw the tree 
    //drawTree(cout, tree);

    sol.connect(tree);

    printResult(cout, tree);
}

Node* readTree(istream& is){
    Node* node;
    int val = 0;

    if( ! (is >> val) ){
        return NULL;
    }
    if(val==0){
        return NULL;
    }
    else{
        node = new Node(val);
        node->left = readTree(is);
        node->right= readTree(is);
    }
    return node;
}

void drawTree(ostream& os, Node* node, int depth, string prefix){
   
    static vector<bool> indents;

    if(!node) return;

    if(depth == 0) indents.clear();

    for(int i=0; i<indents.size(); i++){
        if( i == indents.size()-1){
            os<<prefix;
            break;
        }
        if(indents[i])  os<<"| ";
        else            os<<"  ";
    }

    os<<node->val<<endl;

    indents.push_back(true);

    if( node->right )   prefix = "|-";
    else                prefix = "`-";

    drawTree(os, node->left, depth+1, prefix);

    if( depth < indents.size())
        indents[depth] = false;

    drawTree(os, node->right, depth+1, "`-");

    indents.pop_back();
}

void printResult(ostream& os, Node* root){

    char del = ';';
    Node* first = root;
    for(int depth=1; first!=NULL; depth++){
        Node* node = first;
        first = NULL;

        while(node){
            os<<' '<<node->val;

            if(!first) first = node->left;
            if(!first) first = node->right;

            node = node->next;
        }
        os<<del;
    }
    os<<endl;
}
