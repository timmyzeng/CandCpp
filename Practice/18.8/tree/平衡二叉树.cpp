/*
输入一棵二叉树，判断该二叉树是否是平衡二叉树。
 */


#include <iostream>

using namespace std;

struct TreeNode{
    TreeNode* left;
    TreeNode* right;
    int val;

    TreeNode(int x):left(NULL),right(NULL),val(x){}
};

class Solution {
public:
    bool helper(TreeNode* root, int& height){
        if(root == NULL){
            return true;
        }
        int leftheight = 0;
        int rightheight = 0;
        if(helper(root->left, leftheight) && helper(root->right, rightheight)){
            if(abs(leftheight-rightheight) > 1)
                return false;
            height = (leftheight > rightheight ? leftheight : rightheight)+1;
            return true;
        }
        return false;
    }
    bool IsBalanced_Solution(TreeNode* pRoot) {
        int height = 0;
        return helper(pRoot, height);
    }
};
