#include <iostream>

using namespace std;

template <typename T>
int binarySearch(const T* arr, const int length, const T element){
    int lower = 0;
    int upper = length - 1;
    int middle;

    while (lower <= upper){
        middle = (lower + upper) / 2;
        if (arr[middle] == element) return middle;
        if (arr[middle] > element) upper = middle - 1;
        else lower = middle + 1;
    }

    return -1;
}

int main(){    int length;
    int* array;
    int element;

    cout << "Please enter the length of the array ";
    cin >> length;

    array = new int[length];
    for (int i = 0; i < length; i++){
        cout << "Please enter the one item of the array (in ascending order) ";
        cin >> array[i];

        if (i != 0 && array[i] < array[i-1]){ 
            cout << "Please enter items in ascending order" << endl; 
            return 0;
        }
    }

    cout << "Please enter the element you want to check for ";
    cin >> element;

    int result = binarySearch(array, length, element);
    if (result != -1) cout << "First occurence of element found at index " << result << endl;
    else cout << "Element not found in the given array" << endl;

    return 0;
}