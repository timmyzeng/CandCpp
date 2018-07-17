/*
题目描述
输入两个单调递增的链表，输出两个链表合成后的链表，当然我们需要合成后的链表满足单调不减规则。
 */
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(nullptr) {
	}
};

//非递归
class Solution {
public:
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
    {
        if(pHead1 == nullptr){
            return pHead2;
        }
        if(pHead2 == nullptr){
            return pHead1;
        }

        ListNode* Head = nullptr;
        ListNode* cur = nullptr;

        while(pHead1 != nullptr && pHead2 != nullptr){
            if(pHead1->val <= pHead2->val){
                if(Head == nullptr){
                    Head = pHead1;
                    cur = Head;
                }
                else{
                    cur->next = pHead1;
                    cur = cur->next;
                }
                pHead1 = pHead1->next;
            }
            else if(pHead1->val > pHead2->val){
                if(Head == nullptr){
                    Head = pHead2;
                    cur = Head;
                }
                else{
                    cur->next = pHead2;
                    cur = cur->next;
                }
                pHead2 = pHead2->next;
            }
        }
        if(pHead1 != nullptr){
            cur->next = pHead1;
        }
        if(pHead2 != nullptr){
            cur->next = pHead2;
        }
        return Head;
    }
};



//递归版本
//class Solution {
//public:
    //ListNode* Merge(ListNode* pHead1, ListNode* pHead2)
    //{
        //if(pHead1 == nullptr)
            //return pHead2;
        //if(pHead2 == nullptr)
            //return pHead1;
        //ListNode* head = nullptr;
        //if(pHead1->val < pHead2->val){
            //head = pHead1;
            //head->next = Merge(pHead1->next, pHead2);
        //}
        //else{
            //head = pHead2;
            //head->next = Merge(pHead1, pHead2->next);
        //}
        //return head;
    //}
//};
