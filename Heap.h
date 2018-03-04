/*************************************************************************
	> File Name: Heap.h
	> Author: Timmy
	> Created Time: 2018年03月04日 星期日 12时27分48秒
 ************************************************************************/

#pragma once

template <class T, class Compare>
class Heap{
public:
	//constructor
	//这个空的构造函数，会在初始化列表调用vector的构造函数
	//不需要模拟析构和拷贝构造，因为缺省的已经够用了
	Heap()
	{}
	Heap(T* a, size_t n){
		//reserve
		_array.reserve(n);
		for(size_t i = 0; i < n; ++i){
			_array.push_back(a[i]);
		}
		//CreatHeap
		//我……size_t不能乱用……否则死循环出不去……
		for(int i = (_array.size()-2)/2; i >= 0; --i){
			AdjustDwon(i);
		}
	}
	void Push(const T& x){
		_array.push_back(x);
		AdjustUp(_array.size() - 1);
	}
	//Pop堆顶的数据
	//先将堆顶和最后一个元素交换，再向下调整
	void Pop(){
		swap(_array[0], _array[_array.size() - 1]);
		_array.pop_back();
		AdjustDwon(0);
	}
	bool Empty(){
		return _array.empty();
	}
	size_t size(){
		return _array.size();
	}
	const T& Top(){
		return _array[0];
	}
protected:
	//前提，左右子树已经是大堆
	void AdjustDwon(size_t root){
		Compare com;
		int parent = root;
		int child = parent*2 + 1;
		//结束条件
		//1、孩子小于父亲
		//2、没有孩子节点了
		while(child < _array.size()){
			//利用完全二叉树，以数组为存储模式
			//select bigger child
			if(child+1 < _array.size() 
			  && com(_array[child+1], _array[child])){
				++ child;
			}
			if(com(_array[child], _array[parent])){
				swap(_array[child], _array[parent]);
				parent = child;
				child = parent*2 + 1;
			}
			else{
				break;
			}
		}
	}

	void AdjustUp(size_t child){
		Compare com;
		int parent = (child - 1)/2;
		while(child > 0){
			if(com(_array[child], _array[parent])){
				swap(_array[child], _array[parent]);
				child = parent;
				parent = (child - 1)/2;
			}
			else{
				break;
			}
		}
	}

	vector<T> _array;
};

template <class T>
struct Less{
	bool operator()(const T& left, const T& right){
		return left < right;
	}
};

template <class T>
struct Greater{
	bool operator()(const T& left, const T& right){
		return left > right;
	}
};

void TestHeap(){
	int a[] = {10,11, 13, 12, 16, 18, 15, 17, 14, 19};
	Heap<int, Greater<int>> H1;
	Heap<int, Greater<int>> H2(a, sizeof(a)/sizeof(a[0]));
	H2.Push(12);
	H2.Push(20);
	H2.Push(18);
}
