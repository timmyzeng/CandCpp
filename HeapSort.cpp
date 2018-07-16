#include <iostream>

using namespace std;

void Down(int arr[], int index, int size){
    int parent = index;
    int child = parent*2 + 1;
    while(child < size){
        if(child+1 < size && arr[child] < arr[child+1]){
            ++ child;
        }
        if(arr[child] > arr[parent]){
            swap(arr[child], arr[parent]);
            parent = child;
            child = parent*2 + 1;
        }
        else{
            break;
        }
    }
}

void HeadSort(int arr[], int size){
    //建堆
    for(int i = (size-1-1)/2; i >= 0; -- i){
        Down(arr, i, size);
    }
    int end = size - 1;
    while(end > 0){
        swap(arr[0], arr[end]);
        Down(arr, 0, end);
        -- end;
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
    HeadSort(arr, sizeof(arr)/ sizeof(arr[0]));
    Print(arr, sizeof(arr)/ sizeof(arr[0]));
    return 0;
}
