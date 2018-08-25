//数组中有一个数字出现的次数超过数组长度的一半，请找出这个数字。
//例如输入一个长度为9的数组{1,2,3,2,2,2,5,4,2}。由于数字2在数组中出现了5次，
//超过数组长度的一半，因此输出2。如果不存在则输出0。

#include <iostream>
#include <vector>

using namespace std;



// 时间复杂度nO(n),利用了快排，如果存在这样一个num，肯定在中间
// 如果不存在，通过for循环验证就可以得到
//
/*class Solution {
public:
    int MoreThanHalfNum_Solution(vector<int> numbers) {
        if(numbers.empty())
            return 0;
        if(numbers.size() == 1)
            return numbers[0];
        
        sort(numbers.begin(), numbers.end());
        int half = numbers[numbers.size()/2];
        int counter = 0;
        
        for(int i = 0; i < numbers.size(); ++ i){
            if(half == numbers[i]){
                counter ++;
            }
        }
        
        return counter > (numbers.size()/2) ? half : 0;
    }
};
*/

// O(n)时间复杂度，先通过比较，如果存在大于一半长度的数字，那么第一个for循环下的
// num肯定是它，如果不存在，这就需要通过第二个for循环进行验证了。
class Solution {
public:
    int MoreThanHalfNum_Solution(vector<int> numbers) {
        if(numbers.empty())
            return 0;
        int num = numbers[0];
        int counter = 1;
        for(int i = 1; i < numbers.size(); ++ i){
            if(num == numbers[i])
                counter ++;
            else
                counter --;
            if(counter == 0){
                num = numbers[i];
                counter = 1;
            }
        }
        
        counter = 0;
        for(int i = 0; i < numbers.size(); ++ i){
            if(num == numbers[i])
                counter ++;
        }
        
        return counter > (numbers.size()/2) ? num : 0;
    }
};
