/*
输入一个正整数n,求n!(即阶乘)末尾有多少个0？ 比如: n = 10; n! = 3628800,所以答案为2 

输入描述:
输入为一行，n(1 ≤ n ≤ 1000)
输出描述:
输出一个整数,即题目所求

示例1
输入
10

输出
2
*/

#include <iostream>

using namespace std;

int main(){
    int n = 0;
    while(cin >> n){
        int count = 0;
        int tmp = 0;
        for(int i = 5; i <= n; i+=5){
            tmp = i;
            while(tmp % 5 == 0){
                count ++;
                tmp /= 5;
            }
        }
        cout << count << endl;
    }
    return 0;
}
