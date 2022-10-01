#include <iostream>

using namespace std;

class Node{
    private:
        int value;
        Node* next;

    public:
        Node(){
            value = 0;
            next = NULL;
        }

        Node(int value){
            this->value = value;
            next = NULL;
        }
        

        friend class singlyLinkedList;
};

class singlyLinkedList{
    private:
        Node* head;
        Node* tail;
        int size;

    public:
        // Blank constructor
		singlyLinkedList(){
            head = tail = NULL;
            size = 0;
        }
        
		// Parameterized constructor
        singlyLinkedList(int value){
            Node* temp = new Node(value);
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
};

class sortedSinglyLinkedList : private singlyLinkedList{
	public:
        // Declaring the members of parent class which are to be made public
	 	using singlyLinkedList::removeHead;
		using singlyLinkedList::removeTail;
		using singlyLinkedList::getValue;
        using singlyLinkedList::getSize;
        using singlyLinkedList::print;
        using singlyLinkedList::search;
    
        // Default constructutor
        sortedSinglyLinkedList() : singlyLinkedList(){}
        // Parameterized constructor
        sortedSinglyLinkedList(int value) : singlyLinkedList(value){}

        // Method to insert value whilst maintaining order
        void insert(int value){
            if (empty()) addFront(value);
            else{
                for (int i = 1; i <= getSize(); i++){
                    if (getValue(i) > value){
                        insertPos(value , i);
                        return;
                    }
                }
                addBack(value);
            }
        }

        // Method to delete the first instance of value
        void deleteValue(int value){
            if (empty()) throw "Underflow";
            bool found = false;
            for (int i = 1; i <= getSize(); i++){
                if (getValue(i) == value){
                    found = true;
                    removePos(i);
                    break;
                }
                else if (getValue(i) > value) break;
            }
            if (!found) throw "ValueNotFoundException";
        }

        // Merge this list with another sorted linked list to result in another sorted linked list
        sortedSinglyLinkedList merge(const sortedSinglyLinkedList& oth){
            int thisPos = 1;
            int othPos = 1;

            sortedSinglyLinkedList temp;
            
            while (thisPos <= getSize() && othPos <= oth.getSize()){ 
                if (getValue(thisPos) == oth.getValue(othPos)){
                    temp.addBack(getValue(thisPos));
                    thisPos++;
                    othPos++;
                }
                else if (getValue(thisPos) < oth.getValue(othPos)){
                    temp.addBack(getValue(thisPos));
                    thisPos++;
                }
                else{
                    temp.addBack(oth.getValue(othPos));
                    othPos++;
                }
            }

            if (thisPos <= getSize()){
                while (thisPos <= getSize()){
                    temp.addBack(getValue(thisPos));
                    thisPos++;
                }
            }

            if (othPos <= oth.getSize()){
                while (othPos <= oth.getSize()){
                    temp.addBack(oth.getValue(othPos));
                    othPos++;
                }
            }

            return temp;
        }
};

int main(){
	try{
        /*
		sortedSinglyLinkedList l1;
        l1.insert(14);
        l1.insert(17);
        l1.insert(12);
        l1.insert(12);
        l1.insert(1);
        l1.insert(27);
        l1.print();
        l1.deleteValue(12);
        l1.deleteValue(12);
        l1.print();

        sortedSinglyLinkedList l2;
        l2.insert(24);
        l2.insert(94);
        l2.insert(21);
        l2.insert(42);
        l2.insert(1);
        l2.removeTail();
        l2.print();

        sortedSinglyLinkedList l3 = l1.merge(l2);
        l3.print();
        */
        

       /*
        singlyLinkedList l1;
        l1.addFront(12);
        l1.addFront(75);
        l1.addFront(93);
        l1.addFront(31);
        l1.insertPos(18 , 3);

        singlyLinkedList l2;
        l2.addFront(91);
        l2.addBack(100);

        l1.concatenate(l2);

        l1.print();
        l2.print();
        */

	} catch (const char* exp){
		cout << "Exception occurred : " << exp << endl;
	}
	return 0;
}