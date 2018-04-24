#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Solution {
public:
    vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        vector<int> result;
        size_t size = input.size();
        if(size == 0 || static_cast<int>(size) < k)
            return result;

        priority_queue<int, vector<int>, less<int> > pq;

        for(size_t i = 0; i < static_cast<size_t>(k); ++ i){
            pq.push(input[i]);
        }
        for(size_t i = static_cast<size_t>(k); i < size; ++ i){
            if(input[i] < pq.top()){
                pq.pop();
                pq.push(input[i]);
            }
        }

        for(int i = 0; i < k; ++ i){
            result.push_back(pq.top());
            pq.pop();
        }

        return result;
    }
    //vector<int> GetLeastNumbers_Solution(vector<int> input, int k) {
        //vector<int> result;
        //size_t size = input.size();
        //if(size == 0 || static_cast<int>(size) < k)
            //return result;

        //priority_queue<int, vector<int>, greater<int> > pq;
        //for(size_t i = 0; i < size; ++ i){
            //pq.push(input[i]);
        //}
        //for(int i = 0; i < k; ++ i){
            //result.push_back(pq.top());
            //pq.pop();
        //}

        //return result;
    //}
};

int main(){
    vector<int> v;
    int arr[] = { 1, 4, 7, 9, 30, 5, 6, 23, 4, 8 };
    for(int i = 0; i < 10; ++ i){
        v.push_back(arr[i]);
    }
    Solution a;
    a.GetLeastNumbers_Solution(v, 4);
    return 0;
}
