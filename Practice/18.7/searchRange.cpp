/*
 Given a sorted array of integers, find the starting and ending position of a given A[target] value.

Your algorithm's runtime complexity must be in the order of O(log n).

If the A[target] is not found in the array, return[-1, -1].

For example,
Given[5, 7, 7, 8, 8, 10]and A[target] value 8,
return[3, 4].
 */

#include <cstdlib>
#include <vector>

using namespace std;

//class Solution {
//public:
    //vector<int> searchRange(int A[], int n, int target) {
        //auto pos1 =std::lower_bound(A, A+n, target);
        //auto pos2 =std::upper_bound(A, A+n, target);
        //if(*pos1 != target)
            //return {-1,-1};
        //return {int(pos1-A), int(pos2-A-1)};
    //}
//};

class Solution {
public:
    vector<int> searchRange(int A[], int n, int target) {
        vector<int> result;
        int front = 0;
        int tail = n-1;
        int middle = 0;
        int start = -1;
        int end = -1;
        while(front <= tail){
            middle = front + (tail-front)/2;
            if(A[middle] == target){
                start = middle;
                end = middle;
                while(start >= 0 && A[start] == target){
                    start --;
                }
                while(end <= n-1 && A[end] == target){
                    end ++;
                }
                start ++;
                end --;
                break;
            }
            else if(A[middle] < target){
                front = middle + 1;
            }
            else{
                tail = middle - 1;
            }
        }
        result.push_back(start);
        result.push_back(end);
        return result;
    }
};
