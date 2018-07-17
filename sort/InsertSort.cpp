#include <iostream>

using namespace std;

void InsertSort(int arr[], int size){
    for(int i = 0; i < size-1; ++ i){
        int j = i+1;
        int tmp = arr[j];
        while(j > 0){
            if(tmp < arr[j-1]){
                arr[j] = arr[j-1];
                -- j;
            }
            else{
                break;
            }
        }
        arr[j] = tmp;
    }
}

//二分查找函数，如果arr中有跟key相同的元素，返回该元素的最后一个下标
//如果没有，返回最后一个小于key的下一个下标。
int BinarySearch(int arr[], int size, int key){
    int low = 0;
    int high = size - 1;
    //等于不能少
    while(low <= high){
        int mid = low + (high-low)/2;
        if(arr[mid] < key){
            low = mid+1;
        }
        else if(arr[mid] > key){
            high = mid-1;
        }
        else{
            int next = mid+1;
            while(next < size && arr[next] == arr[mid]){
                ++ next;
                ++ mid;
            }
            return next;
        }
    }
    return low;
}

void InsertSortBinary(int arr[], int size){
    for(int i = 0; i < size-1; ++ i){
        int j = i+1;
        int tmp = arr[j];
        if(tmp < arr[j-1]){
            int index = BinarySearch(arr, j, tmp);
            while(j > index){
                arr[j] = arr[j-1];
                -- j;
            }
            arr[index] = tmp;
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
    int arr[] = {1, 5, 3, 2, 8, 6, 0};
    //int arr[] = {1, 3, 5, 3, 2, 8, 6, 0};
    //int arr[] = {1,2,2,2,5,7,2,0};
    Print(arr, sizeof(arr)/ sizeof(arr[0]));
    InsertSortBinary(arr, sizeof(arr)/ sizeof(arr[0]));
    Print(arr, sizeof(arr)/ sizeof(arr[0]));
    return 0;
}
