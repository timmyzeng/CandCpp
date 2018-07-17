/*************************************************************************
	> File Name: 01find_array.cpp
	> Author: Timmy
	> Created Time: 2018年04月08日 星期日 16时45分42秒
 ************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

int main(){
    system("clear");

    //创建一个arr[2][3]
    vector< vector<int> > arr(2, vector<int>(3));
    for(int i = 0; i <  arr.size(); ++i){
        for(int j = 0; j < arr[0].size(); ++j){
            arr[i][j] = i+j;
        }
    }

    //创建一个arr[3][4]
    vector< vector<int> > arr1(3, vector<int>(3));
    for(int i = 0; i < arr1.size(); ++i){
        arr1[i].resize(4);
    }
    for(int i = 0; i < arr1.size(); ++i){
        for(int j = 0; j < arr1[0].size(); ++j){
            arr1[i][j] = i+j;
        }
    }

    cout << "arr[2][3]:" << endl;
    for(int i = 0; i < arr.size(); ++i){
        for(int j = 0; j < arr[i].size(); ++j){
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }

    cout << endl;
    cout << "arr1[3][4]:" << endl;
    vector<int>::iterator it1;
    vector<vector<int> >::iterator it2;
    for(it2 = arr1.begin(); it2 != arr1.end(); ++it2){
        for(it1 = (*it2).begin(); it1 != (*it2).end(); ++it1){
            cout << *it1 << " ";
        }
        cout << endl;
    }

    return 0;
}
