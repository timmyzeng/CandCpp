/*************************************************************************
	> File Name: BinaryTree.cpp
	> Author: Timmy
	> Created Time: 2018年03月05日 星期一 18时58分36秒
 ************************************************************************/

#include <iostream>
//system需要这个头文件？之前并不需要的，用g++需要
#include <cstdlib>
#include <assert.h>
#include <queue>
#include <stack>

using namespace std;
template <class T> 
struct BinaryTreeNode 
{
	BinaryTreeNode* _left; 
	BinaryTreeNode* _right; 
	T _data; 

	BinaryTreeNode(const T& data = T()){
		_data = data; 
		_left = NULL;
		_right = NULL;
	}
}; 

template <class T>
class BinaryTree 
{
typedef BinaryTreeNode<T> Node; 
public:
	//constructor
	BinaryTree(){
		_root = NULL;
	}
	BinaryTree(const T* a, const T& invalid){
		size_t index = 0;
		_root = _CreateTree(a, invalid, index);
	}
	Node* _CreateTree(const T* a, const T& invalid, size_t& index){
		Node* root = NULL;
		if(a[index] != invalid){
			root = new Node(a[index]);
			root->_left = _CreateTree(a, invalid, ++index);
			root->_right = _CreateTree(a, invalid, ++index);
		}
		return root;
	}

	BinaryTree(const BinaryTree& tree){
		_root = _CopyTree(tree._root);
	}
	Node* _CopyTree(Node* root){
		Node* node = root;
		if(node){
			node = new Node(root->_data);
			node->_left = _CopyTree(root->_left);
			node->_right = _CopyTree(root->_right);
		}
		return node;
	}
	//destructor
	~BinaryTree(){
		Destroy(_root);
	}
	void Destroy(Node* root){
		if(root == NULL)
			return;
		Destroy(root->_left);
		Destroy(root->_right);
		delete root;
	}

	//operator=
	BinaryTree<T>& operator=(const BinaryTree<T>& tree){
		if(this != &tree){
			Destroy(_root);
			_root = _CopyTree(tree._root);
			return *this;
		}
	}
	//BinaryTree<T>& operator=(BinaryTree<T> tree){
		//if(this != &tree){
			//swap(_root, tree._root);
			//return *this;
		//}
	//}

	//PrevOrder
	void PrevOrder(){
		_PrevOrder(_root);
		cout << endl;
	}
	void _PrevOrder(Node* root){
		if(root){
			cout << root->_data << " ";
			_PrevOrder(root->_left);
			_PrevOrder(root->_right);
		}
		return;
	}
	//InOrder
	void InOrder(){
		_InOreder(_root);
		cout << endl;
	}
	void _InOreder(Node* root){
		if(root){
			_InOreder(root->_left);
			cout << root->_data << " ";
			_InOreder(root->_right);
		}
		return;
	}
	//PostOrder
	void PostOrder(){
		_PostOrder(_root);
		cout << endl;
	}
	void _PostOrder(Node* root){
		if(root){
			_PostOrder(root->_left);
			_PostOrder(root->_right);
			cout << root->_data << " ";
		}
		return;
	}
	//LevelOrder
	void LevelOrder(){
		//不能是T，要用到root->_left; root->_right;
		//不好是Node，结构体太大;
		queue<Node*> q;
		if(_root){
			q.push(_root);
			while(!q.empty()){
				Node* top = q.front();
				q.pop();
				cout << top->_data << " ";
				if(top->_left)
					q.push(top->_left);
				if(top->_right)
					q.push(top->_right);
			}
		}
		cout << endl;
	}
	//PrevOrderNonR
	void PrevOrderNonR(){
		//利用栈得以记录访问过的根，用来以后访问右子树
		stack<Node*> s;
		Node* cur = _root;
		while(cur || !s.empty()){
			//根据先根的次序，访问当前节点，并一路向左访问
			while(cur){
				cout << cur->_data << " ";
				s.push(cur);
				cur = cur->_left;
			}
			Node* top = s.top();
			//pop表示左子树已经访问完，接下来访问右子树
			s.pop();
			//右子树的访问是子问题
			cur = top->_right;
		}
		cout << endl;
	}
	//InOrderNonR
	void InOrderNonR(){
		stack<Node*> s;
		Node* cur = _root;
		while(cur || !s.empty()){
			while(cur){
				s.push(cur);
				cur = cur->_left;
			}
			Node* top = s.top();
			s.pop();
			cout << top->_data << " ";
			//....
			cur = top->_right;
		}
		cout << endl;
	}
	//PostOrderNonR
	void PostOrderNonR(){
		stack<Node*> s;
		Node* cur = _root;
		Node* prev = NULL;
		while(cur || !s.empty()){
			while(cur){
				s.push(cur);
				cur = cur->_left;
			}
			Node* top = s.top();
			if(top->_right == NULL || prev == top->_right){
				s.pop();
				prev = top;
				cout << top->_data << " ";
			}
			else{
				//....
				cur = top->_right;
			}
		}
		cout << endl;
	}
	//Size
	size_t Size(){
		return _Size(_root);
	}
	size_t _Size(Node* root){
		if(root == NULL)
			return 0;
		return _Size(root->_left) + _Size(root->_right) + 1;
	}
	//Depth
	size_t Depth(){
		return _Depth(_root);
	}
	size_t _Depth(Node* root){
		size_t leftnum = 0;
		size_t rightnum = 0;
		if(root == NULL)
			return 0;
		if(root->_left)
			leftnum += _Depth(root->_left);
		if(root->_right)
			rightnum += _Depth(root->_right);
		return (leftnum > rightnum ? leftnum : rightnum) + 1;
	}
	//LeafSize
	size_t LeafSize(){
		return _LeafSize(_root);
	}
	size_t _LeafSize(Node* root){
		if(root == NULL)
			return 0;
		if(root->_left == NULL && root->_right == NULL)
			return 1;
		return _LeafSize(root->_left) + _LeafSize(root->_right);
	}
	//GetKLevel
	size_t GetKLevel(size_t K){
		return _GetKLevel(_root, K);
	}
	size_t _GetKLevel(Node* root, size_t K){
		if(K == 0 || root == NULL)
			return 0;
		if(K == 1)
			return 1;
		//不能使用--K，应该用K-1。
		//不能返回除了K=1的其他情况。
		return _GetKLevel(root->_left, K - 1) + _GetKLevel(root->_right, K - 1);
	}

protected: 
	Node* _root; 
}; 

void TestBinaryTree() 
{
	int a1[] = {1,2,3,'#','#',4,'#','#',5,6,'#','#','#'};
	int a2[] = {1,2,'#',3,'#','#',4,5,'#',6,'#',7,'#','#',8,'#','#'}; 
	BinaryTree<int> tree(a1,'#'); 
	BinaryTree<int> tree1(a2, '#');
	BinaryTree<int> tree2(tree);
	tree2 = tree1;

	cout << "tree.PrevOrder" << endl;
	tree.PrevOrder();
	cout << "tree1.InOrder" << endl;
	tree1.InOrder();
	cout << "tree2.PostOrder" << endl;
	tree2.PostOrder();

	cout << "tree.LevelOrder" << endl;
	tree.LevelOrder();
	cout << "tree.PrevOrderNonR" << endl;
	tree.PrevOrderNonR();
	cout << "tree1.InOrderNonR" << endl;
	tree1.InOrderNonR();
	cout << "tree2.PostOrderNonR" << endl;
	tree2.PostOrderNonR();

	cout << "tree.Size:" << tree.Size() << endl;
	cout << "tree.Depth:" << tree.Depth() << endl;
	cout << "tree.LeafSize:" << tree.LeafSize() << endl;
	cout << "tree.GetKLevel(K=2):" << tree.GetKLevel(2) << endl;

	cout << "tree1.Size:" << tree1.Size() << endl;
	cout << "tree1.Depth:" << tree1.Depth() << endl;
	cout << "tree1.LeafSize:" << tree1.LeafSize() << endl;
	cout << "tree1.GetKLevel(K=3):" << tree1.GetKLevel(3) << endl;
}

int main(){
	system("clear");
	TestBinaryTree();
	return 0;
}
