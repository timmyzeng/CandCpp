/*
 *输入一个整数数组，判断该数组是不是某二叉搜索树的后序遍历的结果。
 *如果是则输出Yes,否则输出No。假设输入的数组的任意两个数字都互不相同。
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool VerifySquenceOfBST(vector<int> sequence) {
        if(sequence.empty())
            return false;
        int size = sequence.size();
        if(size == 1 || size == 2)
            return true;
        int begin = 0;
        int end = size - 1;
        return VerifySquenceOfBSTCore(sequence,begin, end);
    }

    bool VerifySquenceOfBSTCore(vector<int>& s, int begin, int end){
        int tmp = 0;
        for(int i = begin; i <= end; ++ i){
            if(i == end)
                return true;
            if(s[i] > s[end]){
                if(i == begin){
                    for(int j = i+1; j < end; ++ j){
                        if(s[j] < s[end])
                            return false;
                    }
                }
                tmp = i;
                break;
            }
        }
        return VerifySquenceOfBSTCore(s, begin, tmp-1)
            && VerifySquenceOfBSTCore(s, tmp, end-1);
    }
};
