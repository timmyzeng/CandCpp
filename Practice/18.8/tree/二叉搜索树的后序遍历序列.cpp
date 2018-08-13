/*
输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。
如果是则输出Yes,否则输出No。假设输入的数组的任意两个数字都互不相同。 
*/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool help(vector<int>& arr, int left, int right){
        if(left >= right)
            return true;
        int i = 0;
        int j = 0;
        for(i = left; i < right; ++ i){
            if(arr[i] > arr[right]){
                break;
            }
        }
        for(j = i; j < right; ++ j){
            if(arr[j] < arr[right]){
                return false;
            }
        }
        return help(arr, 0, i-1) && help(arr, i, right-1);
    }
    bool VerifySquenceOfBST(vector<int> sequence) {
        if(sequence.empty()){
            return false;
        }
        if(sequence.size() == 1 || sequence.size() == 2){
            return true;
        }
        return help(sequence, 0, sequence.size()-1);
    }
};
