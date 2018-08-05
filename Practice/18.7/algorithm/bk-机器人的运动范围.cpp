/*
地上有一个m行和n列的方格。一个机器人从坐标0,0的格子开始移动，每一次只能向左，右，上，下四个方向移动一格，
但是不能进入行坐标和列坐标的数位之和大于k的格子。 例如，当k为18时，机器人能够进入方格（35,37），因为3+5+3+7 = 18。
但是，它不能进入方格（35,38），因为3+5+3+8 = 19。请问该机器人能够达到多少个格子？

回溯
*/

class Solution {
public:
    int helper(int hold, int Rows, int Cols, int row, int col, bool*& flag){
        if(row >= 0 && row < Rows && col >= 0 && col < Cols){
            int tmp = row;
            int sum = 0;
            while(tmp){
                sum += tmp % 10;
                tmp /= 10;
            }
            tmp = col;
            while(tmp){
                sum += tmp % 10;
                tmp /= 10;
            }
            if(sum <= hold && flag[row*Cols+col] == false){
                flag[row*Cols+col] = true;
                return helper(hold, Rows, Cols, row, col+1, flag)
                       + helper(hold, Rows, Cols, row, col-1, flag)
                       + helper(hold, Rows, Cols, row+1, col, flag)
                       + helper(hold, Rows, Cols, row-1, col, flag)
                       + 1;
            }
        }
        return 0;
    }
    
    int movingCount(int threshold, int rows, int cols)
    {
        bool* flag = new bool[rows*cols];
        for(int i = 0; i < rows*cols; ++ i){
            flag[i] = false;
        }
        return helper(threshold, rows, cols, 0, 0, flag);
        delete[] flag;
    }
};


