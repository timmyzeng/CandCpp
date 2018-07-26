/*

读入一个字符串str，输出字符串str中的连续最长的数字串 

输入描述:
每个测试输入包含1个测试用例，一个字符串str，长度不超过255。

输出描述:
在一行内输出str中里连续最长的数字串。

输入
abcd12345ed125ss123456789
输出
123456789

*/

#include <iostream>
#include <cctype>
#include <string>

using namespace std;

void StringLength(string& str){
    int front = 0;
    int num = 0;
    string result;
    while(front < str.size()){
        if(isalpha(str[front])){
            ++ front;
        }
        else{
            num = front;
            string tmp;
            while(num < str.size() && isdigit(str[num])){
                tmp += str[num];
                ++ num;
            }
            if(result.size() <= tmp.size()){
                result = tmp;
            }
            front = num;
        }
    }
    cout << result << endl;
}

int main(){
    string str;
    while(cin >> str){
        StringLength(str);
    }
    return 0;
}
