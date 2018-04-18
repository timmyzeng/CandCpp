/*
 * 题目描述
在一个二维数组中，每一行都按照从左到右递增的顺序排序，
每一列都按照从上到下递增的顺序排序。请完成一个函数，
输入这样的一个二维数组和一个整数，判断数组中是否含有该整数。
*/

#include <vector>
using namespace std;

class Solution {
public:
    bool Find(int target, vector<vector<int> > array) {
        int size = array.size();
        if(size != 0){ 
            int row = size - 1;
            int col = 0;
            while(row >= 0 && col < array[0].size()){
                if(array[row][col] == target){
                    return true;
                }
                else if(array[row][col] < target){
                    ++ col;
                }
                else {
                    -- row;
                }
            }
        }
        return false;
    }
};
