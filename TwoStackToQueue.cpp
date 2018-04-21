/*
 *题目描述
用两个栈来实现一个队列，完成队列的Push和Pop操作。 队列中的元素为int类型。
 */

#include <vector>
using namespace std;
class Solution
{
public:
    int cou = 0;
    void push(int node) {
        stack1.push_back(node);
        stack2.push_back(cou++);
    }
 
    int pop() {
        int i = 0;
        while(stack2[i] == -1)
            {
            i++;
        }
        stack2[i] = -1;
        return stack1[i];
    }
 
private:
    vector<int> stack1;//存数
    vector<int> stack2;//地址
};
