#pragma once
enum PointerTag{
	THREAD,
	LINK
};

template <class T>
struct BinaryTreeNodeThd{
	T _data;
	BinaryTreeNodeThd<T>* _left;
	BinaryTreeNodeThd<T>* _right;
	PointerTag _leftTag;
	PointerTag _rightTag;

	BinaryTreeNodeThd(const T& x){
		_data = x;
		_left = NULL;
		_right = NULL;
		_leftTag = LINK;
		_rightTag = LINK;
	}
};

//TreeIterator
template <class T, class Ptr, class Ref>
struct TreeIterator{
	typedef BinaryTreeNodeThd<T> Node;
	typedef TreeIterator<T, Ptr, Ref> Self;
	Node* _node;

	TreeIterator(Node* node)
		:_node(node)
	{}
	
	Ref operator*(){
		return _node->_data;
	}
	Ptr operator->(){
		return &(operator*());
	}
	bool operator!=(const Self& s){
		return _node != s._node;
	}
	bool operator==(const Self& s){
		return _node == s._node;
	}
};

//InOrderTreeIterator
template <class T, class Ptr, class Ref>
struct InOrderTreeIterator:public TreeIterator<T, Ptr, Ref> {
	typedef BinaryTreeNodeThd<T> Node;
	typedef InOrderTreeIterator<T, Ptr, Ref> Self;
	typedef TreeIterator<T, Ptr, Ref> treeIterator;
	InOrderTreeIterator(Node* node)
		:treeIterator(node)
	{}

	Self& operator++(){
		if(treeIterator::_node->_rightTag == THREAD){
			treeIterator::_node = treeIterator::_node->_right;
		}
		else{
			treeIterator::_node = treeIterator::_node->_right;
			while(treeIterator::_node->_leftTag == LINK){
				treeIterator::_node = treeIterator::_node->_left;
			}
		}
		return *this;
	}
};

//PrevOrderTreeIterator
template <class T, class Ptr, class Ref>
struct PrevOrderTreeIterator:public TreeIterator<T, Ptr, Ref> {
	typedef BinaryTreeNodeThd<T> Node;
	typedef PrevOrderTreeIterator<T, Ptr, Ref> Self;
	typedef TreeIterator<T, Ptr, Ref> Iterator;
	PrevOrderTreeIterator(Node* node)
		:Iterator(node)
	{}

	Self& operator++(){
		if(Iterator::_node->_leftTag == LINK){
			Iterator::_node = Iterator::_node->_left;
		}
		else{
			Iterator::_node = Iterator::_node->_right;
		}
		return *this;
	}
};

template <class T>
class BinaryTreeThd{
	typedef BinaryTreeNodeThd<T> Node;
public:
	typedef InOrderTreeIterator<T, T*, T&> InIterator;
	typedef PrevOrderTreeIterator<T, T*, T&> PrevIterator;
	typedef InOrderTreeIterator<T, const T*, const T&> ConstInIterator;

	//InIterator
	InIterator InBegin(){
		Node* left = _root;
		while(left && left->_leftTag == LINK){
			left = left->_left;
		}
		return InIterator(left);
	}
	InIterator InEnd(){
		return InIterator(NULL);
	}
	//PrevIterator
	PrevIterator PrevBegin(){
		return PrevIterator(_root);
	}
	PrevIterator PrevEnd(){
		return PrevIterator(NULL);
	}
	//construtor
	BinaryTreeThd(T* a, const T& invalid){
		size_t index = 0;
		_root = _CreateTree(a, invalid, index);
	}
	Node* _CreateTree(T* a, const T& invalid, size_t& index){
		Node* root = NULL;
		if(a[index] != invalid){
			root = new Node(a[index]);
			root->_left = _CreateTree(a, invalid, ++index);
			root->_right= _CreateTree(a, invalid, ++index);
		}
		return root;
	}
	//PrevOrderThreading
	void PrevOrderThreading(){
		Node* prev = NULL;
		_PrevOrderThreading(_root, prev);
		prev->_rightTag = THREAD;
	}
	void _PrevOrderThreading(Node* cur, Node*& prev){
		if(cur == NULL)
			return;
		if(cur->_left == NULL){
			cur->_left = prev;
			cur->_leftTag = THREAD;
		}
		if(prev && prev->_right == NULL){
			prev->_right = cur;
			prev->_rightTag = THREAD;
		}
		prev = cur;

		if(cur->_leftTag == LINK)
			_PrevOrderThreading(cur->_left, prev);
		if(cur->_rightTag == LINK)
			_PrevOrderThreading(cur->_right, prev);
	}
	//PrevOrderThd
	//root left right
	void PrevOrderThd(){
		Node* cur = _root;
		while(cur){
			while(cur->_leftTag == LINK){
				cout << cur->_data << " ";
				cur = cur->_left;
			}
			cout << cur->_data << " ";
			cur = cur->_right;
		}
		cout << endl;
	}
	//InOrderThreading
	void InOrderThreading(){
		Node* prev = NULL;
		_InOrderThreading(_root, prev);
		prev->_rightTag = THREAD;
	}
	void _InOrderThreading(Node* cur, Node*& prev){
		if(cur == NULL)
			return;
		_InOrderThreading(cur->_left, prev);
		if(cur->_left == NULL){
			cur->_left = prev;
			cur->_leftTag = THREAD;
		}
		if(prev && prev->_right == NULL){
			prev->_right = cur;
			prev->_rightTag = THREAD;
		}
		prev = cur;
		_InOrderThreading(cur->_right, prev);
	}
	//InOrderThd
	//left root right
	void InOrderThd(){
		Node* cur = _root;
		while(cur){
			while(cur->_leftTag == LINK){
				cur = cur->_left;
			}
			cout << cur->_data << " ";
			while(cur->_rightTag == THREAD){
				cur = cur->_right;
				if(cur == NULL)
					break;
				cout << cur->_data << " ";
			}
			if(cur)
				cur = cur->_right;
		}
		cout << endl;
	}
private:
	Node* _root;
};

void TestBinatyTreeThd(){
	int array[] = {1,2,'#',3,'#','#',4,5,'#',6,'#',7,'#','#',8,'#','#'};
	int array1[] = {1,2,3,'#','#',4,'#','#',5,6,'#','#','#'};
	BinaryTreeThd<int> tree(array, '#');
	BinaryTreeThd<int> tree1(array1, '#');
	tree.PrevOrderThreading();
	tree.PrevOrderThd();
	BinaryTreeThd<int>::PrevIterator pit = tree.PrevBegin();
	while(pit != tree.PrevEnd()){
		cout << *pit << " ";
		++ pit;
	}
	cout << endl;

	tree1.InOrderThreading();
	tree1.InOrderThd();

	BinaryTreeThd<int>::InIterator iit = tree1.InBegin();
	while(iit != tree1.InEnd()){
		cout << *iit << " ";
		++ iit;
	}
	cout << endl;
}
