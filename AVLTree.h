/*************************************************************************
	> File Name: AVLTree.h
	> Author: Timmy
	> Created Time: 2018年03月21日 星期三 20时20分36秒
 ************************************************************************/

template <class K, class V>
struct AVLTreeNode{
	K _key;
	V _value;
	int _bf;
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;

	AVLTreeNode(const K& key, const V& value)
        :_key(key)
        ,_value(value)
        ,_bf(0)
        ,_left(NULL)
        ,_right(NULL)
        ,_parent(NULL)
	{}
};

template <class K, class V>
class AVLTree{
typedef AVLTreeNode<K, V> Node;
public:
    AVLTree()
        :_root(NULL)
    {}
	bool Insert(const K& key, const V& value){
        if(_root == NULL){
	        _root = new Node(key, value);
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
            else 
                return false;
        }
        //insert
        cur = new Node(key, value);
        if(parent->_key < cur->_key){
            parent->_right = cur;
            cur->_parent = parent;
        }
        else{
            parent->_left = cur;
            cur->_parent = parent;
        }
        //update
        while(parent){
            if(cur == parent->_left){
                parent->_bf --;
            }
            else if(cur == parent->_right){
                parent->_bf ++;
            }
            if(parent->_bf == 0){
                break;
            }
            else if(parent->_bf == -1 || parent->_bf == 1){
                cur = parent;
                parent = cur->_parent;
            }
            else if(parent->_bf == -2 || parent->_bf == 2){
                if(parent->_bf == 2){
                    if(cur->_bf == 1){
                        RotateL(parent);
                    }
                    else{
                        RotateRL(parent);
                    }
                }
                else{
                    if(cur->_bf == -1){
                        RotateR(parent);
                    }
                    else{
                        RotateLR(parent);
                    }
                }
                break;
            }
        }
        return true;
    }

    //left
    void RotateL(Node* parent){
        Node* subR = parent->_right;
        Node* subRL = subR->_left;
        
        parent->_right = subRL;
        if(subRL){
            subRL->_parent = parent;
        }
        Node* ppNode = parent->_parent;
        parent->_parent = subR;
        subR->_left = parent;
        
        if(_root == parent){
            _root = subR;
            _root->_parent = NULL;
        }
        else{
            if(ppNode->_left == parent){
                ppNode->_left = subR;
            }
            else{
                ppNode->_right = subR;
            }
            subR->_parent = ppNode;
        }
        parent->_bf = subR->_bf = 0;
    }

    //right
    void RotateR(Node* parent){
        Node* subL = parent->_left;
        Node* subLR = subL->_right;
        
        parent->_left = subLR;
        if(subLR){
            subLR->_parent = parent;
        }
        Node* ppNode = parent->_parent;
        parent->_parent = subL;
        subL->_right = parent;
        
        if(_root == parent){
            _root = subL;
            _root->_parent = NULL;
        }
        else{
            if(ppNode->_left == parent){
                ppNode->_left = subL;
            }
            else{
                ppNode->_right = subL;
            }
            subL->_parent = ppNode;
        }
        parent->_bf = subL->_bf = 0;
    }

    //left right
    void RotateLR(Node* parent){
        Node* subL = parent->_left;
        Node* subLR = subL->_right;
        RotateL(parent->_left);
        RotateR(parent);
        if(subLR->_bf == 0){
            parent->_bf = subL->_bf = 0;
        }
        else if(subLR->_bf == 1){
            parent->_bf = subLR->_bf = 0;
            subL->_bf = -1;
        }
        else if(subLR->_bf == -1){
            subL->_bf = subLR->_bf = 0;
            parent->_bf = 1;
        }
    }

    //right left
    void RotateRL(Node* parent){
        Node* subR = parent->_right;
        Node* subRL = subR->_left;
        RotateR(parent->_right);
        RotateL(parent);
        if(subRL->_bf == 0){
            parent->_bf = subR->_bf = 0;
        }
        else if(subRL->_bf == 1){
            subR->_bf = subRL->_bf =  0;
            parent->_bf = -1;
        }
        else if(subRL->_bf == -1){
            parent->_bf = subRL->_bf = 0;
            subR->_bf = 1;
        }
    }


private:
    Node* _root;
};

void TestAVLTree(){
    AVLTree<int, int> avltree;

    avltree.Insert(16,16);
    avltree.Insert(3,32);
    avltree.Insert(7,7);
    avltree.Insert(11,11);
    avltree.Insert(9,9);
    avltree.Insert(26,26);
    avltree.Insert(18,18);
    avltree.Insert(14,4);
    avltree.Insert(15,15);
}
