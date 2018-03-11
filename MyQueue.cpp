/*************************************************************************
	> File Name: MyQueue.cpp
	> Author: Timmy
	> Created Time: 2018年03月07日 星期三 01时47分55秒
 ************************************************************************/

#include <iostream>

using namespace std;

template <class T>
struct QueueNode{
	T _data;
	QueueNode<T>* _next;

	QueueNode(const T& data)
		:_data(data)
		,_next(NULL)
	{}
};

template <class T>
class MyQueue{
typedef QueueNode<T> Node;
public:
	//constructor
	MyQueue()
		:_size(0)
		,_front(NULL)
		,_rear(NULL)
	{}
	//destructor
	~MyQueue(){
		if(_front){
			while(_front != _rear){
				Node* tmp = _front;
				_front = _front->_next;
				delete tmp;
			}
		}
	}
	//Empty
	bool Empty(){
		return _size == 0;
	}
	//Size
	size_t Size(){
		return _size;
	}
	//Front
	T& Front(){
		if(!Empty()){
			return _front->_data;
		}
	}
	//Back
	T& Back(){
		if(!Empty()){
			return _rear->_data;
		}
	}
	//Push
	void Push(const T& val){
		Node* tmp = new Node(val);
		if(_front == 0){
			_front = _rear = tmp;
		}
		else{
			_rear->_next = tmp;
			_rear = tmp;
		}
		++ _size;
	}
	//Pop
	void Pop(){
		if(!Empty()){
			Node* cur= _front;
			while(cur->_next != _rear){
				cur = cur->_next;
			}
			delete _rear;
			_rear = cur;
			-- _size;
		}
	}
	//Print
	void Print(){
		if(_front){
			Node* cur= _front;
			while(cur != NULL){
				cout << cur->_data << " ";
				cur = cur->_next;
			}
			cout << endl;
		}
	}
protected:
	Node* _front;
	Node* _rear;
	size_t _size;
};

int main(){
	system("clear");
	MyQueue<int> q;
	q.Push(1);
	q.Push(2);
	q.Push(3);
	q.Push(4);
	q.Print();
	cout << "Empty" << endl;
	cout << q.Empty() << endl;
	cout << "Size" << endl;
	cout << q.Size() << endl;
	cout << "Front" << endl;
	cout << q.Front() << endl;
	cout << "Back" << endl;
	cout << q.Back() << endl;
	q.Pop();
	q.Pop();
	cout << "Size" << endl;
	cout << q.Size() << endl;
	cout << "Front" << endl;
	cout << q.Front() << endl;
	cout << "Back" << endl;
	cout << q.Back() << endl;
	return 0;
}
