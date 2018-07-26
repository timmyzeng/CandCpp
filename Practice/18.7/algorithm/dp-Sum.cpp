/*
题目描述
输入两个整数 n 和 m，从数列1，2，3.......n 中随意取几个数,使其和等于 m ,要求将其中所有的可能组合列出来
输入描述:
每个测试输入包含2个整数,n和m
输出描述:
按每个组合的字典序排列输出,每行输出一种组合

输入
5 5
输出
1 4
2 3
5
*/

#include <iostream>
#include <vector>

using namespace std;

//递归
//n是最大值下标
//m是剩余的值
//v用来保存选中的值
//index指的是的当前指向的值
void Bag(int n, int m, vector<int>& v, int index){
    if(m == 0){
        for(int i = 0; i < v.size(); ++ i){
            i == 0 ? cout << v[i] : cout << " " << v[i];
        }
        cout << endl;
    }
    for(int i = index; i <= n && i <= m; ++ i){
        v.push_back(i);
        Bag(n, m-i, v, i+1);
        v.pop_back();
    }
}

int main(){
    int n = 0;
    int m = 0;
    while(cin >> n >> m){
        vector<int> v;
        Bag(n, m, v, 1);
    }
    return 0;
}



