/*
 *题目描述
输入一个链表，从尾到头打印链表每个节点的值。
*/
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
          val(x), next(nullptr) {
    }
};

#include<vector>
#include<stack>
using namespace std;

class Solution {
public:
    vector<int> printListFromTailToHead(ListNode* head) {
        vector<int> arr;
        stack<int> s;
        if(head == nullptr)
            return arr;
        ListNode* cur = head;
        while(cur){
            s.push(cur->val);
            cur = cur->next;
        }
        while(!s.empty()){
            int tmp = s.top();
            s.pop();
            arr.push_back(tmp);
        }
        return arr;
    }
};
