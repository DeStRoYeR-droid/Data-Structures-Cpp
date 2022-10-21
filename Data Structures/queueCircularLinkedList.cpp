#include <iostream>
#include <string>

using namespace std;

template <typename T> class Node{
    private:
        T value;
        Node* next;

    public:
        Node(T value){
            this->value = value;
            next = NULL;
        }

        template <typename U> friend class CircularLinkedList;
};

template <typename T> class CircularLinkedList{
    private:
        Node<T>* cursor;
    
    public:
        CircularLinkedList(){
            cursor= NULL;
        }
        ~CircularLinkedList(){
            while (!empty()){removeFront();}
            delete cursor;
        }
        bool empty() const{
            return (cursor == NULL);
        }  
        void advance(){
            if (empty()) throw "EmptyList";

            cursor = cursor->next;
        }
        void addFront(T element){
            Node<T>* temp = new Node<T>(element);
            
            if (cursor == NULL){
                temp->next = temp;
                cursor = temp;
            }
            else {
                temp->next = cursor->next;
                cursor->next = temp;
            }
        }
        void addBack(T element){
            addFront(element);
            advance();
        }
        void removeFront(){
            if (empty()) throw "UnderFlowError";

            Node<T>* temp = cursor->next;
            if (temp == cursor){
                cursor = NULL;
            }
            else{
                cursor->next = temp->next;
            }
            delete temp;        }
        void removeBack(){
            if (empty()) throw "UnderFlowError";

            Node<T>* temp = cursor;
            if (temp->next == cursor){
                cursor = NULL;
            }
            else{
                Node<T>* trailer = temp->next;

                while (trailer->next != temp){
                    trailer = trailer->next;
                }
                cursor = trailer;
                cursor->next = temp->next;

            }

            delete temp;
        }
        T top(){
        	return this->cursor->next->value;
		}
        void display(string start = "", string nextPtr = " ", string endPtr = "") const{
            if (cursor == NULL) throw "EmptyList";

            Node<T>* traverser = cursor->next;

            do{
                cout << start << traverser->value << nextPtr << endPtr;
                traverser = traverser->next;
            } while (traverser != cursor->next);
        }
};

template <typename T> class Queue{
	private:
		CircularLinkedList<T> cll;
	
	public:
		Queue(){
			this->cll;
		}
		
		bool empty() const;
		T dequeue();
		T top() const;
		void enqueue(T element);
		void display() const;
};

template <typename T> bool Queue<T>::empty() const{
	return cll.empty();
}
template <typename T> T Queue<T>::dequeue(){
	T val = cll.top();
	cll.removeFront();
	return val;
}
template <typename T> T Queue<T>::top() const{
	return cll.top();
}
template <typename T> void Queue<T>::enqueue(T element){
	cll.addBack(element);
}
template <typename T> void Queue<T>::display() const{
	cll.display("" , " " , "");
}

int main(){
	Queue<int> q;
	q.enqueue(10);
	q.display();
	cout << endl;
	q.enqueue(20);
	q.enqueue(30);
	q.display();
	cout << endl;
	cout << "Dequeued element = " << q.dequeue() << endl;
	q.display();
	cout << endl;
	return 0;
}