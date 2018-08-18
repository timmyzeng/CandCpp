//请实现两个函数，分别用来序列化和反序列化二叉树

#include <iostream>
#include <vector>

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
    //序列化的过程就是变成字符串进行传送，反序列化就是将字符串变成相应的结构。
    //1、字符串是char*类型，但是元素是int类型，所以需要考虑char和int类型的转换
    //2、同时通过递归进行二叉树的先序遍历
    void helper(TreeNode* root, vector<int>& tmp){
        if(root == NULL){
            tmp.push_back(0x0fffffff);
            return;
        }
        tmp.push_back((root->val));
        helper(root->left, tmp);
        helper(root->right, tmp);
    }
    char* Serialize(TreeNode *root) {
        vector<int> tmp;
        helper(root, tmp);
        int* arr = new int[tmp.size()];
        for(int i = 0; i < tmp.size(); ++ i){
            arr[i] = tmp[i];
        }
        return (char *)arr;
    }
    
    TreeNode* helper2(int* str, int invalued, int& index){
        if(str[index] == '\0' || str[index] == invalued){
            return NULL;
        }
        TreeNode* root = new TreeNode(str[index]);
        root->left = helper2(str, invalued, ++index);
        root->right = helper2(str, invalued, ++index);
        return root;
    }
    
    TreeNode* Deserialize(char *str) {
        int tmp = 0;
        int* ptr = (int *)str;
        return helper2(ptr, 0xfffffff, tmp);
    }
};
