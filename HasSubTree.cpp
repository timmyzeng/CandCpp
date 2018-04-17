/*题目描述
输入两棵二叉树A，B，判断B是不是A的子结构。（ps：我们约定空树不是任意一个树的子结构）
*/
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
        val(x), left(nullptr), right(nullptr) {
	}
};
class Solution {
    bool IsSubTree(TreeNode* pRoot1, TreeNode* pRoot2){
        if(pRoot2 == nullptr)
            return true;
        if(pRoot1 == nullptr)
            return false;
        if(pRoot1->val == pRoot2->val){
            return IsSubTree(pRoot1->left, pRoot2->left) &&
                IsSubTree(pRoot1->right, pRoot2->right);
        }
        else
            return false;
    }

public:
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
    {
        if(pRoot2 == nullptr){
            return false;
        }
        if(pRoot1 == nullptr){
            return false;
        }
        //判断子树的时候，pRoot2还是重头开始，不要向后走。
        return IsSubTree(pRoot1, pRoot2) ||
            HasSubtree(pRoot1->left, pRoot2) ||
            HasSubtree(pRoot1->right, pRoot2);
    }
};
