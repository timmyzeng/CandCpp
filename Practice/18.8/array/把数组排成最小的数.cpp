//输入一个正整数数组，把数组里所有数字拼接起来排成一个数，打印能拼接出的所有数字中最小的一个。
//例如输入数组{3，32，321}，则打印出这三个数字能排成的最小数字为321323。

#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

// 这种方法通过to_string函数，将int类型转变为string类型
// a = 3; b = 14
// A = 314; B = 143; A > B
// 所以排序的时候，a应该在b后面。
class Solution {
    static bool cmp(int a, int b){
        string A = to_string(a);
        A += to_string(b);
        string B = to_string(b);
        B += to_string(a);
        return A < B;
    }
public:
    string PrintMinNumber(vector<int> numbers) {
        string result;
        if(numbers.empty())
            return result;
        sort(numbers.begin(), numbers.end(), cmp);
        for(int i = 0; i < numbers.size(); ++ i){
            result += to_string(numbers[i]);
        }
        return result;
    }
};
 
