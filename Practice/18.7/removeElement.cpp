/*
Given an array and a value, remove all instances of that value in place and return the new length.
The order of elements can be changed. It doesn't matter what you leave beyond the new length.
*/

#include <iostream>

using namespace std;

class Solution {
public:
    int removeElement(int A[], int n, int elem) {
        int index = 0;
        for(int i = 0; i < n; ++ i){
            A[index] = A[i];
            if(A[i] != elem){
                ++ index;
            }
        }
        return index;
    }
};

/*
class Solution {
public:
    int removeElement(int A[], int n, int elem) {
        for(int i = 0; i < n; ++i){
            if(A[i] == elem){
                while(i < n && A[--n] == elem)
                    ;
                A[i] = A[n];
            }
        }
        return n;
    }
};
*/
