/*************************************************************************
	> File Name: 1.16.cpp
	> Author: Timmy
	> Created Time: Wed 24 Jan 2018 10:06:08 PM CST
 ************************************************************************/

#include <iostream>
#include <assert.h>

using namespace std;

//实现一个add函数，整型相加。不能使用+-*/，++，--

long long Add( int a, int b ){
	if( b == 0 )
		return a;
	int sum = a^b;
	b = (a&b)<<1;
	a = sum;
	return Add( a, b );
}

int main(){
	system( "clear" );
	cout << Add(3, 7) << endl;

	int a = 49;
	int b = 4;
	while( b != 0 ){
		int sum = a^b;
		b = (a&b)<<1;
		a = sum;
	}
	cout << a << endl;
	return 0;
}

//逆置单链表+查找单链表的倒数第k个节点，要求只能便利一次链表
//1、逆置单链表
//struct Node{
	//Node(){
		//_val = 0;
		//_next = NULL;
	//}
	//Node( int val ){
		//_val = val;
		//_next = NULL;
	//}

	//int _val; 
	//Node* _next;
//};

//void print( Node* n ){
	//if( n == NULL )
		//return;
	//while( n ){
		//cout << n->_val << "->";
		//n = n->_next;
	//}
	//cout << "NULL" << endl;
//}

//Node* my_reverse( Node*& head, int k ){
	//assert( k );
	//if( head == NULL )
		//return NULL;
	//Node* fast = head;
	//Node* slow = head;
	//Node* prev = head;
	//Node* next = slow->_next;
	//Node* knode = NULL;

	//while( k-- ){
		//fast = fast->_next;
		//if( fast == NULL ){
			//cout << "wrong length" << endl;
			//exit( -1 );
		//}
	//}

	//while( prev != next ){
		//slow = next;
		//if( slow->_next )
			//next = slow->_next;
		//if( fast != NULL ){
			//fast = fast->_next;
			//knode = prev;
		//}
		//slow->_next = prev;
		//prev = slow;
	//}
	//head->_next = NULL;
	//head = slow;
	//return knode;
//}

//int main(){
	//Node* head = new Node(1);
	//Node* n1= new Node(2);
	//Node* n2= new Node(4);
	//Node* n3= new Node(5);
	//Node* n4= new Node(6);

	//head->_next = n1;
	//n1->_next = n2;
	//n2->_next = n3;
	//n3->_next = n4;
	//n4->_next = NULL;
	//print(head);
	//cout << my_reverse( head, 1 )->_val << endl;
	//print(head);

	//return 0;
//}
