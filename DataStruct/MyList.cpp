/*************************************************************************
	> File Name: MyList.cpp
	> Author: Timmy
	> Created Time: 2018年03月03日 星期六 12时00分59秒
 ************************************************************************/

#include <iostream>
#include <assert.h>

using namespace std;

template <class T>
struct ListNode{
	T _data;
	ListNode<T>* _next;
	ListNode<T>* _prev;

	ListNode(const T& x){
		_data = x;
		_next = NULL;
		_prev = NULL;
	}
};

//Ptr = T*, Ref = T&
//Ptr = const T*, Ref = const T&
template <class T, class Ptr, class Ref>
struct ListIterator{
	typedef ListIterator<T, Ptr, Ref> Self;
	typedef ListNode<T> Node;
	Node* _node;

	ListIterator(Node* node){
		_node = node;
	}

	//*
	Ref operator*(){
		return _node->_data;
	}
	//->
	Ptr operator->(){
		return &(_node->_data);
	}
	//++
	Self& operator++(){
		_node = _node->_next;
		return *this;
	}
	//++(int)
	//不使用&，返回的是临时变量
	Self operator++(int){
		Node* tmp = _node;
		_node = _node->_next;
		return Self(tmp);
	}
	//--
	Self& operator--(){
		_node = _node->_prev;
		return *this;
	}
	//--(int)
	Self operator--(int){
		Node* tmp = _node;
		_node = _node->_prev;
		return Self(tmp);
	}
	//!=
	bool operator!=(const Self& s){
		return _node != s._node;
	}
	//==
	bool operator==(const Self& s){
		return _node == s._node;
	}
};

template <class T>
class MyList{
public:
	typedef ListNode<T> Node;
	typedef T* Pointer;
	typedef T& Reference;
	typedef ListIterator<T, T*, T&> Iterator;
	typedef ListIterator<T, const T*, const T&> ConstIterator;

	//constructor
	MyList(){
		_head = new Node(T());
		_head->_next = _head;
		_head->_prev = _head;
	}
	//destructor
	~MyList(){
		Clear();
		//Iterator it = Begin();
		//while(it != End()){
			//Node* tmp = it._node;
			//delete tmp;
			//++it;
		//}
		delete _head;
		_head = NULL;
	}

	//Iterator
	//Begin
	Iterator Begin(){
		return Iterator(_head->_next);
	}
	ConstIterator Begin()const{
		return ConstIterator(_head->_next);
	}
	//End
	Iterator End(){
		return Iterator(_head);
	}
	ConstIterator End()const{
		return ConstIterator(_head);
	}
	//Capatcity
	//Empty
	bool Empty(){
		return _head->_next == _head;
	}
	//Size
	size_t Size(){
		size_t size = 0;
		Iterator cur = _head->_next;
		while(cur != _head){
			++ size;
			++ cur;
		}
		return size;
	}
	//Element access
	//Front
	Reference Front(){
		return _head->_next->_data;
	}
	//Back
	Reference Back(){
		return _head->_prev->_data;
	}
	//Modifiers
	//PushBack
	void PushBack(const T& val){
		Insert(_head, val);
		//Node* tail = _head->_prev;
		//Node* newnode = new Node(val);

		//tail->_next = newnode;
		//newnode->_prev = tail;
		//newnode->_next = _head;
		//_head->_prev = newnode;
	}
	//PushFront
	void PushFront(const T& val){
		Insert(_head->_next, val);
	}
	//PopBack
	void PopBack(){
		Erase(--End());
		//if(_head->_next != _head){
			//Node* cur = _head->_prev;
			//Node* prev = cur->_prev;
			//prev->_next = _head;
			//_head->_prev = prev;
			//delete cur;
		//}
	}
	//PopFront
	void PopFront(){
		Erase(Begin());
		//if(_head->_next != _head){
			//Node* cur = _head->_next;
			//Node* next = cur->_next;
			//_head->_next = next;
			//next->_prev = _head;
			//delete cur;
		//}
	}
	//Insert
	//before pos
	void Insert(Iterator pos, const T& val){
		assert(pos._node != NULL);
		Node* cur = pos._node;
		Node* prev = cur->_prev;
		Node* newnode = new Node(val);
		prev->_next = newnode;
		newnode->_prev = prev;
		newnode->_next = cur;
		cur->_prev = newnode;
	}
	//Erase
	void Erase(Iterator pos){
		assert(pos._node != NULL);
		if(_head->_next != _head){
			Node* prev = pos._node->_prev;
			Node* next = pos._node->_next;
			prev->_next = next;
			next->_prev = prev;
			delete pos._node;
		}
	}
	//Clear
	void Clear(){
		Iterator it = Begin();
		while(it != End()){
			Node* tmp = it._node;
			delete tmp;
			++ it;
		}
		_head->_next = _head;
		_head->_prev = _head;
	}
private:
	Node* _head;
};

template <class T>
void Print(const MyList<T>& list){
	//不能漏了typename
	typename MyList<T> :: ConstIterator citl = list.Begin();
	while(citl != list.End()){
		cout << *citl << " ";
		++ citl;
	}
	cout << endl;
}

int main(){
	system("clear");
	MyList<int> list;
	list.PushBack(1);
	list.PushBack(2);
	list.PushBack(3);
	list.PushBack(4);
	list.PushFront(5);
	Print<int>(list);
	cout << list.Empty() << endl;
	cout << list.Size() << endl;
	list.PopBack();
	list.PopFront();
	Print<int>(list);
	cout << list.Size() << endl;
	cout << list.Front() << " " << list.Back() << endl;
	cout << "1" << endl;
	return 0;
}

