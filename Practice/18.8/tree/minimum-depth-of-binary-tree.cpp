//Given a binary tree, find its minimum depth.
//The minimum depth is the number of nodes along 
//the shortest path from the root node down to the nearest leaf node.
//
#include <iostream>

using namespace std;

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x):val(x),left(NULL),right(NULL){}
};

class Solution {
public:
    int run(TreeNode *root) {
        if(root == NULL)
            return 0;
        if(root->left == NULL){
            return run(root->right)+1;
        }
        if(root->right == NULL){
            return run(root->left)+1;
        }
        int left_height = 0;
        int right_height = 0;
        left_height = run(root->left);
        right_height = run(root->right);
        return (left_height < right_height ? left_height : right_height)+1;
    }
};
