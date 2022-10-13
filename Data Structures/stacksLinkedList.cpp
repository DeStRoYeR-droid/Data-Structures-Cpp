#include <iostream>
#include <exception>

using namespace std;

// Exception classes
class Underflow : public exception{
    public:
	    const char * what() const throw(){
	    	return "Underflow : Top does not exist";
	    }
};
class Overflow : public exception{
    public:
	    const char * what() const throw(){
	    	return "Overflow : Memory limit exceeded";
	    }
};

// Node class 
template <typename T> class Node{
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

// Linked list class (singly linked list)
template <typename T> class singlyLinkedList{
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
        
       
		bool empty();
		
		int getSize();
		
		void addFront(T element);
		void print(string sep);
		
		T removeFront();
		T getHead();
};
template <typename T> bool singlyLinkedList<T>::empty(){
	return (this->size == 0);
}
template <typename T> void singlyLinkedList<T>::addFront(T element){
	Node<T>* newNode = new Node<T>(element);
	
	if (empty()) {
		head = tail = newNode;
	}
	else{
		newNode->next = head;
		head = newNode;
	}
	this->size++;
} 
template <typename T> void singlyLinkedList<T>::print(string sep){
	if (empty()) cout << "Empty List ";
	
	else{
		Node<T>* temp = this->head;
		
		while (temp->next != NULL){
			cout << temp->value << sep;
			temp = temp->next;
		}
		cout << temp->value;
	}		
}
template <typename T> T singlyLinkedList<T>::removeFront(){
	if (empty()) throw Underflow();
	else{
		Node<T>* temp = head;
		head = head->next;
		T ret_value = temp->value;
		
		delete temp;
		size--;
		return ret_value;
	}
}
template <typename T> int singlyLinkedList<T>::getSize(){
	return this->size;
}
template <typename T> T singlyLinkedList<T>::getHead(){
	return this->head->value;
}

// Stack class
template <typename T> class Stack{
	private:
		singlyLinkedList<T> stack;
	
	public:
		Stack(){
			this->stack;
		}
		
		void push(T element);
		void print();
		
		bool empty();
		
		T pop();
        T top();
};
template <typename T> void Stack<T>::print(){
	this->stack.print("");
}
template <typename T> void Stack<T>::push(T element){
	this->stack.addFront(element);
}
template <typename T> T Stack<T>::pop(){
	T value = this->stack.removeFront();
	return value;
}
template <typename T> T Stack<T>::top(){
	return this->stack.getHead();
}
template <typename T> bool Stack<T>::empty(){
	return this->stack.empty();
}

class BigNumber{
	private:
		Stack<int> number;
		string stringVal;
		
		void addDigit(int num){
			this->number.push(num);
			char val = 48 + num;
			this->stringVal = val + this->stringVal;
		}
		int removeDigit(){
			return this->number.pop();
		}
	
	public:
		BigNumber(string value = ""){
			this->number;
			for (int i = 0; i < value.size(); i++){
				number.push(value[i] - '0');
			}
			this->stringVal = value;
		}
		void showNumber();
		BigNumber operator + (const BigNumber& other);
		friend ostream& operator << (ostream& out , const BigNumber& obj){
			out << obj.stringVal;
			return out;
		}
};
void BigNumber::showNumber(){
	cout << this->stringVal;
}
BigNumber BigNumber::operator +(const BigNumber& other){
	int carry = 0;
	int sum;
	BigNumber a1(this->stringVal);
	BigNumber a2(other.stringVal);
	
	BigNumber result;
	
	while (!a1.number.empty() && !a2.number.empty()){
		sum = a1.removeDigit() + a2.removeDigit() + carry;
		carry = sum / 10;
		sum = sum % 10;
		result.addDigit(sum);
	}
	
	while (!a1.number.empty()){
		sum = a1.removeDigit() + carry;
		carry = sum / 10;
		sum = sum % 10;
		result.addDigit(sum);
	}
	while (!a2.number.empty()){
		sum = a2.removeDigit() + carry;
		carry = sum / 10;
		sum = sum % 10;
		result.addDigit(sum);
	}
	if (carry != 0){
		result.addDigit(carry);
	}
	return result;
}


void additionBignumbers(){
    BigNumber result;
    BigNumber term;
    BigNumber* numbers;
    string value;
    int n;
    int lenValue = 0;
    cout << "How many numbers do you want to add ";
    cin >> n;

    numbers = new BigNumber[n];

    for (int i = 0; i < n; i++){
        cout << "Please enter the value ";
        cin >> value;

        term = BigNumber(value);
        result = result + term;

        if (value.size() > lenValue){
            lenValue = value.size();
        }

        numbers[i] = term;
    }

    for (int i = 0; i < n; i++){
        if (i == 0){
            cout << '\t' << numbers[i] << endl;
        }
        else {
            cout << "+\t" << numbers[i] << endl;
        }
    }
    for (int i = 0; i < lenValue+14; i++){
        cout << "-";
    }
    cout << endl << '\t' << result << endl;

    for (int i = 0; i < lenValue+14; i++){
        cout << "-";
    }
}

int main(){
    additionBignumbers();
	return 0;
}