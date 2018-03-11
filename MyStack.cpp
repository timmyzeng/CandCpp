/*************************************************************************
	> File Name: MyStack.cpp
	> Author: Timmy
	> Created Time: 2018年03月07日 星期三 00时14分20秒
 ************************************************************************/

#include <iostream>

using namespace std;

template <class T>
class MyStack{
public:
	//constructor
	MyStack()
		:_array(NULL)
		,_size(0)
		,_capacity(0)
	{}
	//destructor
	~MyStack(){
		if(_array){
			delete[] _array;
			_array = NULL;
		}
		_size = _capacity = 0;
	}
	//Push
	void Push(const T& x){
		_CheckCapacity();
		_array[_size] = x;
		++ _size;
	}
	void _CheckCapacity(){
		if(_size == _capacity){
			_capacity = _capacity > 0 ? _capacity*2 : 1;
			T* tmp = new T[_capacity];
			for(int i = 0; i < _size; ++i){
				tmp[i] = _array[i];
			}
			delete[] _array;
			_array = tmp;
		}
	}
	//Empty
	bool Empty(){
		return _size == 0;
	}
	//Size
	size_t Size(){
		if(!Empty()){
			return _size;
		}
		else
			cout << "empty" << endl;
	}
	//Top
	const T& Top(){
		if(!Empty()){
			return _array[_size - 1];
		}
		else
			cout << "empty" << endl;
	}
	//Pop
	void Pop(){
		if(!Empty()){
			-- _size;
		}
		else
			cout << "empty" << endl;
	}
protected:
	T* _array;
	size_t _size;
	size_t _capacity;
};

int main(){
	system("clear");

	MyStack<int> s;
	s.Push(1);
	s.Push(2);
	s.Push(3);
	s.Push(4);
	cout << "Size" << endl;
	cout << s.Size() << endl;
	cout << "Top" << endl;
	cout << s.Top() << endl;
	s.Pop();
	s.Pop();
	s.Pop();
	cout << "Empty" << endl;
	cout << s.Empty() << endl;
	s.Pop();
	cout << "Empty" << endl;
	cout << s.Empty() << endl;

	return 0;
}
