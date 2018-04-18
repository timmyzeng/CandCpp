/*
题目描述
输入一个链表，输出该链表中倒数第k个结点。
 */

struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(nullptr) {
	}
};
class Solution {
public:
    ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) {
        if(pListHead == nullptr)
            return nullptr;
        ListNode* fast = pListHead;
        ListNode* slow = pListHead;
        while(k){
            if(fast != nullptr){
                fast = fast->next;
            }
            else{
                break;
            }
            //K的递减只能放在最后，用来判断当k的值超过了节点个数
            -- k;
        }
        if(k > 0){
            return nullptr;
        }
        while(fast != nullptr){
            fast = fast->next;
            slow = slow->next;
        }
        return slow;
    }
};
