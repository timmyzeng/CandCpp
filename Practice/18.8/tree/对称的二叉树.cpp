//请实现一个函数，用来判断一颗二叉树是不是对称的。
//注意，如果一个二叉树同此二叉树的镜像是同样的，定义其为对称的。

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
    bool helper(TreeNode* left, TreeNode* right){
        //左为空，判断右是否也为空
        if(left == NULL){
            return right == NULL;
        }
        //走到这里，表示left肯定不为空
        if(right == NULL){
            return false;
        }
        //如果用相同来判断的话，剩下的子节点没有办法判断了
        if(left->val != right->val){
            return false;
        }
        //走left的左和right的右，left的右和right的左
        return helper(left->left, right->right) && helper(left->right, right->left);
    }
    bool isSymmetrical(TreeNode* pRoot)
    {
        if(pRoot == NULL)
            return true;
        return helper(pRoot->left, pRoot->right);
    }

};
