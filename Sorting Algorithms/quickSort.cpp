#include <iostream>

using namespace std;

int partition(int* arr, int lower, int higher, int pivot){
    int i = lower;
    int j = lower;
    
    while (i <= higher){
        if (arr[i] > pivot){
            i++;
        }
        else{
            swap(arr[i], arr[j]);
            i++; 
            j++;
        }
    }

    return j-1;
}

void quickSort(int* arr, int lower, int higher){
    if (lower < higher){
        int pivot = arr[higher];
        int pos = partition(arr, lower, higher, pivot);

        quickSort(arr, lower , pos - 1);
        quickSort(arr, pos + 1 , higher);
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

    quickSort(array , 0 , length);

    printArray(array, length);
    return 0;
}