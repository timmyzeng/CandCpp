/*
 *题目描述
输入一个复杂链表（每个节点中有节点值，以及两个指针，一个指向下一个节点，另一个特殊指针指向任意一个节点），
返回结果为复制后复杂链表的head。（注意，输出结果中请不要返回参数中的节点引用，否则判题程序会直接返回空）
 */

#include <iostream>

using namespace std;

struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(nullptr), random(nullptr) {
    }
};

class Solution {
public:
    RandomListNode* Clone(RandomListNode* pHead){
        if(pHead == nullptr)
            return nullptr;
        RandomListNode* cur = pHead;
        RandomListNode* next = cur->next;
        RandomListNode* tmp = nullptr;
        while(cur != nullptr){
            tmp = new RandomListNode(cur->label);
            cur->next = tmp;
            tmp->next = next;
            cur = next;
            if(cur)
                next = cur->next;
        }

        cur = pHead;
        RandomListNode* cop = cur->next; 
        while(cur != nullptr){
            if(cur->random)
                cop->random = cur->random->next;
            cur = cop->next;
            if(cur)
                cop = cur->next;
        }

        cur = pHead;
        cop = cur->next;
        pHead = cop;
        while(cur){
            cur->next = cop->next;
            cur = cop->next;
            if(cur){
                cop->next = cur->next;
                cop = cur->next;
            }
        }
        cop->next = nullptr;

        return pHead;
    }
};
