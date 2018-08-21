//Given n, generate all structurally unique BST's (binary search trees) that store values 1...n.

//For example,
//Given n = 3, your program should return all 5 unique BST's shown below.

   //1         3     3      2      1
    //\       /     /      / \      \
     //3     2     1      1   3      2
    ///     /       \                 \
   //2     1         2                 3


//Definition for binary tree
//
//

#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
    vector<TreeNode*> helper(int left, int right){
        vector<TreeNode*> v;
        // 如果left > right 表示结束，没有节点，所以插入NULL
        if(left > right){
            v.push_back(NULL);
        }
        // 1、一个for循环遍历n个元素
        // 2、每一个元素对应的左右子树，递归创建
        // 3、每一个元素的子树个数等于左子树的个数乘以右子树的个数
        for(int i = left; i <= right; ++ i){
            vector<TreeNode*> l_root = helper(left, i-1);
            vector<TreeNode*> r_root = helper(i+1, right);
            for(int j = 0; j < l_root.size(); ++ j){
                for(int z = 0; z < r_root.size(); ++ z){
                    TreeNode* root = new TreeNode(i);
                    root->left = l_root[j];
                    root->right = r_root[z];
                    v.push_back(root);
                }
            }
        }
        return v;
    }
public:
    vector<TreeNode *> generateTrees(int n) {
        return helper(1, n);
    }
};
