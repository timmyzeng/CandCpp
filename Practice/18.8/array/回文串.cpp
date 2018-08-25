//给定一个字符串，问是否能通过添加一个字母将其变为回文串。

//输入描述:
//一行一个由小写字母构成的字符串，字符串长度小于等于10。
//输出描述:
//输出答案(YES\NO).

//示例1
//输入
//coco
//输出
//YES

// 考虑回文串的性质，如果一定要实现添加就可以的话
// 肯定是多出了一个或者没有多出一个。
// 同时如果相同的一定是对称的。
#include <iostream>

using namespace std;

int main(){
    string str;
    while(cin >> str){
        bool first = false;
        int left = 0;
        int right = str.size()-1;
        while(left <= right){
            if(str[left] == str[right]){
                left ++;
                right --;
            }
            else{
                if(first){
                    break;
                }
                if(str[left] == str[right-1]){
                    right --;
                }
                else{
                    left ++;
                }
                first = true;
            }
        }
        if(left > right){
            cout << "YES" << endl;
        }
        else{
            cout << "NO" << endl;
        }
        str.clear();
    }
    return 0;
}
