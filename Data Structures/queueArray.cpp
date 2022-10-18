#include <iostream>
#include <exception>

using namespace std;

class QueueError : public runtime_error{
    public:
        QueueError(string const& message) : runtime_error(message) {} 
};

template <typename T>
class Queue{
    private:
        T* arr;
        int front;
        int rear;
        int max_capacity;
        int cur_size;
    
    public:
        Queue(int size = 10){
            this->max_capacity = size;
            this->arr = new T[max_capacity];
            this->front = 0;
            this->rear = 0;
            this->cur_size = 0;
        }

        void display();
        void enqueue(T element);
        T dequeue();
        T top();
};

template <typename T> T Queue<T>::dequeue(){
    if (cur_size == 0) throw QueueError("Empty Queue");

    T ret_value = this->arr[this->front];
    this->front++;
    this->cur_size--;
    return ret_value;
}
template <typename T> T Queue<T>::top(){
    if (cur_size == 0) throw QueueError("Empty Queue");

    return this->arr[this->front];
}
template <typename T> void Queue<T>::display(){
    if (this->cur_size == 0) cout << "Empty Queue" << endl;
    else{
        cout << "Front " << this->front << endl;
        cout << "Rear  " << this->rear << endl;
        int i = (front + 1) % max_capacity;
        cout << arr[front] << " "; 
        while (i != this->rear){
            cout << arr[i] << " ";
            i++;
            i = (i < max_capacity)? i: 0;
        }
        cout << endl;
    }
}
template <typename T> void Queue<T>::enqueue(T element){
    if (this->cur_size == this->max_capacity) throw QueueError("Queue Full");

    arr[rear++] = element;
    rear = rear % max_capacity;
    cur_size++;
}

int main(){
    Queue<int> Q(3);
    Q.enqueue(10);
    Q.enqueue(20);
    Q.enqueue(30);
    Q.display();
    cout << Q.dequeue() << endl;
    Q.display();
    Q.enqueue(10);
    Q.display();
    Q.enqueue(70);
}