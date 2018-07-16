#include <iostream>

using namespace std;

void SelectSort(int arr[], int size){
    int min = 0;
    for(int i = 0; i < size; ++ i){
        min = i;
        for(int j = i + 1; j < size; ++ j){
            if(arr[j] < arr[min]){
                min = j;
            }
        }
        if(min != i){
            swap(arr[min], arr[i]);
        }
    }
}

void SelectSortOP(int arr[], int size){
    int begin = 0;
    int end = size - 1;
    for(; begin < end; ++ begin, -- end){
        int min = begin;
        int max = begin;
        for(int i = begin; i <= end; ++ i){
            if(arr[max] < arr[i]){
                max = i;
            }
            if(arr[min] > arr[i]){
                min = i;
            }
        }
        if(max != end){
            swap(arr[max], arr[end]);
        }
        //防止min在end，max在begin。
        //然后出现交换两次的情况，这样就等于没有交换
        if(end == min){
            min = max;
        }
        if(min != begin){
            swap(arr[min], arr[begin]);
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
    SelectSortOP(arr, sizeof(arr)/ sizeof(arr[0]));
    Print(arr, sizeof(arr)/ sizeof(arr[0]));
    return 0;
}
