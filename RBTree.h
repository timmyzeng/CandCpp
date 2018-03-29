/*************************************************************************
	> File Name: RBTree.h
	> Author: Timmy
	> Created Time: 2018年03月29日 星期四 16时19分49秒
 ************************************************************************/

#include <iostream>

using namespace std;

enum color{
    RED,
    BLACK
};

template <class K, class V>
struct RBTreeNode{
    K _key;
    V _value;
    color _col;
    RBTreeNode<K, V>* _left;
    RBTreeNode<K, V>* _right;
    RBTreeNode<K, V>* _parent;

    RBTreeNode(const K& key, const V& value)
        :_key(key)
        ,_value(value)
        ,_col(RED)
        ,_left(NULL)
        ,_right(NULL)
        ,_parent(NULL)
    {}
};

template <class K, class V>
class RBTree{
typedef RBTreeNode<K, V> Node;
public:
    //constructor
    RBTree()
        :_root(NULL)
    {}
    //Insert
    bool Insert(const K& key, const V& value){
        if(_root == NULL){
            _root = new Node(key, value);
            _root->_col = BLACK;
            return true;
        }
        Node* cur = _root;
        Node* parent = NULL;
        //find the locationg to insert Node
        while(cur){
            if(cur->_key < key){
                parent = cur;
                cur = cur->_right;
            }
            else if(cur->_key > key){
                parent = cur;
                cur = cur->_left;
            }
            else{
                return false;
            }
        }
        //insert
        //link cur and parent
        cur = new Node(key, value);
        if(parent->_key < key){
            parent->_right = cur;
        }
        else{
            parent->_left = cur;
        }
        cur->_parent = parent;
        //if parent == NULL,stop
        while(parent && parent->_col == RED){
            Node* grandfather = parent->_parent;
            //parent == grandfather->_left
            if(parent == grandfather->_left){
                Node* uncle = grandfather->_right;
                if(uncle && uncle->_col == RED){
                    parent->_col = BLACK;
                    uncle->_col = BLACK;
                    grandfather->_col = RED;
                    //continue
                    cur = grandfather;
                    parent = cur->_parent;
                }
                else{
                    if(cur == parent->_right){
                        RotateL(parent);
                    }
                    RotateR(grandfather);
                    parent->_col = BLACK;
                    grandfather->_col = RED;
                }
            }
            //parent == grandfather->_right
            else{
                Node* uncle = grandfather->_left;
                if(uncle && uncle->_col == RED){
                    parent->_col = uncle->_col = BLACK;
                    grandfather->_col = RED;
                    //contine
                    cur = grandfather;
                    parent = cur->_parent;
                }
                else{
                    if(cur == parent->_left){
                        RotateR(parent);
                    }
                    RotateL(grandfather);
                    parent->_col = BLACK;
                    grandfather->_col = RED;
                }
            }
        }
        _root->_col = BLACK;
        return true;
    }
    //RotateL
    void RotateL(Node* cur){
        Node* subR = cur->_right;
        Node* subRL = subR->_left;
        
        cur->_right = subRL;
        if(subRL){
            subRL->_parent = cur;
        }
        Node* ppNode = cur->_parent;
        cur->_parent = subR;
        subR->_left = cur;
        if(ppNode == NULL){
            _root = subR;
            _root->_parent = NULL;
        }
        else{
            subR->_parent = ppNode;
            if(ppNode->_left == cur){
                ppNode->_left = subR;
            }
            else{
                ppNode->_right = subR;
            }
        }
    }
    //RotateR
    void RotateR(Node* cur){
        Node* subL = cur->_left;
        Node* subLR = subL->_right;
        
        cur->_left = subLR;
        if(subLR){
            subLR->_parent = cur;
        }
        Node* ppNode = cur->_parent;
        cur->_parent = subL;
        subL->_right = cur;
        if(ppNode == NULL){
            _root = subL;
            _root->_parent = NULL;
        }
        else{
            if(ppNode->_left == cur){
                ppNode->_left = subL;
            }
            else{
                ppNode->_right = subL;
            }
        }
    }
    //IsBalance
    bool IsBalance(){
        //_root == RED
        if(_root && _root->_col == RED){
            cout << "wrong color in root" << endl;
            return false;
        }
        size_t Num = 0;
        size_t BlackNum = 0;
        Node* cur = _root;
        while(cur){
            if(cur->_col == BLACK){
                ++ Num;
            }
            cur = cur->_left;
        }
        return _IsBalance(_root, Num, BlackNum);
    }
    bool _IsBalance(Node* cur, const size_t Num, size_t BlackNum){
        if(cur == NULL){
            //blacknum == Num(base blacknum)
            if(Num != BlackNum){
                cout << "wrong black number" << endl;
                return false;
            }
            return true;
        }
        //two RED Node
        if(cur->_col == RED && cur->_parent->_col == RED){
            cout << "two red node:" << cur->_key << endl;
            return false;
        }
        if(cur->_col == BLACK){
            ++ BlackNum;
        }
        _IsBalance(cur->_left, Num , BlackNum);
        _IsBalance(cur->_right, Num , BlackNum);
    }
private:
    Node* _root;
};

void TestRBTree(){
    RBTree<int, int> rbtree;
    int arr1[] = {1,2,3,4,5};
    int arr2[] = {4, 2, 6, 1, 3, 5, 15, 7, 16, 14};
    for(int i = 0; i < sizeof(arr2)/sizeof(arr2[0]); ++i){
        rbtree.Insert(arr2[i], arr2[i]);
    }
    cout << "IsBalance?" << rbtree.IsBalance() << endl;
}
