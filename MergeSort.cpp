#include <iostream>
#include <cstdlib>

using namespace std;

void Merge(int arr[], int* tmp, int left1, int right1, int left2, int right2){
    int i = left1;
    int front = left1;
    int end = right2;
    while(left1 <= right1 && left2 <= right2){
        if(arr[left1] <= arr[left2]){
            tmp[i++] = arr[left1++];
        }
        else if(arr[left1] > arr[left2]){
            tmp[i++] = arr[left2++];
        }
    }
    while(left1 <= right1){
        tmp[i++] = arr[left1++];
    }
    while(left2 <= right2){
        tmp[i++] = arr[left2++];
    }

    while(front <= end){
        arr[front] = tmp[front];
        front ++;
    }
}

void MergeSort(int arr[], int* tmp, int left, int right){
    if(left >= right){
        return;
    }
    int mid = left + (right - left) / 2;

    MergeSort(arr, tmp, left, mid);
    MergeSort(arr, tmp, mid+1, right);
    Merge(arr, tmp, left, mid, mid+1, right);
}

void MergeSortNoR(int *list, int length){  
    int i, left_min, left_max, right_min, right_max, next;  
    int *tmp = (int*)malloc(sizeof(int) * length);  

    for (i = 1; i < length; i *= 2)  
            for (left_min = 0; left_min < length - i; left_min = right_max){   
                    right_min = left_max = left_min + i;  
                    right_max = left_max + i;  
                    if (right_max > length)  
                            right_max = length;  
                    next = 0;  
                    while (left_min < left_max && right_min < right_max)  
                            tmp[next++] = list[left_min] > list[right_min] ? list[right_min++] : list[left_min++];  
                    while (left_min < left_max)  
                            list[--right_min] = list[--left_max];  
                    while (next > 0)  
                            list[--right_min] = tmp[--next];  
            }  
    free(tmp);
}  

void Print(int arr[], int size){
    for(int i = 0 ; i < size; ++ i){
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main(){
    int arr[] = {1, 3, 5, 3, 2, 8, 6, 0};
    int *tmp = new int[sizeof(arr)/sizeof(arr[0])];
    Print(arr, sizeof(arr)/ sizeof(arr[0]));
    //MergeSort(arr, tmp, 0, sizeof(arr)/sizeof(arr[0])-1);
    MergeSortNoR(arr, sizeof(arr)/ sizeof(arr[0]));
    Print(arr, sizeof(arr)/ sizeof(arr[0]));
    delete[] tmp;
    return 0;
}
