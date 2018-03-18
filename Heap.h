#pragma once

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

template <class T, class Compare>
class Heap{
public:
	//constructor
	Heap()
	{}
	Heap(T* a, size_t n){
		//reserve
		_array.reserve(n);
		for(size_t i = 0; i < n; ++i){
			_array.push_back(a[i]);
		}

		for(int i = (_array.size()-2)/2; i >= 0; --i){
			AdjustDwon(i);
		}
	}
	void Push(const T& x){
		_array.push_back(x);
		AdjustUp(_array.size() - 1);
	}

	void Pop(){
		swap(_array[0], _array[_array.size() - 1]);
		_array.pop_back();
		AdjustDwon(0);
	}
	bool Empty(){
		return _array.empty();
	}
	size_t Size(){
		return _array.size();
	}
	const T& Top(){
		return _array[0];
	}
	//Print for Test
	void Print(){
		if(!_array.empty()){
			for(int i = 0; i < _array.size(); ++i){
				cout << _array[i] << " ";
			}
		}
	}
	
protected:
	vector<T> _array;

	void AdjustDwon(size_t root){
		Compare com;
		int parent = root;
		int child = parent*2 + 1;
		while(child < _array.size()){
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

};


void TestHeap(){
	int a[] = {10,11, 13, 12, 16, 18, 15, 17, 14, 19};
	Heap<int, Greater<int>> H1;
	Heap<int, Greater<int>> H2(a, sizeof(a)/sizeof(a[0]));
	H2.Push(12);
	H2.Push(20);
	H2.Push(18);
	H2.Print();
}
