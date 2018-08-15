//给定一个二叉树和其中的一个结点，
//请找出中序遍历顺序的下一个结点并且返回。
//注意，树中的结点不仅包含左右子结点，同时包含指向父结点的指针。
//
//

#include <iostream>

using namespace std;

struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
    TreeLinkNode(int x) :val(x), left(NULL), right(NULL), next(NULL) {
        
    }
};

class Solution {
public:
    TreeLinkNode* GetNext(TreeLinkNode* pNode)
    {
        if(pNode == NULL){
            return NULL;
        }
        TreeLinkNode* cur = pNode->right;
        TreeLinkNode* parent = NULL;
        //右子树存在，返回右子树的最左节点
        if(cur){
            while(cur->left){
                cur = cur->left;
            }
            return cur;
        }
        //右子树不存在
        //当前节点的父节点不存在
        if(pNode->next == NULL){
            return NULL;
        }
        else if(pNode->next->left == pNode){        //当前节点是父节点的左子树
            return pNode->next;
        }
        else{        //当前节点是父节点的右子树
            parent = pNode->next;
            while(parent && parent->right == pNode){
                pNode = parent;
                parent = pNode->next;
            }
            return parent;
        }
    }
};
