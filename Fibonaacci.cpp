/*
 *题目描述
大家都知道斐波那契数列，现在要求输入一个整数n，请你输出斐波那契数列的第n项。
n<=39
 */

class Solution {
public:
    int Fibonacci(int n) {
        int a = 1;
        int b = 1;
        int c = 1;
        if(n == 0)
            return 0;
        if(n <= 2)
            return c;
        while(n > 2){
            a = b;
            b = c;
            c = a + b;
            -- n;
        }
        return c;
    }
};
