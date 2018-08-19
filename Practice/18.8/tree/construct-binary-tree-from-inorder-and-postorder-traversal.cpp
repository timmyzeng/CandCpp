//Given inorder and postorder traversal of a tree, construct the binary tree.

//Note: 
//You may assume that duplicates do not exist in the tree.


#include <iostream>
#include <vector>

using namespace std;

//Definition for binary tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


//这道题目需要注意边界的控制，
//最重要的是要记住每次的开始在begin而不是0
//还有计算下一个区间的时候，用相对距离来计算
class Solution {
    TreeNode* helper(vector<int>& in, int i_beg, int i_end, vector<int>& post, int p_beg, int p_end){
        if(i_beg > i_end)
            return NULL;
        int index = i_beg;
        int counter = 0;
        while(index <= i_end){
            if(in[index] == post[p_end]){
                break;
            }
            index ++;
            counter ++;
        }
        TreeNode* root = new TreeNode(in[index]);
        root->left = helper(in, i_beg, index-1, post, p_beg, p_beg+counter-1);
        root->right = helper(in, index+1, i_end, post, p_beg+counter, p_end-1);
        return root;
    }
public:
    TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder) {
        if(inorder.size() != postorder.size() || inorder.empty() || postorder.empty())
            return NULL;
        return helper(inorder, 0, inorder.size()-1, postorder, 0, postorder.size()-1);
    }
};
