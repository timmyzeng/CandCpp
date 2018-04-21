/*
 *题目描述
输入某二叉树的前序遍历和中序遍历的结果，请重建出该二叉树。
假设输入的前序遍历和中序遍历的结果中都不含重复的数字。
例如输入前序遍历序列{1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}，则重建二叉树并返回
*/

#include <vector>
using namespace std;
struct TreeNode {
 int val;
 TreeNode *left;
 TreeNode *right;
 TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
class Solution {
public:
    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
        int pre_size = pre.size();
        int vin_size = vin.size();
        if(pre_size == 0 || pre_size != vin_size)
            return nullptr;

        vector<int> left_pre, left_vin, right_pre, right_vin;
        TreeNode* root = new TreeNode(pre[0]);
        int root_index = 0;

        for(int i = 0; i < vin_size; ++i){
            if(pre[0] == vin[i]){
                root_index = i;
                break;
            }
        }

        for(int i = 0; i < root_index; ++i){
            left_pre.push_back(pre[i+1]);
            left_vin.push_back(vin[i]);
        }
        for(int i = root_index+1; i < vin_size; ++i){
            right_pre.push_back(pre[i]);
            right_vin.push_back(vin[i]);
        }

        root->left = reConstructBinaryTree(left_pre, left_vin);
        root->right = reConstructBinaryTree(right_pre, right_vin);

        return root;
    }
};
