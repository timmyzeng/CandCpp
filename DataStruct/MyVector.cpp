/*************************************************************************
	> File Name: MyVector_list.cpp
	> Author: Timmy
	> Created Time: 2018年03月01日 星期四 11时05分28秒
 ************************************************************************/

#include <iostream>
#include <assert.h>
#include <cstring>

using namespace std;

//type_trait
struct __TrueType{};
struct __FalseType{};

template <class T>
struct __type_trait{
	typedef __FalseType IsPODType;
};
template <>
struct __type_trait<int>{
	typedef __TrueType IsPODType;
};

template <class T>
T* __type_copy(T* des, const T* sour, size_t size, __TrueType){
	return (T*)memcpy(des, sour, size*sizeof(T));
};

template <class T>
T* __type_copy(T* des, const T* sour, size_t size, __FalseType){
	for( int i = 0; i < size; ++i){
		des[i] = sour[i];
	}
	return des;
};

template <class T>
T* type_copy(T* des, T* sour, size_t size){
	return __type_copy(des, sour, size,typename __type_trait<T>::IsPODType());
};

//MyVector
template <class T>
class  MyVector{
public:
	typedef T* Pointer;
	typedef T& Reference;

	typedef T* Iterator;
	typedef const T* ConstIterator;

	//Member functions
	//constructor
	MyVector(){
		_start = NULL;
		_finish = NULL;
		_end_of_storage = NULL;
	}
	MyVector(size_t n, const T& val = T()){
		_start = new T[n];
		for(int i = 0; i<n; ++i){
			_start[i] = val;
		}
		_finish = _start + n;
		_end_of_storage = _finish;
	}
	MyVector(const MyVector<T>& v){
		size_t size = v.Size();
		_start = new T[size];
		type_copy<T>(_start, v._start, size);
		_finish = _start + size;
		_end_of_storage = _finish;
	}
	//destructor
	~MyVector(){
		if(_start){
			delete[] _start;
			_start = NULL;
			_finish = NULL;
			_end_of_storage = NULL;
		}
	}

	//Iterators
	//Begin
	Iterator Begin(){
		return _start;
	}

	//End
	Iterator End(){
		return _finish;
	}

	//Capacity
	//Size
	size_t Size()const{
		return _finish - _start;
	}
	//Capacity
	size_t Capacity()const{
		return _end_of_storage - _start;
	}
	//Empty
	bool Empty(){
		return _start == _finish;
	}
	//Resize
	void Resize(size_t n, const T& val = T()){
		//1、n > capacity
		Reserve(n);
		//2、n < size
		if(n < Size()){
			_finish = _start + n;
		}
		//3、n > size && n < capacity
		else{
			while(_finish != (_start + n)){
				*_finish = val;
				_finish++;
			}
		}
	}
	//Reserve
	void Reserve(size_t n){
		size_t size = Size();
		size_t capacity = Capacity();
		if(n > capacity){
			T* tmp = new T[n];
			if(_start){
				type_copy<T>(tmp, _start, size);
			}
			delete[] _start;
			_start = tmp;
			_finish = _start + size;
			_end_of_storage = _start + n;
		}
	}

	//Element accsee
	//Front
	Reference Front(){
		return *Begin();
	}
	//Back
	Reference Back(){
		return *(End() - 1);
	}
	//[]
	Reference operator[](size_t index){
		return *(Begin() + index);
	}

	//Modifiers
	//PushBack
	void PushBack(const T& x){
		Insert(End(), x);
	}
	//PopBack
	void PopBack(){
		assert(Size() > 0);
		Erase(End());
	}
	//Insert
	void Insert(Iterator pos, const T& val){
		int offset = pos - _start;
		if(_finish == _end_of_storage){
			size_t newcapacity = Capacity() > 0 ? Capacity()*2 : 1;
			Reserve(newcapacity);
			pos = _start + offset;
		}
		assert(pos <= _finish && pos >= _start);
		Iterator end = End() - 1;
		while(end >= pos){
			*(end + 1) = *end;
			--end;
		}
		*pos = val;
		++ _finish;
	}
	//Erase
	void Erase(Iterator pos){
		assert(pos <= _finish && pos >= _start);
		while(pos < _finish){
			*pos = *(pos + 1);
			pos = pos + 1;
		}
		-- _finish;
	}
	//Clear
	void Clear(){
		_finish = _start;
	}
	
private:
	//member
	Iterator _start;
	Iterator _finish;
	Iterator _end_of_storage;
};

int main(){
	system("clear");
	MyVector<int> v;
	//MyVector<int> v(4, 1);

	v.PushBack(1);
	v.PushBack(2);
	v.PushBack(3);
	v.PushBack(4);
	v.PushBack(5);
	
	MyVector<int> v_copy(v);
	//v.resize(7, 10);
	//v.reserve(10);
	//v.resize(3, 12);

	for(size_t i = 0; i < v.Size(); ++i){
		cout << v[i] << " ";
	}
	cout << endl;

	for(size_t i = 0; i < v.Size(); ++i){
		cout << v_copy[i] << " ";
	}
	cout << endl;

	cout << v.Size() << endl;
	cout << v.Capacity() << endl;
	v.PopBack();
	v.PopBack();
	v.PopBack();
	for(size_t i = 0; i < v.Size(); ++i){
		cout << v[i] << " ";
	}
	cout << endl;
	cout << v.Size() << endl;
	cout << v.Capacity() << endl;
	cout << v.Empty() << endl;
	v.Clear();
	cout << v.Empty() << endl;

	return 0;
}
