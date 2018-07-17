/*
 *请实现一个函数，用来判断一颗二叉树是不是对称的。注意，如果一个二叉树同此二叉树的镜像是同样的，定义其为对称的。
 */

#include <iostream>

using namespace std;
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};

class Solution {
public:
    bool isSymmetrical(TreeNode* pRoot){
        if(pRoot == NULL)
            return true;
        TreeNode* left = pRoot->left;
        TreeNode* right = pRoot->right;

        return IsSymmetricalCore(left, right);
    }

    bool IsSymmetricalCore(TreeNode* &leftnode, TreeNode*& rightnode){
        if(leftnode == NULL && rightnode == NULL)
            return true;
        else if(leftnode && rightnode && leftnode->val == rightnode->val){
            return IsSymmetricalCore(leftnode->left, rightnode->right)
                && IsSymmetricalCore(leftnode->right, rightnode->left);
        }
        return false;
    }

};
