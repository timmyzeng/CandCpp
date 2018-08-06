
//Given a linked list and a value x, partition it such that all nodes 
//less than x come before nodes greater than or equal to x.

//You should preserve the original relative order of 
//the nodes in each of the two partitions.

//For example,
//Given1->4->3->2->5->2and x = 3,
//return1->2->2->4->3->5.

/*
1、创建两个链表，小的和大的分开，然后连起来。
2、情况：
    头结点的值就比x大，要头插；
    连续的值都是小于x的，不需要交换；
    如果prev小于x，尾部指针需要跟着走，不然会出现交换小元素的位置。
*/

#include <iostream>

using namespace std;

//Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


class Solution {
public:
    ListNode *partition(ListNode *head, int x) {
        if(head == NULL || head->next == NULL){
            return head;
        }
        ListNode* Head = head;
        ListNode* cur = head->next;
        ListNode* prev = head;
        ListNode* tail = head;
        bool greater = true;
        
        if(head->val < x){
            greater = false;
        }
        
        while(cur){
            if(cur->val < x && prev->val >= x){
                prev->next = cur->next;
                if(greater){
                    greater = false;
                    cur->next = tail;
                    Head = tail = cur;
                }
                else{
                    cur->next = tail->next;
                    tail->next = cur;
                    tail = cur;
                }
                cur = prev->next;
            }
            else{
                if(prev->val < x)
                    tail = prev;
                prev = cur;
                cur = cur->next;
            }
        }
        return Head;
    }
};
