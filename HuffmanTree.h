#pragma once
#include "Heap.h"

template <class T>
struct HuffmanTreeNode{
	T _val;
	HuffmanTreeNode<T>* _left;
	HuffmanTreeNode<T>* _right;

	HuffmanTreeNode(const T& val)
		:_val(val)
		,_left(NULL)
		,_right(NULL)
	{}
};

template <class T>
class HuffmanTree{
	typedef HuffmanTreeNode<T> Node;
	struct NodeCompare{
		//const Node* left, const Node* right 
		//wrong
		bool operator()(Node* left, Node* right){
			return left->_val < right->_val;
		}
	};
public:
	//constructor
	HuffmanTree()
		:_root(NULL)
	{}
	HuffmanTree(T* arr, size_t size, const T& invalid){
		Heap<Node*, NodeCompare> minheap;
		for(int i = 0; i < size; ++i){
			if(arr[i] != invalid){
				//Node*
				minheap.Push(new Node(arr[i]));
			}
		}
		//minheap.Size()>1
		while(minheap.Size() > 1){
			Node* left = minheap.Top();
			minheap.Pop();
			Node* right = minheap.Top();
			minheap.Pop();
			Node* parent = new Node(left->_val + right->_val);
			parent->_left = left;
			parent->_right = right;
			minheap.Push(parent);
		}
		_root = minheap.Top();
	}
	//destructor
	~HuffmanTree(){
		Destroy(_root);
		_root = NULL;
	}
	void Destroy(Node* root){
		if(root){
			Destroy(root->_left);
			Destroy(root->_right);
			delete root;
		}
	}
	//GetRoot
	Node* GetRoot(){
		return _root;
	}
private:
	HuffmanTree(const HuffmanTree<T>& huf);
	Node*& operator=(const HuffmanTree<T>& huf);
	Node* _root;
};

void TestHuffmanTree(){
	int arr[] = {0,1,2,3,4,5,6,7,8,9};
	size_t Size = sizeof(arr)/sizeof(arr[0]);
	HuffmanTree<int> hp(arr, Size, arr[0]);
	cout << hp.GetRoot()->_val << endl;
}
