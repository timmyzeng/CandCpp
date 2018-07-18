/*
Given two numbers represented as strings, return multiplication of the numbers as a string.
Note: The numbers can be arbitrarily large and are non-negative.
*/
#include <iostream>
#include <string>

using namespace std;
//手工模拟乘法的实现。

class Solution {
public:
    string multiply(string num1, string num2) {
        int size1 = num1.size();
        int size2 = num2.size();
        int carry = 0;
        string result(size1+size2, '0');

        for(int i = size1-1; i >= 0; -- i){
            int a = num1[i] - '0';
            for(int j = size2-1; j >= 0; -- j){
                int b = num2[j] - '0';
                int c = result[i+j+1] - '0';
                int tmp = c+carry+a*b;
                result[i+j+1] = tmp%10 + '0';
                carry = tmp/10;
            }
            if(carry){
                result[i] += carry;
                carry = 0;
            }
        }
        int i = 0;
        while(i < size1+size2 && result[i] == '0'){
            ++ i;
        }
        return (i == result.size()) ? "0" : result.substr(i);
    }
};
