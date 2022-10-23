#include <iostream>

using namespace std;

void merge(int* arr, int left, int mid, int right){
    // Copying value from the array
    int i , j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int leftSubarray[n1] , rightSubarray[n2];

    for (int i = 0; i < n1; i++) leftSubarray[i] = arr[left + i];
    for (int j = 0; j < n2; j++) rightSubarray[j] = arr[mid + j + 1];

    i = 0;      // Index of left sub array
    j = 0;      // Index of right subarray
    k = left;   // Index of pseudo-sorted array

    while (i < n1 && j < n2){
        if (leftSubarray[i] <= rightSubarray[j]){
            arr[k] = leftSubarray[i];
            i++;
        }
        else{
            arr[k] = rightSubarray[j];
            j++;
        }
        k++;
    }

    while (i < n1){
        arr[k] = leftSubarray[i];
        i++; k++;
    }

    while (j < n2){
        arr[k] = rightSubarray[j];
        j++; k++;
    }
}

void mergeSort(int* arr, int left, int right){
    if (left < right){
        int mid = (left + right) / 2;
        mergeSort(arr, left ,mid);
        mergeSort(arr, mid+1, right);
        merge(arr, left, mid, right);
    }
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

    mergeSort(array , 0 , length);

    printArray(array, length);
    return 0;
}