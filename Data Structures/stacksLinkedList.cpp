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
class InvalidExpression : public runtime_error{
	private: 
		const char* msg;
	public:
		InvalidExpression(const char* what = "") : 
			runtime_error(what){
				this->msg = what;
			}  
	    const char * what() const throw(){
	    	return this->msg;
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

		int getSize();
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
template <typename T> int Stack<T>::getSize(){
	return this->stack.getSize();
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
        int getSize();
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
int BigNumber::getSize(){
    return this->stringVal.size();
}

void additionBignumbers(){
    BigNumber result;
    BigNumber term;
    BigNumber* numbers;
    string value;
    int n;
    int size;
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
    cout << endl;
    
    for (int i = 0; i < n; i++){
        size = numbers[i].getSize();
        if (i == 0){
            cout << "\t";
            for (int i = 0; i < lenValue - size; i++){
                cout << " ";
            }
            cout << numbers[i] << endl;
        }
        else {
            cout << "+\t";
            for (int i = 0; i < lenValue - size; i++){
                cout << " ";
            }
            cout << numbers[i] << endl;
        }
    }
    for (int i = 0; i < lenValue+10; i++){
        cout << "-";
    }
    cout << endl << '\t' << result << endl;

    for (int i = 0; i < lenValue+10; i++){
        cout << "-";
    }
}


// Infix to postfix conversion
int calculateExpression(int operand1, int operand2, char symbol){
	int result;
	switch(symbol){
		case '+':
			result = operand1 + operand2;
			break;

		case '-':
			result = operand1 - operand2;
			break;

		case '/':
			result = operand1 / operand2;
			break;

		case '*':
			result = operand1 * operand2;
			break;

		case '^':
			result = 1;
			for (int i = 0; i < operand2; i++){
				result = result * operand1;
			}
			break;
			
		case '%':
			result = operand1 % operand2;
			break;
		
		default:
			throw InvalidExpression("Invalid operators are there in place");
	}
	return result;
}
int calculateValue(string expression){
	Stack<int> operands;
	try{
		for (int i = 0; i < expression.size(); i++){
			int val = expression[i] - '0';

			if (val > 0 && val < 10){
				operands.push(val);
			}
			else{
				int operand2 = operands.pop();
				int operand1 = operands.pop();
				
				operands.push(calculateExpression(operand1 , operand2, expression[i]));
			}
		}
	}
	catch (Underflow ue){
		throw InvalidExpression("Expresssion has more operands than possible");
	}
	if (operands.getSize() > 1) throw InvalidExpression("The expression has more operands than possible");
	return operands.pop();
}
int precedence(char operation){
	if (operation == '(') return -1;
	else if (operation == '^') return 3;
	else if (operation == '*' || operation == '/' || operation == '%') return 2;
	else if (operation == '+' || operation == '-') return 1;
	
	else throw InvalidExpression("Invalid operator passed");
}
string infixToPostfix(string expression){
	Stack<char> operations;
	string result;
	char cur_char;
	for (int i = 0; i < expression.size(); i++){
		cur_char = expression[i];
		
		if (cur_char >= '0' && cur_char <= '9') result += cur_char;
		else if (cur_char == '(') operations.push(cur_char);
		else if (cur_char == ')'){
			while (operations.top() != '('){
				result += operations.pop();
			}
			operations.pop();
			operations.print();
		}
		else{
			while (!operations.empty() && precedence(cur_char) <= precedence(operations.top())){
				result += operations.pop();
			}
			operations.push(cur_char);
		}
	}
	
	while (!operations.empty()) result += operations.pop();
	
	return result;
}

int main(){
	try{
		string infixExpression;
		
		cout << "Please enter your expression ";
		cin >> infixExpression;
		
		string postfixExpression = infixToPostfix(infixExpression);
		
		cout << "Infix expression = " << infixExpression << endl;
		cout << "Postfix expression = " << postfixExpression << endl;
		cout << "Value of expression = " << calculateValue(postfixExpression) << endl;
	}
	catch (InvalidExpression ie){
		cout << ie.what() << endl;
	}
	return 0;
}