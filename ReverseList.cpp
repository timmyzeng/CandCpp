/*
 *题目描述
输入一个链表，反转链表后，输出链表的所有元素。
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
    ListNode* ReverseList(ListNode* pHead) {
        if(pHead == nullptr || pHead->next == nullptr)
            return pHead;
        ListNode* Node = ReverseList(pHead->next);
        pHead->next->next = pHead;
        pHead->next = nullptr;
        return Node;
    }
};
