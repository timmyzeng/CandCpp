#pragma once

#include <iostream>

using namespace std;

#include "RBTree.h"

template <class K, class V>
class MyMap{
public:
    typedef typename RBTree<K, pair<K, V> ,MapKeyOfValue<K, V> >::Iterator Iterator;

    pair<Iterator, bool> Insert(const pair<K, V>& kv){
        return _rbtree.Insert(kv);
    }

    V& operator[](const K& key){
        pair<Iterator, bool> tmp = _rbtree.Insert(make_pair(key, V()));
        return (tmp.first)->second; 
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
    RBTree<K, pair<K, V> ,MapKeyOfValue<K, V> > _rbtree;
};

void TestMyMap(){
    MyMap<string, string> dict;
    dict.Insert(make_pair("map", "地图"));
    dict.Insert(make_pair("set", "集合"));
    dict.Insert(make_pair("string", "字符串"));
    dict.Insert(make_pair("int", "整型"));
    dict.Insert(make_pair("map", "影射"));

    dict["map"] = "影射";
    dict["long"] = "长整型";

    MyMap<string, string>::Iterator it = dict.Begin();
    while(it != dict.End()){
        cout << it->first << ":" << it->second << endl;
        ++ it;
    }
}
