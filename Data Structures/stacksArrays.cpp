#include <iostream>
#include <exception>

using namespace std;

class Underflow : public runtime_error{
    public:
    Underflow(const string& what = "Underflow : Top does not exist") : runtime_error(what) {}
};
class Overflow : public runtime_error{
    public:
    Overflow(const string& what = "Overflow : Memory limit exceeded") : runtime_error(what) {};
};

template <typename T>
class Stack{
    private:
        unsigned int max_size;
        int cur_top;
        T* stack;

    public:
        Stack(int size = 10){
            this->cur_top = -1;
            this->max_size = size;
            this->stack = new T[max_size];
        }

        bool empty();
        bool full();

        T pop();
        T top();
        
        void print();
        void push(T element);      
};

template <typename T> bool Stack<T>::empty(){ return (this->cur_top == -1); }
template <typename T> bool Stack<T>::full(){ return (this->cur_top == this->max_size-1); }

template <typename T> T Stack<T>::pop(){
    if (empty()) throw Underflow();
    return this->stack[cur_top--];
}
template <typename T> T Stack<T>::top(){
    if (empty()) throw Underflow();
    return this->stack[cur_top];
}

template <typename T> void Stack<T>::print(){
    cout << "Top : [ ";
    for (int i = cur_top; i >= 0; i--){
        cout << this->stack[i] << " ";
    }
    cout << "] : End";
    cout << endl;
}
template <typename T> void Stack<T>::push(T element){
    if (full()) throw Overflow();
    this->stack[++cur_top] = element;
}

int main(){
    try{
        Stack<int> s(5);
        s.push(10);
        s.push(11);
        s.print();
        s.pop();
        s.push(13);
        s.print();
        s.pop();
        s.print();
        s.pop();
        s.print();
        s.push(10);
        s.push(12);
        s.push(13);
        s.push(14);
        s.push(15);
        s.print();
        s.push(16);
    }
    catch (Underflow ue){
        cout << ue.what() << endl;
    }
    catch (Overflow oe){
        cout << oe.what() << endl;
    }
    catch (const char* exp){
        cout << "Exception Occurred : " << exp << endl;
    }
    return 0;
}