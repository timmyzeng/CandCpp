/*************************************************************************
	> File Name: delete_print_list.1.19.cpp
	> Author: Timmy
	> Created Time: Tue 30 Jan 2018 08:00:49 PM CST
 ************************************************************************/

#include <iostream>
#include <assert.h>

using namespace std;

//struct node{
	//node( int n ){
		//val = n;
		//next = NULL;
	//}
	//int val;
	//node* next;
//};

////1.删除一个无头节点单链表的非尾节点。
//void delete_list( node* pos ){
	//assert(pos->next);
	//node* tmp = pos->next;
	//pos->next = pos->next->next;
	//swap(tmp->val, pos->val);
	//delete tmp;
//}

////从尾到头打印单链表。
//void print_reverse( node* head ){
	//if( head == NULL )
		//return;
	//print_reverse( head->next );
	//cout << head->val << " ";
//}

//void print( node* root ){
	//while( root ){
		//cout << root->val << "->";
		//root = root->next;
	//}
	//cout << "NULL" << endl;
//}

//2.复杂单链表的复制，random指向任意一个节点或null，返回复制后的新链表。

#define datatype int 

typedef struct complexnode{
	complexnode(datatype val){
		_data = val;
		_next = NULL;
		_random = NULL;
	}
	datatype _data;
	complexnode* _next;
	complexnode* _random;
}comnode;

comnode* copy_complex_list( comnode* head ){
	comnode* cur = head;
	comnode* next = cur->_next;
	if( cur == NULL )
		return NULL;
	//将每一个节点复制到当前节点的后面，并链入链表
	while( cur ){
		comnode* tmp = new comnode(cur->_data);
		cur->_next = tmp;
		tmp->_next = next;
		cur = next;
		if( cur )
			next = cur->_next;
	}
	cur = head;
	next = cur->_next;
	//给新链入的节点置random
	while( cur ){
		if( cur->_random )
			next->_random = cur->_random->_next;
		else
			next->_random = NULL;
		cur = next->_next;
		if( cur )
			next = cur->_next;
	}
	cur = head;
	next = cur->_next;
	comnode* result = next;
	while( cur ){
		cur->_next = next->_next;
		cur = cur->_next;
		if( cur ){
			next->_next = cur->_next;
			next = next->_next;
		}
	}
	return result;
}

void print_random( comnode* head ){
	comnode* cur = head;
	cout << "list:";
	while( cur ){
		cout << cur->_data << "->";
		cur = cur->_next;
	}
	cout << "NULL" << endl << "random:";
	cur = head;
	while( cur ){
		if( cur->_random )
			cout << cur->_random->_data << " ";
		else
			cout << "NULL" << " ";
		cur = cur->_next;
	}
	cout << endl;
}

int main(){
	comnode* head = new comnode(1);
	comnode* n1 = new comnode(2);
	comnode* n2 = new comnode(4);
	comnode* n3 = new comnode(5);
	comnode* n4 = new comnode(9);

	head->_next = n1;
	n1->_next = n2;
	n2->_next = n3;
	n3->_next = n4;
	n4->_next = NULL;

	head->_random = n2;
	n1->_random = head;
	n2->_random = n3;
	n3->_random = NULL;
	n4->_random = n4;

	system( "clear" );
	comnode* copy_list = copy_complex_list( head );
	print_random(head);
	cout << "copy_list:" << endl;
	print_random(copy_list);

	return 0;
}
