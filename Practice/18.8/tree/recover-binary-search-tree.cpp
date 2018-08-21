//Two elements of a binary search tree (BST) are swapped by mistake.
//Recover the tree without changing its structure.
//Note: 
//A solution using O(n ) space is pretty straight forward. 
//Could you devise a constant space solution?


#include <iostream>

using namespace std;

//Definition for binary tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


//重点在于使用指针进行记录两个值，题目说了有两个错误的值。
//必须使用引用，为什么呢？引用和指针的区别是啥呢
class Solution {
    void helper(TreeNode* root, TreeNode*& prev, TreeNode*& w1, TreeNode*& w2){
        if(root == NULL)
            return;
        helper(root->left, prev, w1, w2);
        if(prev && prev->val >= root->val){
            w1 = root;
            if(w2 == NULL)
                w2 = prev;
        }
        prev = root;
        helper(root->right, prev, w1, w2);
    }
public:
    void recoverTree(TreeNode *root) {
        if(root == NULL)
            return;
        TreeNode* w1 = NULL, *w2 = NULL, *prev = NULL;
        helper(root, prev, w1, w2);
        if(w1 && w2)
            swap(w1->val, w2->val);
    }
};
