#include <iostream>

using namespace std;

template <typename T>
void bubbleSort(T* arr, int length){
    for (int i = 0; i < length; i++){
        bool swapped = false;
        for (int j = 0; j < length - i - 1; j++){
            if (arr[j] > arr[j+1]){
                swap(arr[j] , arr[j+1]);
                swapped = true;
            }
        }

        if (!swapped) break;
    }
}

template <typename T>
void insertionSort(T* arr, int length){
    for (int i = 1; i < length; i++){
        T temp = arr[i];
        int j = i-1;
        while (j >= 0 && arr[j] > temp){
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = temp;
    }
}

template <typename T>
void selectionSort(T* arr, int length){
    for (int i = 0; i < length; i++){
        int min = i;
        for (int j = i+1; j < length; j++){
            if (arr[j] < arr[min]){
                min = j;
            }
        }
        swap(arr[i] , arr[min]);
    }
}

int main(){
    int length;
    int* array;
    int choice;

    cout << "Please enter the length of the array ";
    cin >> length;

    array = new int[length];
    for (int i = 0; i < length; i++){
        cout << "Please enter the one item of the array ";
        cin >> array[i];
    }

    cout << "Array before sorting" << endl;
    for (int i = 0; i < length; i++){
        cout << array[i] << " ";
    }
    cout << endl << endl;

    cout << "Which sorting algorithm do you want to use on the passed array " << endl;
    cout << "1. Bubble Sort" << endl;
    cout << "2. Insertion Sort" << endl;
    cout << "3. Selection Sort" << endl;
    cout << "Please enter your choice (1/2/3) ";
    cin >> choice;

    switch(choice){
        case 1:
            bubbleSort(array, length);
            break;

        case 2:
            insertionSort(array, length);
            break;
        
        case 3:
            selectionSort(array, length);
            break;
        
        default:
            cout << "Please enter a valid choice next time" << endl;
            return 0;
    } 

    cout << "Sorted array is as follows" << endl;
    for (int i = 0; i < length; i++){
        cout << array[i] << " ";
    }
    cout << endl;



    return 0;
}