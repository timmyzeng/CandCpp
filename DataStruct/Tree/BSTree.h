/*************************************************************************
	> File Name: BSTree.h
	> Author: Timmy
	> Created Time: 2018年03月18日 星期日 16时30分00秒
 ************************************************************************/

#include <iostream>

using namespace std;

template <class K>
struct BStreeNode{
	K _key;
	BStreeNode<K>* _left;
	BStreeNode<K>* _right;

	BStreeNode(const K& key)
		:_key(key)
		,_left(NULL)
		,_right(NULL)
	{}
};

template <class K>
class BSTree{
typedef BStreeNode<K> Node;
public:
	//constructor
	BSTree()
		:_root(NULL)
	{}
	//Insert
	bool Insert(const K& key){
		//root == NULL
		if(_root == NULL){
			_root = new Node(key);
			return true;
		}
		Node* cur = _root;
		Node* parent = NULL;
		while(cur){
			if(cur->_key < key){
				parent = cur;
				cur = cur->_right;
			}
			else if(cur->_key > key){
				parent = cur;
				cur = cur->_left;
			}
			//_key == key
			else{
				return false;
			}
		}
		cur = new Node(key);
		//_right
		if(parent->_key < key){
			parent->_right = cur;
		}
		//_left
		else{
			parent->_left = cur;
		}
		return true;
	}
	//InsertR
	bool InsertR(const K& key){
		return _InsertR(_root, key);
	}
	bool _InsertR(Node*& root, const K& key){
		if(root == NULL){
			root = new Node(key);
		}
		else if(root->_key < key){
			_InsertR(root->_right, key);
		}
		else if(root->_key > key){
			_InsertR(root->_left, key);
		}
		else
			return false;
		return true;
	}

	//Find
	Node* Find(const K& key){
		if(_root){
			Node* cur = _root;
			while(cur){
				if(cur->_key < key){
					cur = cur->_right;
				}
				else if(cur->_key > key){
					cur = cur->_left;
				}
				else{
					return cur;
				}
			}
		}
		return NULL;
	}
	//FindR
	Node* FindR(const K& key){
		return _FindR(_root, key);
	}
	Node* _FindR(Node* root, const K& key){
		if(root == NULL)
			return NULL;
		else if(root->_key < key){
			_FindR(root->_right, key);
		}
		else if(root->_key > key){
			_FindR(root->_left, key);
		}
		else{
			return root;
		}
	}

	//Remove
	//先查找到需要删除的节点
	//如果节点是叶子节点,处理方式和只有一个孩子节点的节点一致
	//只有一个孩子节点要分左右：
	//但是同时先考虑一个问题。parent节点是否为NULL，NULL表示删除的是当前二叉树的根节点
	//如果不是NULL，再分清楚是左边还是右边
	//如果删除的节点有两个孩子节点，采取替换的方法：
	//现在删除节点的右子树找到最小的节点，一般是右子树的最左节点。
	//如果找到了最左节点，那么替换再删除。
	//如果没有找到最左节点，那么就是当前节点的下一个节点被删除。
	bool Remove(const K& key){
		if(_root){
			Node* cur = _root;
			Node* parent = NULL;
			//find node
			while(cur){
				if(cur->_key < key){
					parent = cur;
					cur = cur->_right;
				}
				else if(cur->_key > key){
					parent = cur;
					cur = cur->_left;
				}
				//remove
				else{
					Node* del = cur;
					//cur->_left == NULL
					if(cur->_left == NULL){
						//if del == root
						if(parent == NULL){
							_root = cur->_right;
						}
						else{
							//parent->_left == cur
							if(parent->_left == cur){
								parent->_left = cur->_right;
							}
							else{
								parent->_right = cur->_right;
							}
						}
					}
					//cur->_right == NULL
					else if(cur->_right == NULL){
						if(parent == NULL){
							_root = cur->_left;
						}
						else{
							if(parent->_left == cur){
								parent->_left = cur->_left;
							}
							else{
								parent->_right = cur->_left;
							}
						}
					}
					//complex
					else{
						parent = cur;
						Node* pos = cur->_right;
						while(pos->_left){
							parent = pos;
							pos = pos->_left;
						}
						cur->_key = pos->_key;
						del = pos;
						//pos->_right != NULL
						if(pos->_right){
							parent->_right = pos->_right;
						}
						else{
							parent->_left = NULL;
						}
					}
					//delete
					delete del;
					return true;
				}
			}
		}
		//can't find
		return false;
	}

	//RemoveR
	bool RemoveR(const K& key){
		return _RemoveR(_root, key);
	}
	bool _RemoveR(Node*& root, const K& key){
		if(root){
			Node* cur = root;
			if(cur->_key < key){
				_RemoveR(root->_right, key);
			}
			else if(cur->_key > key){
				_RemoveR(root->_left, key);
			}
			else{
				Node* del = root;
				if(root->_left == NULL){
					root = root->_right;
				}
				else if(root->_right == NULL){
					root = root->_left;
				}
				else{
					Node* pos = root->_right;
					while(pos->_left){
						pos = pos->_left;
					}
					root->_key = pos->_key;
					return _RemoveR(root->_right, pos->_key);
				}
				delete del;
				return true;
			}
		}
		return false;
	}

	//InOrder
	void InOrder(){
		_InOrder(_root);
		cout << endl;
	}
	void _InOrder(Node* root){
		if(root){
			_InOrder(root->_left);
			cout << root->_key << " ";
			_InOrder(root->_right);
		}
		return;
	}
	//for test
	void ShowKey(Node* root){
		if(root){
			cout << root->_key << endl;
		}
		else
			cout << "NULL" << endl;
	}
private:
	Node* _root;
};

//TestBSTree
void TestBSTree(){
	BSTree<int> bstree;
	//Insert
	bstree.Insert(5);
	bstree.Insert(6);
	bstree.Insert(4);
	bstree.Insert(7);
	bstree.Insert(3);
	bstree.Insert(8);
	bstree.Insert(2);
	bstree.Insert(9);
	bstree.Insert(1);
	bstree.InOrder();
	////InsertR
	//bstree.InsertR(5);
	//bstree.InsertR(2);
	//bstree.InsertR(6);
	//bstree.InsertR(1);
	//bstree.InsertR(7);
	//bstree.InsertR(4);
	//bstree.InsertR(6);
	//bstree.InOrder();
	//
	//Find
	bstree.ShowKey(bstree.Find(1));
	bstree.ShowKey(bstree.Find(2));
	bstree.ShowKey(bstree.Find(3));
	bstree.ShowKey(bstree.Find(4));
	bstree.ShowKey(bstree.Find(5));
	bstree.ShowKey(bstree.Find(6));
	bstree.ShowKey(bstree.Find(7));
	bstree.ShowKey(bstree.Find(8));
	bstree.ShowKey(bstree.Find(9));
	bstree.ShowKey(bstree.Find(10));
	bstree.ShowKey(bstree.Find(50));
	bstree.ShowKey(bstree.Find(0));
	////FindR
	//bstree.ShowKey(bstree.FindR(1));
	//bstree.ShowKey(bstree.FindR(2));
	//bstree.ShowKey(bstree.FindR(3));
	//bstree.ShowKey(bstree.FindR(4));
	//bstree.ShowKey(bstree.FindR(5));
	//bstree.ShowKey(bstree.FindR(6));
	//bstree.ShowKey(bstree.FindR(7));
	//bstree.ShowKey(bstree.FindR(8));
	//bstree.ShowKey(bstree.FindR(9));
	//bstree.ShowKey(bstree.FindR(10));
	//bstree.ShowKey(bstree.FindR(50));
	//bstree.ShowKey(bstree.FindR(0));
	//
	//Remove
	bstree.Remove(1);
	bstree.Remove(3);
	bstree.Remove(5);
	bstree.Remove(7);
	bstree.Remove(10);
	bstree.InOrder();

	bstree.Remove(1);
	bstree.Remove(2);
	bstree.Remove(3);
	bstree.Remove(4);
	bstree.Remove(5);
	bstree.Remove(6);
	bstree.Remove(7);
	bstree.Remove(8);
	bstree.Remove(10);
	bstree.InOrder();
	////RemoveR
	//bstree.RemoveR(1);
	//bstree.RemoveR(3);
	//bstree.RemoveR(5);
	//bstree.RemoveR(7);
	//bstree.RemoveR(10);
	//bstree.InOrder();

	//bstree.RemoveR(1);
	//bstree.RemoveR(2);
	//bstree.RemoveR(3);
	//bstree.RemoveR(4);
	//bstree.RemoveR(5);
	//bstree.RemoveR(6);
	//bstree.RemoveR(7);
	//bstree.RemoveR(8);
	//bstree.RemoveR(10);
	//bstree.InOrder();
}
