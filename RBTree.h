#pragma once

#include <iostream>

using namespace std;

enum Color{RED, BLACK};

template <class V>
struct RBTreeNode{
    RBTreeNode<V>* _left;
    RBTreeNode<V>* _right;
    RBTreeNode<V>* _parent;

    V _v;
    Color _col;

    RBTreeNode(const V& v)
        :_v(v)
         ,_left(NULL)
         ,_right(NULL)
         ,_parent(NULL)
         ,_col(RED)
    {}
};

template<class V, class Ref, class Ptr>
struct __RBTreeIterator{
    typedef RBTreeNode<V> Node;
    typedef __RBTreeIterator<V, Ref, Ptr> Self;
    Node* _node;

    __RBTreeIterator()
    {}

    __RBTreeIterator(Node* node)
        :_node(node)
    {}

    Ref operator*(){
        return _node->_v;
    }

    Ptr operator->(){
        return &(operator*());
    }

    Self operator++(){
        if(_node->_right){
            _node = _node->_right;
            while(_node->_left){
                _node = _node->_left;
            }
        }
        else{
            Node* cur = _node;
            Node* parent = cur->_parent;
            while(parent && parent->_right == cur){
                cur = parent;
                parent = cur->_parent;
            }
            _node = parent;
        }
        return *this;
    }

    Self operator++(int){
        Self tmp(*this);
        ++ (*this);
        return tmp;
    }

    bool operator!=(const Self& s){
        return _node != s._node;
    }

    Self operator--(){
        if(_node->_left){
            _node = _node->_left;
            while(_node->_right){
                _node = _node->_right;
            }
        }
        else{
            Node* cur = _node;
            Node* parent = cur->_parent;

            while(parent && parent->_left == cur){
                cur = parent;
                parent = cur->_parent;
            }
            _node = parent;
        }
        return *this;
    }

    Self operator--(int){
        Self tmp(*this);
        ++ (*this);
        return tmp;
    }
};

template <class K>
struct SetKeyOfValue{
    const K& operator()(const K& key){
        return key;
    }
};

template <class K, class V>//pair<K,V>
struct MapKeyOfValue{
    const K& operator()(const pair<K,V>& kv){
        return kv.first;
    }
};

template<class K, class V, class KeyOfValue>
class RBTree{
    typedef RBTreeNode<V> Node;
public:
    typedef __RBTreeIterator<V, V&, V*> Iterator;
    typedef __RBTreeIterator<V, const V&, const V*> ConstIterator;

    RBTree()
        :_root(NULL)
    {}

    Iterator Begin(){
        Node* cur = _root;
        while(cur->_left){
            cur = cur->_left;
        }
        return cur;
    }

    Iterator End(){
        return NULL;
    }

    pair<Iterator, bool> Insert(const V& v){
        if(_root == NULL){
            _root = new Node(v);
            _root->_col = BLACK;
            return make_pair(Iterator(_root), true);
        }

        Node* cur = _root;
        Node* parent;
        KeyOfValue kov;
        while(cur){
            if(kov(cur->_v) < kov(v)){
                parent = cur;
                cur = cur->_right;
            }
            else if(kov(cur->_v) > kov(v)){
                parent = cur;
                cur = cur->_left;
            }
            else{
                return make_pair(Iterator(cur), false);
            }
        }

        cur = new Node(v);
        Node* ret = cur;
        if(kov(cur->_v) < kov(parent->_v)){
            parent->_left = cur;
            cur->_parent = parent;
        }
        else{
            parent->_right = cur;
            cur->_parent = parent;
        }

        while(parent && parent->_col == RED){
            Node* grandparent = parent->_parent;
            if(grandparent->_left == parent){
                Node* uncle = grandparent->_right;
                if(uncle && uncle->_col == RED){
                    parent->_col = BLACK;
                    uncle->_col = BLACK;
                    cur = grandparent;
                    parent = cur->_parent;
                }
                else{
                    if(parent->_right == cur){
                        RotateL(parent);
                        swap(parent, cur);
                    }
                    RotateR(grandparent);
                    parent->_col = BLACK;
                    grandparent->_col = RED;
                }
            }
            else{
                Node* uncle = grandparent->_left;
                if(uncle && uncle->_col == RED){
                     parent->_col = BLACK;
                    uncle->_col = BLACK;
                    cur = grandparent;
                    parent = cur->_parent;
               }
                else{
                     if(parent->_left== cur){
                        RotateR(parent);
                        swap(parent, cur);
                    }
                    RotateL(grandparent);
                    parent->_col = BLACK;
                    grandparent->_col = RED;
               }
           }
        }
        return make_pair(Iterator(ret), true);
    }

	void RotateR(Node* parent){
        Node* subL = parent->_left;
        Node* subLR = subL->_right;
        Node* ppnode = parent->_parent;

        parent->_left = subLR;
        if(subLR)
            subLR->_parent = parent;

        subL->_right = parent;
        parent->_parent = subL;
        //parent == _root
        if(ppnode){
            if(ppnode->_left == parent)
                ppnode->_left = subL;
            else
                ppnode->_right = subL;

            subL->_parent = ppnode;
        }
        else
            _root = subL;

        _root->_parent = NULL;
    }

	void RotateL(Node* parent){
        Node* subR = parent->_right;
        Node* subRL = subR->_left;
        Node* ppnode = parent->_parent;

        parent->_right = subRL;
        if(subRL)
            subRL->_parent = parent;

        parent->_parent = subR;
        subR->_left = parent;
        //parent == _root
        if(ppnode){
            if(ppnode->_left == parent)
                ppnode->_left = subR;
            else
                ppnode->_right = subR;

            subR->_parent = ppnode;
        }
        else
            _root = subR;

        _root->_parent = NULL;
    }

    Iterator Find(const K& key){
        KeyOfValue kov;
        Node* cur = _root;
        while(cur){
            if(kov(cur->_v) == key){
                return Iterator(cur);
            }
            
            if(kov(cur->_v) < key)
                cur = cur->_right;
            else
                cur = cur->_left;
        }
        return End(); 
    }

    bool IsBalance(){
        if(_root == NULL)
            return true;
        if(_root->_col == RED){
            cout << "root's color is red" << endl;
            return false;
        }

        Node* cur = _root;
        int base = 0;
        int blacknum = 0;
        while(cur){
            if(cur->_col == BLACK)
                ++ base;
            cur = cur->_left;
        }

        return _IsBalance(_root, base, blacknum);
    }

    bool _IsBalance(Node* cur, const int base, int blacknum){
        if(cur == NULL){
            if(blacknum == base)
                return true;
            else{
                cout << "wrong blacknum" << endl;
                return false;
            }
        }

        Node* parent = NULL;
        parent = cur->_parent;

        if(cur->_col == BLACK)
            ++ blacknum;
        else
            if(parent && parent->_col == RED){
                KeyOfValue kov;
                cout << "two red node:" << kov(cur->_v) << endl;
            }

        return _IsBalance(cur->_left, base, blacknum)
            && _IsBalance(cur->_right, base, blacknum);
    }

private:
    Node* _root;
};
