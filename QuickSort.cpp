#include <iostream>

using namespace std;

void QuickSort(int arr[], int low, int high){
    int key = arr[high];

    if(low >= high){
        return;
    }
    int left = low;
    int right = high;

    while(left < right){
        while(left < right && arr[left] <= key){
            ++ left;
        }
        arr[right] = arr[left];
        while(left < right && arr[right] >= key){
            -- right;
        }
        arr[left] = arr[right];
    }
    arr[left] = key;
    QuickSort(arr, low, left-1);
    QuickSort(arr, left+1, high);
}

void QuickSort2(int arr[], int low, int high){
    int key = arr[high];

    if(low >= high){
        return;
    }
    int left = low;
    int right = high;

    while(left < right){
        while(left < right && arr[left] <= key){
            ++ left;
        }
        while(left < right && arr[right] >= key){
            -- right;
        }
        if(left != right){
            swap(arr[left], arr[right]);
        }
    }
    swap(arr[left], arr[high]);
    QuickSort2(arr, low, left-1);
    QuickSort2(arr, left+1, high);
}

//三数取中
int Mid(int *arr, int low, int high){
    int middle = low + (high-low)/2;
    if(arr[low] < arr[high]){
        if(arr[high] < arr[middle]){
            return high;
        }
        else if(arr[middle] < arr[low]){
            return low;
        }
        else{
            return middle;
        }
    }
    else{
        if(arr[low] < arr[middle]){
            return low;
        }
        else if(arr[middle] < arr[high]){
            return high;
        }
        else{
            return middle;
        }
    }
}

void QuickSort3(int arr[], int low, int high){
    if(low >= high){
        return;
    }

    int index = Mid(arr, low, high);
    swap(arr[index], arr[high]);

    int key = arr[high];
    int cur = low;
    int prev = cur-1;
    while(cur <= high){
        while(cur <= high && arr[cur] > key){
            ++ cur;
        }
        if(++ prev != cur){
            swap(arr[prev], arr[cur]);
        }
        ++ cur;
    }
    QuickSort3(arr, low, prev-1);
    QuickSort3(arr, prev, high);
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
    QuickSort3(arr, 0, sizeof(arr)/ sizeof(arr[0])-1);
    Print(arr, sizeof(arr)/ sizeof(arr[0]));
    return 0;
}
