/*
 *给定一个二叉树和其中的一个结点，请找出中序遍历顺序的下一个结点并且返回。
 注意，树中的结点不仅包含左右子结点，同时包含指向父结点的指针。
 */

#include <iostream>

using namespace std;

struct TreeLinkNode {
    int val;
    struct TreeLinkNode *left;
    struct TreeLinkNode *right;
    struct TreeLinkNode *next;
    TreeLinkNode(int x) :val(x), left(nullptr), right(nullptr), next(nullptr) 
    {}
};

class Solution {
public:
    TreeLinkNode* GetNext(TreeLinkNode* pNode){
        if(pNode == nullptr)
            return nullptr;
        if(pNode->right){
            TreeLinkNode* sub = pNode->right;
            while(sub->left){
                sub = sub->left;
            }
            return sub;
        }
        else{
            if(pNode->next && (pNode->next->left == pNode)){
                return pNode->next;
            }
            else if(pNode->next && (pNode->next->right == pNode)){
                TreeLinkNode* parent = pNode->next;
                //parent == root
                //root->next == nullptr
                while(parent && (parent->right == pNode)){
                    pNode = parent;
                    parent = pNode->next;
                }
                return parent; 
            }
            else
                return nullptr;
        }
    }
};
