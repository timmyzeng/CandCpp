/*
 *
题目描述
一只青蛙一次可以跳上1级台阶，也可以跳上2级。求该青蛙跳上一个n级的台阶总共有多少种跳法。
 */

class Solution {
public:
    int jumpFloor(int number) {
        int a = 0;
        int b = 1;
        int c = 1;
        if(number == 0)
            return 0;
        if(number == 1)
            return b;
        while(number > 1){
            a = b;
            b = c;
            c = a + b;
            -- number;
        }
        return c;
    }
};
