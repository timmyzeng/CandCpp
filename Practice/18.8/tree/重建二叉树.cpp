//输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。
//假设输入的前序遍历和中序遍历的结果中都不含重复的数字。
//例如输入前序遍历序列{1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}，
//则重建二叉树并返回。

#include <iostream>
#include <vector>

using namespace std;


// Definition for binary tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

class Solution {
public:
    TreeNode* helper(vector<int>& pre, int pleft, int pright, vector<int>& vin, int vleft, int vright){
        if(pleft > pright)
            return NULL;
        TreeNode* root = new TreeNode(pre[pleft]);
        int count = 0;
        int i = 0;
        for(i = vleft; i <= vright; ++ i){
            if(vin[i] == pre[pleft])
                break;
            count ++;
        }
        root->left = helper(pre, pleft+1, pleft+count, vin, vleft, i-1);
        root->right = helper(pre, pleft+count+1, pright, vin, i+1, vright);
        return root;
    }
    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
        if(pre.empty() || vin.empty() || pre.size() != vin.size()){
            return NULL;
        }
        return helper(pre, 0, pre.size()-1, vin, 0, vin.size()-1);
    }
};
