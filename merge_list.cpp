/*************************************************************************
	> File Name: 1.15.cpp
	> Author: Timmy
	> Created Time: Thu 18 Jan 2018 12:12:19 PM CST
 ************************************************************************/

// #include <iostream>

// using namespace std;

// class Solution{
// 	public:
// 		int Sum_Solution( int n ){
// 			bool a[n][n+1];
// 			return sizeof(a)>>1;
// 		}
// };

// int main(){
// 	Solution s;
// 	cout << s.Sum_Solution(10) << endl;
// 	return 0;
// }

//A 求1+2+3+...+n，要求不能使用乘除法，for,while，if,else,switch,case等关键字以及条件判断语句
//1构造函数+静态成员
//class tmp{
	//public:
		//tmp( ){
			//++n;
			//sum += n;
		//}

		//void static init(){
			//n = 0;
			//sum = 0;
		//}
		//int static getsum(){
			//return sum;
		//}
	//private:
		//static int n;
		//static int sum;
//};

//int tmp::n = 0;
//int tmp::sum = 0;

//int count(int n){
	//tmp::init();
	//tmp* a = new tmp[n];
	//delete[] a;
	//a = NULL;
	//tmp::getsum();
//}

//int main(){
	//cout << count(100) << endl;
	//return 0;
//}
//
//
//
//2虚函数
//#include <iostream>  
//using namespace std;  
  
//class A;  
//A* Array[2];  
  
//class A  
//{  
//public:  
	//virtual int Sum(int n)  
	//{  
		//return 0;  
	//}  
//};  
  
//class B:public A  
//{  
//public:  
	//virtual int Sum(int n)  
	//{  
		//return Array[!!n]->Sum(n-1)+n;  
	//}  
//};  
  
//int solution2_Sum(int n)  
//{  
	//A a;  
	//B b;  
	//Array[0]=&a;  
	//Array[1]=&b;  
  
	//int value=Array[1]->Sum(n);  
  
	//return value;  
//}  
  
//int main()  
//{  
	//cout<<solution2_Sum(100)<<endl;  
	//return 0;  
//}  
//

//3 利用&&前为假，不再计算后面式子的性质作为递归的结束
//同理||
//int sum( int n ){
	//int result = n;
	//result && (result += sum(n-1));
	//return result;
//}
//int main(){
	//cout << sum(100) << endl;
	//return 0;
//}
//
//不是很懂啊
//4 利用异常处理，完成递归的条件判断
//public int sum(int n)
//{
  //try
  //{
	  //int[] array = new int[n-2];
	  //return n+sum(n-1);
  //}
  //catch(Exception e)
  //{
	  //return 1;
  //}
//}
//
//5 利用模板
//#include <iostream>
//using namespace std;
//
//template <unsigned N>
//class Sum{
	//public:
		//enum{
			//sum = N+Sum<N-1>::sum
		//};
//};

//template<>
//class Sum<1>{
	//public:
		//enum{
			//sum = 1
		//};
//};

//int main(){
	//cout << Sum<100>::sum << endl;
	//return 0;
//}

/*B 合并两个有序链表，合并之后的链表依然是有序的*/
//#define DateType int
//struct Node{
	//Node(){
		//_val = 0;
		//_next = NULL;
	//}

	//Node( DateType val ){
		//_val = val;
		//_next = NULL;
	//}

	//Node* _next;
	//DateType _val;
//}; 

//void print( Node* node ){
	//while( node != NULL ){
		//cout << node->_val << "->";
		//node = node->_next;
	//}
	//cout << "NULL" << endl;
//}

//Node* mymerge( Node* l1, Node* l2 ){
	//if( l1 == NULL )
		//return l2;
	//if( l2 == NULL )
		//return l1;

	//Node* large = l1;
	//Node* small = l2;

	//if( l1-> _val < l2-> _val ){
		//large = l2;
		//small = l1;
	//}

	//Node* head= new Node(small->_val);
	//Node* cur = head;
	//small = small->_next;

	//Node* tmp = NULL;
	//while( large != NULL && small != NULL ){
		//if( large->_val > small->_val ){
			//tmp = new Node(small->_val);
			//small = small->_next;
		//}
		//else{
			//tmp = new Node(large->_val);
			//large = large->_next;
		//}

		//cur->_next = tmp;
		//cur = cur->_next;
	//}
	
	//if( large )
		//cur->_next = large;
	//else if( small )
		//cur->_next = small;

	//return head;
//}

//int main(){
	//Node* n1 = new Node(3);
	////Node* n2 = new Node(3);
	////Node* n3 = new Node(4);
	////Node* n4 = new Node(6);
	////Node* n5 = new Node(7);

	////n1->_next = n2;
	////n2->_next = n3;
	////n3->_next = n4;
	////n4->_next = n5;
	////n5->_next = NULL;
	
	//Node* n6 = new Node(2);
	////Node* n7 = new Node(2);
	////Node* n8 = new Node(5);
	////Node* n9 = new Node(7);
	////Node* n10 = new Node(9);
	////Node* n11 = new Node(12);

	////n6->_next = n7;
	////n7->_next = n8;
	////n8->_next = n9;
	////n9->_next = n10;
	////n10->_next = n11;
	////n11->_next = NULL;

	//print( n1 );
	//print( n6 );
	//print( mymerge( n1, n6 ) );
	
	//return 0;
//}
//
//调用list merge
//int main(){
	//list<DateType> list1;
	//list<DateType> list2;
	//list<DateType> :: iterator it;
	
	//for( int i = 0; i < 10; i += 2 ){
		//list1.push_back(i);
		//list2.push_back(i+1);
	//}

	//for( it = list1.begin(); it != list1.end(); ++it ){
		//cout << *it << " ";
	//}
	//cout << endl;

	//for( it = list2.begin(); it != list2.end(); ++it ){
		//cout << *it << " ";
	//}
	//cout << endl;

	//list1.merge(list2);
	
	//for( it = list1.begin(); it != list1.end(); ++it ){
		//cout << *it << " ";
	//}
	//cout << endl;

	//return 0;
//}
