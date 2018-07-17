#include <cstdio>
#include <cstdlib>
#include <assert.h>
#include <iostream>
#include <stack>

using namespace std;

struct ListNode{
    ListNode* _next;
    int _val;

    ListNode(int x)
        :_next(NULL)
         ,_val(x)
    {}
};

//1.打印链表
void PrintList(ListNode* cur){
    while(cur!=NULL){
        cout << cur->_val << "->";
        cur = cur->_next;
    }
    cout << "NULL" << endl;
}

//2.从尾到头打印单链表 
void PrintReverse(ListNode* cur){
    //R
    //if(cur->_next){
        //PrintReverse(cur->_next);
    //}
    //cout << cur->_val << " ";
    //
    //NotR
    stack<int> s;
    while(cur!=NULL){
        s.push(cur->_val);
        cur = cur->_next;
    }
    while(!s.empty()){
        int tmp = s.top();
        cout << tmp << " ";
        s.pop();
    }
}

//3.删除一个无头单链表的非尾节点 
void DeleteNode(ListNode* cur){
    ListNode* tmp = cur->_next;
    cur->_val = tmp->_val;
    cur->_next = tmp->_next;
    delete tmp;
}

//4.在无头单链表的一个节点前插入一个节点 
void InsertNode(ListNode* cur, int key){
    ListNode* node = new ListNode(key);
    ListNode* tmp = cur->_next;
    cur->_next = node;
    node->_next = tmp;
    swap(cur->_val, node->_val);
}

//5.单链表实现约瑟夫环 
int JosephRing(ListNode* cur, int k){
    ListNode* prev = NULL;
    while(cur->_next != cur){
        int tmp = k;
        while(--tmp){
            prev = cur;
            cur = cur->_next;
        }
        prev->_next = cur->_next;
        delete cur;
        cur = prev->_next;
    }
    return cur->_val;
}

//6.逆置/反转单链表 
void Reverse(ListNode*& head){
    assert(head);
    ListNode* cur = head;
    ListNode* prev = NULL;
    ListNode* next = cur->_next;
    while(cur != NULL){
        cur->_next = prev;
        prev = cur;
        cur = next;
        if(next!=NULL){
            next = next->_next;
        }
    }
    head = prev;
}
//7.单链表排序（冒泡排序&快速排序） 
//升序
/*    //冒泡*/
void ListSortBubble(ListNode* head){
    if(head == NULL || head->_next == NULL){
        return;
    }
    ListNode* cur = head;
    ListNode* next = cur->_next;
    ListNode* tail = NULL;
    while(tail != head){
        cur = head;
        next = cur->_next;
        int flag = 0;
        while(next != tail){
            if(cur->_val > next->_val){
                flag = 1;
                swap(next->_val, cur->_val);
            }
            cur = next; 
            next = next->_next;
        }
        if(flag == 0){
            break;
        }
        tail = cur;
    }
}

/*//快排*/
////只能使用前后指针法
////递归写法
void ListSortQuit(ListNode* head, ListNode* tail){
    if(head == NULL || head->_next == NULL || head == tail)
        return;
    ListNode* prev = head;
    ListNode* cur = head->_next;
    int key = head->_val;
    while(cur != tail){
        if(cur->_val < key){
            prev = prev->_next;
            if(prev != cur){
                swap(cur->_val, prev->_val);
            }
        }
        cur = cur->_next;
    }
    swap(head->_val, prev->_val);
    ListSortQuit(head, prev);
    ListSortQuit(prev->_next, tail);
}
//
//8.合并两个有序链表,合并后依然有序 
ListNode* MegerList(ListNode* fir, ListNode* sec){
    if(fir == NULL){
        return sec;
    }
    if(sec == NULL){
        return fir;
    }
    ListNode* bigger = fir;
    ListNode* smaller = sec;
    ListNode* head = NULL;
    ListNode* tmp = NULL;
    ListNode* cur = NULL;

    if(fir->_val < sec->_val){
        smaller = fir;
        bigger = sec;
    }
    head = cur = smaller;
    smaller = smaller->_next;
    while(smaller && bigger){
        if(smaller->_val <= bigger->_val){
            cur->_next = smaller;
            if(smaller){
                cur = smaller;
            }
            smaller = smaller->_next;
        }
        else{
            cur->_next = bigger;
            if(bigger){
                cur = bigger;
            }
            bigger = bigger->_next;
        }
    }
    if(smaller){
        cur->_next = smaller;
    }
    if(bigger){
        cur->_next = bigger;
    }
    return head;
}
//9.查找单链表的中间节点，要求只能遍历一次链表 
ListNode* FindMiddle(ListNode* head){
    if(head == NULL)
        return NULL;
    ListNode* fast = head;
    ListNode* slow = head;
    while(fast && fast->_next && fast->_next->_next){
        slow = slow->_next;
        fast = fast->_next->_next;
    }
    return slow;
}

//10.查找单链表的倒数第k个节点，要求只能遍历一次链表
ListNode* FindLastKNode(ListNode* head, int k){
    assert(k > 0);
    if(head == NULL){
        return head;
    }
    ListNode* slow = head;
    ListNode* fast = head;
    while(k){
        if(fast == NULL){
            break;
        }
        fast = fast->_next;
        k--;
    }
    if(k){
        return NULL;
    }
    while(fast!=NULL){
        slow = slow->_next;
        fast = fast->_next;
    }
    head = slow;
    return head;
}

//11.查找函数
ListNode* Find(ListNode* head, int key){
    while(head!=NULL){
        if(head->_val == key){
            return head;
        }
        head = head->_next;
    }
    return NULL;
}
//12. 创建链表
ListNode* InitList(int arr[], int size){
    ListNode* cur = NULL;
    ListNode* head = NULL;
    for(int i=0; i<size; ++i){
        ListNode* tmp = new ListNode(arr[i]);
        if(cur == NULL){
            cur = tmp;
            head = cur;
        }
        cur->_next = tmp;
        cur = tmp;
    }
    return head;
}

//13.判断单链表是否带环？若带环，求环的长度？求环的入口点？并计算每个算法的时间复杂度&空间复杂度。 
//返回相遇点
//判断带环
ListNode* IsRing(ListNode* head){
    if(head == NULL || head->_next == NULL){
        return NULL;
    }
    ListNode* fast = head;
    ListNode* slow = head;
    do{
        fast = fast->_next->_next;
        slow = slow->_next;
    }while(fast && fast->_next && fast != slow);
    if(fast && fast->_next){
        return fast;
    }
    return NULL;
}
//
//环的长度
int RingLength(ListNode* meetnode){
    if(meetnode == NULL){
        return -1;
    }
    ListNode* fast = meetnode;
    ListNode* slow = meetnode;
    int count = 0;
    do{
        fast = fast->_next->_next;
        slow = slow->_next;
        ++ count;
    }while(fast != slow);
    return count;
}
//环的入口
ListNode* RingEntry(ListNode* head, ListNode* meetnode){
    if(head == NULL || meetnode == NULL){
        return NULL;
    }
    while(head != meetnode){
        head = head->_next;
        meetnode = meetnode->_next;
    }
    return head;
}
//14.判断两个链表是否相交，若相交，求交点。（假设链表不带环） 
ListNode* TwoListIsRing(ListNode* fir, ListNode* sec){
    if(fir == NULL || sec == NULL){
        return NULL;
    }
    ListNode* fast = fir;
    ListNode* slow = sec;
    ListNode* tmp = NULL;
    int firnum = 0;
    int srcnum = 0;
    while(fir->_next != NULL){
        ++ firnum;
        fir = fir->_next;
    }
    while(sec->_next != NULL){
        ++ srcnum;
        sec = sec->_next;
    }
    if(sec == fir){
        int run = firnum - srcnum;
        if(run < 0){
            run = -run;
            tmp = fast;
            fast = slow;
            slow = tmp;
        }
        while(run--){
            fast = fast->_next;
        }
        do{
            fast = fast->_next;
            slow = slow->_next;
        }while(fast != slow);
        return fast;
    }
    return NULL;
}

//15.判断两个链表是否相交，若相交，求交点。（假设链表可能带环）【升级版】 
//
//
//
//16.复杂链表的复制。一个链表的每个节点，有一个指向next指针指向下一个节点，
//还有一个random指针指向这个链表中的一个随机节点或者NULL，
//现在要求实现复制这个链表，返回复制后的新链表。 
//ps: 复杂链表的结构 
struct ComplexNode { 
    int _data ; // 数据 
    struct ComplexNode * _next; // 指向下一个节点的指针 
    struct ComplexNode * _random; // 指向随机节点（可以是链表中的任意节点 or 空） 

    ComplexNode(int x)
        :_data(x)
         ,_next(NULL)
         ,_random(NULL)
    {}
};
ComplexNode* ComplexListCopy(ComplexNode* head){
    if(head == NULL){
        return NULL;
    }
    ComplexNode* cur = head;
    ComplexNode* next = head->_next;
    ComplexNode* tmp = NULL;
    ComplexNode* result = NULL;
    //copy
    while(cur){
        tmp = new ComplexNode(cur->_data);
        cur->_next = tmp;
        tmp->_next = next;
        cur = next;
        if(next){
            next = next->_next;
        }
    }
    //set random 
    cur = head;
    next = cur->_next;
    while(cur){
        if(cur->_random){
            next->_random = cur->_random->_next;
        }
        cur = next->_next;
        if(cur){
            next = cur->_next;
        }
    }
    //detach
    cur = head;
    next = cur->_next;
    result = cur->_next;
    while(cur){
        cur->_next = next->_next;
        cur = next->_next;
        if(cur){
            next->_next = cur->_next;
            next = cur->_next;
        }
        else{
            next->_next = cur;
        }
    }
    return result;
}

void Test(){
    //int arr[] = {1,2,3,4,5};
    //ListNode* head = InitList(arr, sizeof(arr)/sizeof(arr[0]));
    //PrintList(head);
    //PrintReverse(head);
    //
    //DeleteNode(Find(head, 4));
    //DeleteNode(Find(head, 0));
    //PrintList(head);
    //
    //InsertNode(Find(head, 4), 10);
    //InsertNode(Find(head, 0), 12);
    //PrintList(head);
    //
    //ring
    //Find(head, 7)->_next = head;
    //cout << JosephRing(head, 3) << endl;
    //
    //Reverse(head);
    //PrintList(head);
    //
    //int arr1[] = {7,6,3,4,2,5,1};
    //ListNode* head1 = InitList(arr1, sizeof(arr1)/sizeof(arr1[0]));
    //PrintList(head1);
    //ListSortBubble(head1);
    //ListSortQuit(head1, NULL);
    //PrintList(head1);
    //
    //PrintList(head);
    //int arr2[] = {2,3,5,7,9,10,11};
    //ListNode* head2 = InitList(arr2, sizeof(arr2)/sizeof(arr2[0]));
    //PrintList(head2);
    //PrintList(MegerList(head, head2));
    //
    //cout << FindMiddle(head)->_val << endl;
    //cout << FindLastKNode(head, 7)->_val << endl;
    //
    //
    //ring
    //
    //Find(head, 5)->_next = Find(head, 3);
    //cout << IsRing(head)->_val << endl;
    //cout << RingLength(IsRing(head)) << endl;
    //cout << RingEntry(head, IsRing(head))->_val << endl;
    //
    //
    //int arr[] = {1,2,3,4};
    //ListNode* head = InitList(arr, sizeof(arr)/sizeof(arr[0]));
    //int arr1[] = {1,5,6,7,8};
    //ListNode* head1 = InitList(arr1, sizeof(arr1)/sizeof(arr1[0]));
    //Find(head1,8)->_next = Find(head, 2);
    //PrintList(head);
    //PrintList(head1);
    //cout << TwoListIsRing(head, head1)->_val << endl;
    //
    //
    //ComplexNode* n1 = new ComplexNode(1);
    //ComplexNode* n2 = new ComplexNode(2);
    //ComplexNode* n3 = new ComplexNode(3);
    //ComplexNode* n4 = new ComplexNode(4);
    //ComplexNode* n5 = new ComplexNode(5);
    //ComplexNode* head = n1;

    //n1->_next = n2;
    //n2->_next = n3;
    //n3->_next = n4;
    //n4->_next = n5;
    //n5->_next = NULL;

    //n1->_random = n5;
    //n2->_random = n4;
    //n3->_random = n3;
    //n4->_random = n2;
    //n5->_random = n1;

    //ComplexNode*cur = head;
    //while(cur != NULL){
        //cout << cur->_data << "->";
        //cur = cur->_next;
    //}
    //cout << "NULL" << endl;
    //cur = head;
    //while(cur != NULL){
        //if(cur->_random){
            //cout << cur->_random->_data << "->";
        //}
        //cur = cur->_next;
    //}
    //cout << "NULL" << endl;

    //ComplexNode* t = ComplexListCopy(head);
    //cur = t;

    //while(cur != NULL){
        //cout << cur->_data << "->";
        //cur = cur->_next;
    //}
    //cout << "NULL" << endl;
    
    //cur = t;
    //while(cur != NULL){
        //if(cur->_random){
            //cout << cur->_random->_data << "->";
        //}
        //cur = cur->_next;
    //}
    //cout << "NULL" << endl;
}

int main(){
    Test();
    return 0;
}
