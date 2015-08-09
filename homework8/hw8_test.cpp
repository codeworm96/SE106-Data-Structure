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
class Solution {
public:
    //the solution to the problem
    //parameter: the pointer of the root node
    //returns the answer
    int maxPathSum(TreeNode* root) {
        //special case: the empty tree
        //the answer is not well defined, the TA says not to consider it.
        if(root == NULL){
            return 0;
        }
        pair<int, int> res = dp(root);
        //Note: without the restriction the answer is bigger
        return res.second;
    }
private:
//Note for the pair<int, int> return value of dp
//first: the answer when the node root is at one end of the path
//second: the answer without the restriction above
    pair<int, int> dp(TreeNode* root){
        //the empty tree has no valid answer
        //return (-INF, -INF) to represent no answer
        if (root == NULL){
            return make_pair(-INF,-INF);
        }else{
            //solve to subproblem
            pair<int, int> l = dp(root->left);
            pair<int, int> r = dp(root->right);
            //combine the answer
            //Part One: Node root is at one end of the path
            //Case1 : The Node root alone
            //Case2 : The Node root + the path that the root->left is at one end
            //Case3 : The Node root + the path that the root->right is at one end
            //Part Two: without restriction
            //Case1 : The Node root + the path that the root->left is at one end (if it is > 0)
            //                      + the path that the root->right is at one end (if it is > 0)
            //Case2 : The answer of root->left
            //Case3 : The answer of root->right
            return make_pair(max(max(l.first, r.first), 0) + root->val,
                             max(max(l.first, 0) + root->val + max(r.first, 0), max(l.second, r.second)));
        }
    }
};

TreeNode * read_tree(istream & is)
{
    int val;
    is >> val;
    if (val == -INF){
        return NULL;
    }else{
        TreeNode * res = new TreeNode(val);
        res->left = read_tree(is);
        res->right = read_tree(is);
        return res;
    }
}

int main()
{
    TreeNode * root = read_tree(cin);
    Solution ans;
    cout << ans.maxPathSum(root) << endl;
    return 0;
}
