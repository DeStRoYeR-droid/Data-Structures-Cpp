#include <iostream>

using namespace std;

template <typename T>
class Node{
    private:
        T value;
        Node* next;

    public:
        Node(){
            this->next = NULL;
        }
        Node(T value){
            this->value = value;
            this->next = NULL;
        }

        template <typename U> friend class SinglyLinkedList;
};

template <typename T>
class SinglyLinkedList{
    private:
        Node<T>* head;
        Node<T>* tail;
        int size;
    
    public:
        SinglyLinkedList(){
            head = tail = NULL;
            size = 0;
        }

        ~SinglyLinkedList(){
        	while (!empty()){
        		removeHead();
			}
			
			delete head, tail, size;
		}

        int getSize() const { return size;}

        bool empty() const{ return (head == NULL); }

        void print() const{
            if (empty()) cout << "Empty list" << endl;
            else{
                Node<T>* temp = head;
                while (temp->next != NULL){
                    cout << temp->value << "->";
                    temp = temp->next;
                }
                cout << temp->value << endl;
            }
        }

		void addBack(T value){
			Node<T>* temp = new Node<T>(value);
			
			if (head == NULL) head = tail = temp;
			else{
				tail->next = temp;
				tail = temp;
			}
			this->size++;
		}
		
        void addFront(T value){
            Node<T>* temp = new Node<T>(value);
            
            if (head == NULL) head = tail = temp;
			else{
            	temp->next = head;
            	head = temp;
        	}
			this->size++;
        }
        
        void removeHead(){
            if (empty()) throw "Underflow";
            
			Node<T>* temp = head;
            if (head == tail) head = tail = NULL;
            else head = head->next;
			            
            delete temp;
            size--;
        }

        void removeTail(){
        	if (empty()) throw "Underflow";
        	
			Node<T>* p = head;
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

        void removePos(int position){
			if (empty()) throw "Underflow";
			if (position < 0 || position > size) throw "PositionError";
			
			if (position == 1) removeHead();
			else if (position == size) removeTail();
			else{
				Node<T>* temp = head;
				Node<T>* trailer = NULL;
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
		
		void insertPos(T value , int position){
			if (position < 0 || position-1 > size) throw "PositionError";
			
			if (position == 1) addFront(value);
			else if (position == size+1) addBack(value);
			else{
				Node<T>* p = new Node<T>(value);
				Node<T>* temp = head;
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

        T& getValue(int position) {
            if (position < 0 || position-1 > size) throw "InvalidPositionError";
            else{
                int cur_pos = 1;
                Node<T>* temp = head;
                while (cur_pos < position){
                    temp = temp->next;
                    cur_pos++;
                }

                return temp->value;
            }
        }
};

template <typename T>
class SortedSinglyLinkedList : private SinglyLinkedList<T>{
    private:
        using SinglyLinkedList<T>::removePos;
        using SinglyLinkedList<T>::addFront;
        using SinglyLinkedList<T>::addBack;
        using SinglyLinkedList<T>::insertPos;

    public:
	 	using SinglyLinkedList<T>::removeHead;
		using SinglyLinkedList<T>::removeTail;
		using SinglyLinkedList<T>::getValue;
        using SinglyLinkedList<T>::getSize;
        using SinglyLinkedList<T>::print;
        using SinglyLinkedList<T>::empty;

        SortedSinglyLinkedList() : SinglyLinkedList<T>(){}

        void insert(T value){
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

        void deleteValue(T value){
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

};

class Term{
    private:
        int power;
        int coeff;
    
    public:
        Term(int power = 0, int coeff = 0){
            this->power = power;
            this->coeff = coeff;
        }

        friend ostream& operator << (ostream& out, const Term& t){
            out << "Coeff   : " << t.coeff << "\tPower   : " << t.power;

            return out;
        }
        
        bool operator > (const Term& oth){
            return (this->power > oth.power);
        } 
        
        Term operator + (const Term& oth){
            Term result;
            result.power = this->power + oth.power;
            result.coeff = this->coeff + oth.coeff;
            return result;
        }

        friend class Polynomial;
};

class Polynomial : private SortedSinglyLinkedList<Term>{
    private:
        using SortedSinglyLinkedList<Term>::insert;
        using SortedSinglyLinkedList<Term>::getValue;
        using SortedSinglyLinkedList<Term>::deleteValue;

    public:
        using SortedSinglyLinkedList<Term>::print;
        Polynomial() : SortedSinglyLinkedList<Term>(){}

        void addTerm(int power, int coeff){
            Term temp(power , coeff);
            for (int i = 1; i <= this->getSize(); i++){
                if (getValue(i).power == temp.power){
                    Term newValue = getValue(i) + temp;
                    getValue(i) = newValue;
                    return;
                }
            }
            insert(temp);
        }

        void print(){
            for (int i = 1; i <= this->getSize(); i++){
                cout << getValue(i) << endl;
            }
        }
};

int main(){
    Polynomial p1;
    p1.addTerm(0, 1);
    p1.addTerm(0, 2);
    p1.addTerm(0, 4);
    p1.addTerm(1, 9);
    p1.addTerm(2, 3);
    p1.addTerm(7, 2);
    p1.print();
    return 0;
}