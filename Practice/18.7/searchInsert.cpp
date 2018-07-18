/*
Given a sorted array and a target value, 
return the index if the target is found.
If not, return the index where it would be if it were inserted in order.

You may assume no duplicates in the array.

Here are few examples.
[1,3,5,6], 5 → 2
[1,3,5,6], 2 → 1
[1,3,5,6], 7 → 4
[1,3,5,6], 0 → 0
*/

#include <iostream>

using namespace std;

class Solution {
public:
    //二分查找
    int searchInsert(int A[], int n, int target) {
        if(A == NULL || n <= 0)
            return 0;
        int start = 0;
        int end = n-1;
        while(start <= end){
            int mid = start + (end-start)/2;
            if(A[mid] > target){
                end = mid - 1;
            }
            else if(A[mid] < target){
                start = mid + 1;
            }
            else{
                return mid;
            }
        }
        //没有找到，就是start的地方进行插入
        return start;
    }
};
