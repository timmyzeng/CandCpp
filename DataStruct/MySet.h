#pragma once
#include <iostream>

using namespace std;

#include "RBTree.h"

template<class K>
class MySet{
public:
    typedef typename RBTree<K, K, SetKeyOfValue<K> >::Iterator Iterator;

    pair<Iterator, bool> Insert(const K& key){
        return _rbtree.Insert(key);
    }

    Iterator Find(const K& key){
        return _rbtree.Find(key);
    }

    Iterator Begin(){
        return _rbtree.Begin();
    }

    Iterator End(){
        return _rbtree.End();
    }

private:
    RBTree<K, K, SetKeyOfValue<K> > _rbtree;
};

void TestMySet(){
    MySet<string> myset;
    myset.Insert("string");
    myset.Insert("int");
    myset.Insert("long");
    myset.Insert("string");

    MySet<string>::Iterator it = myset.Begin();
    while(it != myset.End()){
        cout << *it << endl;
        ++ it;
    }
}
