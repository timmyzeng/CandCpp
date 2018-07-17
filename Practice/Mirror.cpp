/*题目描述
操作给定的二叉树，将其变换为源二叉树的镜像。
输入描述:
二叉树的镜像定义：源二叉树 
    	    8
    	   /  \
    	  6   10
    	 / \  / \
    	5  7 9 11
    	镜像二叉树
    	    8
    	   /  \
    	  10   6
    	 / \  / \
    	11 9 7  5  
*/

struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(nullptr), right(nullptr) {
	}
};
////递归
//class Solution {
//public:
    //void Mirror(TreeNode *pRoot) {
        //if(pRoot == nullptr)
            //return;
        //if(pRoot->left == nullptr && pRoot->right == nullptr)
            //return;
        //TreeNode* tmp = pRoot->left;
        //pRoot->left = pRoot->right;
        //pRoot->right = tmp;
        //Mirror(pRoot->left);
        //Mirror(pRoot->right);
    //}
//};

//非递归
#include <stack>
using namespace std;
class Solution {
public:
    void Mirror(TreeNode *pRoot) {
        if(pRoot == nullptr)
            return;
        stack<TreeNode*> s;
        s.push(pRoot);
        while(!s.empty()){
            if(pRoot->left != nullptr || pRoot->right != nullptr){
                TreeNode* tmp = pRoot->left;
                pRoot->left = pRoot->right;
                pRoot->right = tmp; 
            }
            s.pop();
            if(pRoot->left)
                s.push(pRoot->left);
            if(pRoot->right)
                s.push(pRoot->right);
        }
    }
};
