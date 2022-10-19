#include <bits/stdc++.h>

using namespace std;

void compareAndSwap(int* arr, int i, int j, int direction){
    if (direction == (arr[i] > arr[j])) swap(arr[i] , arr[j]);
}

void bitonicMerge(int* arr, int low, int cen, int dir){
    if (cen > 1){
        int k = cen / 2;
        for (int i = low; i < low + k; i++) compareAndSwap(arr, i , i+k, dir);
        bitonicMerge(arr, low, k, dir);
        bitonicMerge(arr, low+k, k, dir);
    }
}

void bitonicSort(int* arr, int low, int cen, int dir){
    if (cen > 1){
        int k = cen / 2;

        bitonicSort(arr, low, k , 1);
        bitonicSort(arr, low+k, k , 0);

        bitonicMerge(arr, low, cen , dir);
    }
}

void sort(int a[], int N, int up)
{
    bitonicSort(a,0, N, up);
}

void printArray(int* arr, int length){
    for (int i = 0; i < length; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main(){
    int length;
    int* array;

    cout << "Please enter the length of the array ";
    cin >> length;
    array = new int[length];
    for (int i = 0; i < length; i++){
        cout << "Please enter item of the array ";
        cin >> array[i];
    }

    sort(array , length, 1);

    printArray(array, length);
    return 0;
}