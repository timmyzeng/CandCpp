#include <iostream>

using namespace std;

void ShellSort(int arr[], int size){
    int space = size;
    int low = 0;

    //space最后一直都是1
    while(space > 1){
        space = space / 3 + 1;
        for(int front = 0; front < size-space; ++ front){
            low = front;
            int tmp = arr[low+space];
            while(low >= 0){
                if(arr[low] > tmp){
                    arr[low+space] = arr[low];
                    low -= space;
                }
                else{
                    break;
                }
            }
            arr[low+space] = tmp;
        }
    }
}

void Print(int arr[], int size){
    for(int i = 0 ; i < size; ++ i){
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main(){
    int arr[] = {1, 3, 5, 3, 2, 8, 6, 0};
    Print(arr, sizeof(arr)/ sizeof(arr[0]));
    ShellSort(arr, sizeof(arr)/ sizeof(arr[0]));
    Print(arr, sizeof(arr)/ sizeof(arr[0]));
    return 0;
}
