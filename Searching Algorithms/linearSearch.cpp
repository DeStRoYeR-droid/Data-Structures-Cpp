#include <iostream>

using namespace std;

template <typename T>
int linearSearch(const T* arr, const int length, const T element){
    for (int i = 0; i < length; i++){
        if (arr[i] == element) return i;
    }
    return -1;
}

int main(){
    int length;
    int* array;
    int element;

    cout << "Please enter the length of the array ";
    cin >> length;

    array = new int[length];
    for (int i = 0; i < length; i++){
        cout << "Please enter the one item of the array ";
        cin >> array[i];
    }

    cout << "Please enter the element you want to check for ";
    cin >> element;

    int result = linearSearch(array, length, element);
    if (result != -1) cout << "First occurence of element found at index " << result << endl;
    else cout << "Element not found in the given array" << endl;

    return 0;
}