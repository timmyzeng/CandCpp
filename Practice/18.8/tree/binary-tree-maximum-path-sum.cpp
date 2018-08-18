/*
Given a binary tree, find the maximum path sum.

The path may start and end at any node in the tree.

For example:
Given the below binary tree,

       1
      / \
     2   3

Return 6.
*/

#include <iostream>
#include <limits.h>

using namespace std;

//Definition for binary tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

//1、考虑节点小于0的情况
//2、Max指的是总的最大路径值
//3、cur_max指的是当前节点的最大路径值
//4、如果节点小于0的话，返回0，因为cur->val小于0，相加反而变小
class Solution {
    int helper(TreeNode* root, int& Max, int cur_max){
        if(root == NULL){
            return 0;
        }
        int l_max = 0;
        int r_max  = 0;
        l_max = helper(root->left, Max, l_max);
        r_max = helper(root->right, Max, r_max);
        Max = max(Max, l_max+r_max+root->val);
        return max(max(l_max, r_max)+root->val, 0);
    }
public:
    int maxPathSum(TreeNode *root) {
        int Max = INT_MIN;
        int cur_max = INT_MIN;
        helper(root, Max, cur_max);
        return Max;
    }
};
