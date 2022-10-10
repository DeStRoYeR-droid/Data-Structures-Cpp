#include <iostream>

using namespace std;

template <typename T>
class Node{
    private:
        T value;
        Node* next;

    public:
        Node(){
            next = NULL;
        }

        Node(T value){
            this->value = value;
            next = NULL;
        }
        

        template <typename U> friend class singlyLinkedList;
};

template <typename T>
class singlyLinkedList{
    private:
        Node<T>* head;
        Node<T>* tail;
        int size;

    public:
        // Blank constructor
		singlyLinkedList(){
            head = tail = NULL;
            size = 0;
        }
        
		// Parameterized constructor
        singlyLinkedList(T value){
            Node<T>* temp = new Node<T>(value);
            head = tail = temp;
            size = 1;
        }
        
        // Destructor
        ~singlyLinkedList(){
        	while (!empty()){
        		removeHead();
			}
			
			delete head, tail, size;
		}
		
        // Method to get the size of linked list
		int getSize() const { return size;}
		
		// Method to check if linked list is empty or not
        bool empty() const{ return (head == NULL); }

		// Method to print the linked list
        void print() const{
            if (empty()) cout << "Empty list" << endl;
            else{
                Node* temp = head;
                while (temp->next != NULL){
                    cout << temp->value << "->";
                    temp = temp->next;
                }
                cout << temp->value << endl;
            }
        }
        
        //Method to add to the back of the list
		void addBack(int value){
			Node* temp = new Node(value);
			
			if (head == NULL) head = tail = temp;
			else{
				tail->next = temp;
				tail = temp;
			}
			this->size++;
		}
		
		// Method to add to the front of the list
        void addFront(int value){
            Node* temp = new Node(value);
            
            if (head == NULL) head = tail = temp;
			else{
            	temp->next = head;
            	head = temp;
        	}
			this->size++;
        }
        
        // Method to remove the head
        void removeHead(){
            if (empty()) throw "Underflow";
            
			Node* temp = head;
            if (head == tail) head = tail = NULL;
            else head = head->next;
			            
            delete temp;
            size--;
        }

        // Method to remove the tail
        void removeTail(){
        	if (empty()) throw "Underflow";
        	
			Node* p = head;
        	if (head == tail) head = tail = NULL;
        	else{				
	        	while (p->next != tail){
	        		p = p->next;
				}
				tail = p;
				p = p->next;
				tail->next = NULL;
			}
			
			delete p;
			size--;
		}
		
        // Method to remove an element at any given position
		void removePos(int position){
			if (empty()) throw "Underflow";
			if (position < 0 || position > size) throw "PositionError";
			
			if (position == 1) removeHead();
			else if (position == size) removeTail();
			else{
				Node* temp = head;
				Node* trailer = NULL;
				int cur_pos = 1;
				while (cur_pos != position){
					trailer = temp;
					temp = temp->next;
					cur_pos++;
				}
				trailer->next = temp->next;
				delete temp;
				size--;
			}
		}
		
        // Method to insert value at any given position
		void insertPos(int value , int position){
			if (position < 0 || position-1 > size) throw "PositionError";
			
			if (position == 1) addFront(value);
			else if (position == size+1) addBack(value);
			else{
				Node* p = new Node(value);
				Node* temp = head;
				int cur_pos = 1;
				while (cur_pos != position - 1){
					temp = temp->next;	
					cur_pos++;
				}
				p->next = temp->next;
				temp->next = p;
				size++;
			}
		}

        // Method to get the value at any given position
        int getValue(int position) const {
            if (position < 0 || position-1 > size) throw "InvalidPositionError";
            else{
                int cur_pos = 1;
                Node* temp = head;
                while (cur_pos < position){
                    temp = temp->next;
                    cur_pos++;
                }

                return temp->value;
            }
        }
		
        // Method to concatenate the values from one linked list to another
		void concatenate(singlyLinkedList& other){
			if (empty() && other.empty()) return;
			else if (other.empty()) return;
			else if (empty()){
				this->head = other.head;
				this->tail = other.tail;
				this->size = other.size;
			}
			else{
				this->tail->next = other.head;
				this->tail = other.tail;
				this->size += other.size;
			}
			other.head = other.tail = NULL;
            other.size = 0;
		}
		
        // Method to return first instanct of the node with any given value
		Node* search(int value) const{
            Node* temp = head;
            while (temp != NULL && temp->value != value){
                temp = temp->next;
            }
            
            if (temp) return temp;
            return NULL;
        }

        void reverse(){
            if (size < 2){
                // Literally do nothing
                return;
            }
            Node* temp = head;
            Node* prev = NULL;
            Node* next = NULL;

            while (temp != NULL){
                next = temp->next;
                temp->next = prev;

                prev = temp;
                temp = next;
            }
            head = prev;
        }
};