//Given a binary tree, determine if it is a valid binary search tree (BST).

//Assume a BST is defined as follows:
//The left subtree of a node contains only nodes with keys less than the node's key.
//The right subtree of a node contains only nodes with keys greater than the node's key.
//Both the left and right subtrees must also be binary search trees.

#include <iostream>

using namespace std;

//Definition for binary tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

//利用上下限制的方法，确定左右子树值的区域。
class Solution {
    bool helper(TreeNode* root, TreeNode* Min, TreeNode* Max){
        if(root == NULL)
            return true;
        if((Min && root->val <= Min->val) || (Max && root->val >= Max->val))
            return false;
        return helper(root->left, Min, root) && helper(root->right, root, Max);
    }
public:
    bool isValidBST(TreeNode *root) {
        return helper(root, NULL, NULL);
    }
};
