/*
对于一个有正有负的整数数组，请找出总和最大的连续数列。
给定一个int数组A和数组大小n，请返回最大的连续数列的和。保证n的大小小于等于3000。

测试样例：
[1,2,3,-6,1]

返回：6
*/

#include <iostream>
#include <vector>

using namespace std;

class MaxSum {
public:
    int getMaxSum(vector<int> A, int n) {
        if(n <= 0)
            return -1;
        int tmp = A[0];
        int max = A[0];
        for(int i = 1; i < n; ++ i){
            if(tmp + A[i] > A[i]){
                tmp += A[i];
            }
            else{
                tmp = A[i];
            }
            if(max < tmp){
                max = tmp;
            }
        }
        return max;
    }
};
