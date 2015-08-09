 /*
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
#include <algorithm>   //required by the solution
#include <utility>     //required by the solution
#include <iostream>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

const int INF = 0xFFFFFFF; //represent infinite

void print_tree(ostream & os, TreeNode * root)
{
    if (root ==  NULL){
        os << -INF << endl;
    }else{
        os << root->val <<endl;
        print_tree(os, root->left);
        print_tree(os, root->right);
    }
}

TreeNode * build_tree(int size, int l, int h)
{
    if (size == 0){
        return NULL;
    }
    if (size == 1){
        TreeNode * res = new TreeNode(l + rand() % (h - l + 1));
        return res;
    }
    int lsize = 0;
    TreeNode * res = new TreeNode(l + rand() % (h - l + 1));
    res->left = build_tree(lsize, l, h);
    res->right = build_tree(size - lsize - 1, l, h);
    return res;
}



int main()
{
    srand(time(0));
    int n;
    cin >> n;
    TreeNode * root = build_tree(n, -100, 100);
    print_tree(cout, root);
    return 0;
}
