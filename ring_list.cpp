/*************************************************************************
	> File Name: ring_list.1.17.cpp
	> Author: Timmy
	> Created Time: Sun 28 Jan 2018 10:24:03 PM CST
 ************************************************************************/

#include <iostream>

using namespace std;
//设计一个不能被继承的类
class person{
	public:
		friend class man;
	private:
		person(){}
};

class man:virtual public person {
	public:
		man(){
			age = 18;
		}
		void show(){
			cout << age << endl;
		}
	private:
		int age;
};

// class son:public man{
// 	public:
// 		son(){}
// };

int main(){
	man bob;
	system( "clear" );
	bob.show();
	return 0;
}


//
//wrong
//class person{
	//public:
		//friend class man;
	//private:
		//person(){
			//_num = 0;
		//}
		//int _num;
//};

//class man{
	//public:
		//void show( person &a){
			//cout << a::_num << endl;
		//}
//};

//int main(){
	//man a;
	//a.show();
	//return 0;
//} 

//判断链表是否带环，带环返回环的长度，环的入口。
//struct node{
	//node( int n ){
		//val = n;
		//next = NULL;
	//}
	//int val;
	//node* next;
//};

//node* is_ring( node* root ){
	//if( root == NULL || root->next == NULL )
		//return NULL;
	//node* fast = root;
	//node* slow = root;

	//do{
		//fast = fast->next->next;
		//slow = slow->next;
		//if( fast->next == NULL || fast->next->next == NULL )
			//return NULL;
	//}while( slow != fast );

	//return slow;
//}

//int ring_length( node* root ){
	//node* meet_node = is_ring( root );
	//node* slow = meet_node;
	//if( meet_node == NULL )
		//return 0;
	//int cnt = 0;
	//do{
		//meet_node = meet_node->next->next;
		//slow = slow->next;
		//cnt++;
	//}while( slow != meet_node );
	//return cnt;
//}

//node* entry_ring( node* root ){
	//node* meet_node = is_ring( root );
	//node* slow = root;
	//if( meet_node == NULL )
		//return NULL;
	//while( slow != meet_node ){
		//slow = slow->next;
		//meet_node = meet_node->next;
	//}
	//return slow;
//}

//void print( node* root ){
	//while( root ){
		//cout << root->val << "->";
		//root = root->next;
	//}
	//cout << "NULL" << endl;
//}

//int main(){
	//node* head = new node(8);
	//node* n1 = new node(2);
	//node* n2 = new node(3);
	//node* n3 = new node(4);
	//node* n4 = new node(5);

	//head->next = n1;
	//n1->next = n2;
	//n2->next = n3;
	//n3->next = n4;
	//n4->next = n2;

	//system( "clear" );
	//cout << is_ring(head)->val << endl;
	//cout << ring_length(head) << endl;;
	//cout << entry_ring(head)->val << endl;
	//return 0;
//}
