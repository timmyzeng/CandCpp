#include <iostream>

using namespace std;

void BubbleSort(int arr[], int size){
    int index = size;
    int flag = 1;
    int change = 1;
    for(int i = size; i > 0; -- i){
        for(int j = 0; j < index-1; ++ j){
            if(arr[j] > arr[j+1]){
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
                change = j+1;
                flag = 0;
            }
        }
        index = change;
        if(flag){
            break;
        }
    }
}

void BubbleSortOP(int arr[], int size){
    int high = size - 1;
    int low = 0;
    while(low < high){
        bool flag = true;
        for(int i = low; i < high; ++ i){
            if(arr[i] > arr[i+1]){
                int tmp = arr[i];
                arr[i] = arr[i+1];
                arr[i+1] = tmp;
                flag = false;
            }
        }
        if(flag){
            break;
        } 
        -- high;
        for(int i = high; i > low; -- i){
             if(arr[i] < arr[i-1]){
                int tmp = arr[i];
                arr[i] = arr[i-1];
                arr[i-1] = tmp;
                flag = false;
            }
        }
        if(flag){
            break;
        } 
        ++ low;
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
    //BubbleSort(arr, sizeof(arr)/ sizeof(arr[0]));
    Print(arr, sizeof(arr)/ sizeof(arr[0]));
    BubbleSortOP(arr, sizeof(arr)/ sizeof(arr[0]));
    Print(arr, sizeof(arr)/ sizeof(arr[0]));
    return 0;
}
