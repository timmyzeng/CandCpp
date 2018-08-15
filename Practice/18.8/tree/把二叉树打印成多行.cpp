//从上到下按层打印二叉树，同一层结点从左至右输出。每一层输出一行。

#include <iostream>
#include <vector>
#include <queue>

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
        vector<vector<int> > Print(TreeNode* pRoot) {
            if(pRoot == NULL){
                return vector<vector<int> >();
            }
            queue<TreeNode*> q;
            vector<vector<int> > v;
            q.push(pRoot);
            while(!q.empty()){
                vector<int> v1;
                TreeNode* tmp = NULL;
                int num = 0;
                int size = q.size();
                v1.resize(size);
                while(num < size){
                    tmp = q.front();
                    v1[num] = tmp->val;
                    if(tmp->left)
                        q.push(tmp->left);
                    if(tmp->right)
                        q.push(tmp->right);
                    q.pop();
                    num ++;
                }
                v.push_back(v1);
            }
            return v;
        }
};
