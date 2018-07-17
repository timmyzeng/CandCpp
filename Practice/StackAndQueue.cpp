#include <iostream>
#include <stack>
#include <queue>
#include <assert.h>

using namespace std;

//（1）实现一个栈，要求实现Push（出栈）、Pop（入栈）、Min（返回最小值的操作）的时间复杂度为O(1) 
class MinStack{
public:
    void Push(int x){
        s.push(x);
        if(m.empty() || x <= m.top())
            m.push(x);
    }

    void Pop(){
        int tmp = s.top();
        s.pop();
        if(tmp == m.top())
            m.pop();
    }

    int Min(){
        assert(m.size());
        return m.top();
    }

private:
    stack<int> s;
    stack<int> m;
};
//（2）使用两个栈实现一个队列 
class TwoStackToQueue{
public:
    void Push(int x){
        input.push(x);
    }

    void Pop(){
        if(!output.empty()){
            output.pop();
        }
        else if(!input.empty()){
            while(!input.empty()){
                output.push(input.top());
                input.pop();
            }
            output.pop();
        }
        else
            return;
    }

    int Front(){
        if(output.empty() && !input.empty()){
            while(!input.empty()){
                output.push(input.top());
                input.pop();
            }
        }
        return output.top();
    }
private:
    stack<int> input;
    stack<int> output;
};
//（3）使用两个队列实现一个栈 
class TowQueueTOStack{
public:
    void Push(int x){

    }

    void Pop(){
    }

    int Top(){
    }

private:
    queue<int> q1;
    queue<int> q2;
};
//（4）判断元素出栈、入栈顺序的合法性。如：入栈的序列（1,2,3,4,5），出栈序列为（4,5,3,2,1）是合法序列，
//入栈的序列（1,2,3,4,5），出栈序列为（1,5,3,2,4）是不合法序列 
//（5）一个数组实现两个栈

void Test(){
    //1
    //MinStack Min;
    //Min.Push(1);
    //Min.Push(2);
    //Min.Push(1);
    //Min.Push(0);
    //Min.Push(2);
    //Min.Push(4);
    //Min.Pop();
    //Min.Pop();
    //Min.Pop();
    //Min.Pop();
    //Min.Pop();
    //cout << Min.Min() << endl;

    //2
    TwoStackToQueue ts;
    ts.Push(2);
    ts.Push(3);
    ts.Push(4);
    ts.Push(5);

    cout << ts.Front()  << endl;
}
int main(){
    Test();
    return 0;
}
