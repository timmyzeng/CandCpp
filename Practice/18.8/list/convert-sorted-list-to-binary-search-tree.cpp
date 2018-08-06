/*

Given a singly linked list where elements are sorted 
in ascending order, convert it to a height balanced BST.
*/

/*
 * time out
        if(head == NULL)
            return NULL;
        ListNode* slow = head, *fast = head, *prev = NULL,*next = NULL;
        while(fast != NULL && fast->next != NULL){
            if(prev == NULL){
                prev = slow;
            }
            else{
                prev = slow;
            }
            slow = slow->next;
            fast = fast->next->next;
        }
        if(prev){
            prev->next = NULL;
        }
        next = slow->next;
        
        TreeNode* cur = new TreeNode(slow->val);
        cur->left = sortedListToBST(head);
        cur->right = sortedListToBST(next);
        
        return cur;
*/

#include <iostream>

using namespace std;


//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


//Definition for binary tree
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};


class Solution {
public:
    TreeNode* sort(ListNode* head, ListNode* tail){
        if(head == tail){
            return NULL;
        }
        ListNode* slow = head, *fast = head;
        while(fast!=tail && fast->next!=tail){
            fast = fast->next->next;
            slow = slow->next;
        }
        TreeNode* root = new TreeNode(slow->val);
        root->left = sort(head, slow);
        root->right = sort(slow->next, tail);
        return root;
    }
    
    TreeNode *sortedListToBST(ListNode *head) {
        return sort(head, NULL);
    }
};
