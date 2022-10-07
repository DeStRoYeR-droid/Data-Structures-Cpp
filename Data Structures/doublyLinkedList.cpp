#include <iostream>

using namespace std;

template <typename T>
class doubleLinkNode{
    private:
        T value;
        doubleLinkNode* next;
        doubleLinkNode* prev;

    public:
        doubleLinkNode(){
            next = prev = NULL;
        }

        doubleLinkNode(T value){
            this->value = value;
            this->next = this->prev = NULL;
        }

        template <typename U>friend class doublyLinkedList;
        friend class bigNumber;
};

template <typename T>
class doublyLinkedList{
    private:
        doubleLinkNode<T>* header;
        doubleLinkNode<T>* trailer;

    public:
        doublyLinkedList(){
            this->header = new doubleLinkNode<T>();
            this->trailer = new doubleLinkNode<T>();
            this->header->next = this->trailer;
            this->trailer->prev = this->header;
        }

        ~doublyLinkedList(){
            while (!empty()) removeFront();
            delete header , trailer;
        }

        bool empty(){return (header->next == trailer);}

        void addFront(T value){
            doubleLinkNode<T>* temp = new doubleLinkNode<T>(value);
            temp->next = header->next;
            temp->prev = header;
            header->next->prev = temp;
            header->next = temp;
        }

        void addBack(int value){
            doubleLinkNode<T>* temp = new doubleLinkNode<T>(value);
            temp->next = trailer;
            temp->prev = trailer->prev;
            trailer->prev->next = temp;
            trailer->prev = temp;
        }

        void removeFront(){
            if (empty()) throw "UnderflowException";

            doubleLinkNode<T>* temp = this->header->next;
            
            header->next = temp->next;
            temp->next->prev = header;

            delete temp;
        }

        void removeBack(){
            if (empty()) throw "UnderflowException";

            doubleLinkNode<T>* temp = this->trailer->prev;

            trailer->prev = temp->prev;
            temp->prev->next = trailer;

            delete temp;
        }

        void print() const{
            if (header->next == trailer) cout << "Empty List" << endl;

            else{
                doubleLinkNode<T>* temp = this->header->next;
                while (temp != this->trailer->prev){
                    cout << temp->value << "->";
                    temp = temp->next;
                }
                cout << temp->value << endl;
            }
        }

        friend class bigNumber;
};

class bigNumber : private doublyLinkedList<int>{
    private:
        using doublyLinkedList<int>::addBack;
        using doublyLinkedList<int>::addFront;

    public:
        bigNumber(string value = "") : doublyLinkedList<int>(){
            int i;
            for (i = value.size(); i >= 4; i=i-4){
                this->addFront(stoi(value.substr(i-4, 4)));
            }
            int remainingDigits = value.size() % 4;
            if (remainingDigits){
                this->addFront(stoi(value.substr(i-remainingDigits, remainingDigits)));
            }
        }

        bigNumber operator + (const bigNumber& other){
            bigNumber result;

            doubleLinkNode<int>* thisPointer = this->trailer->prev;
            doubleLinkNode<int>* othPointer = other.trailer->prev;

            int carry = 0;
            int sum_terms;

            while (thisPointer != header && othPointer != other.header){
                sum_terms = thisPointer->value + othPointer->value + carry;
                carry = sum_terms / 10000;
                sum_terms = sum_terms % 10000;

                result.addFront(sum_terms);

                thisPointer = thisPointer->prev;
                othPointer = othPointer->prev;
            }

            while (thisPointer != header){
                sum_terms = thisPointer->value + carry;
                carry = sum_terms / 10000;
                sum_terms = sum_terms % 10000;
                result.addFront(sum_terms);
                
                thisPointer = thisPointer->prev;
            }

            while (othPointer != other.header){
                sum_terms = othPointer->value + carry;
                carry = sum_terms / 10000;
                sum_terms = sum_terms % 10000;
                result.addFront(sum_terms);
                othPointer = othPointer->prev;
            }

            if (carry){
                result.addFront(carry);
            }

            return result;   
        }

        void print() const{
            doubleLinkNode<int>* temp = header->next;
            cout << temp->value;
            temp = temp->next;
            while (temp != trailer){
                int value = temp->value; 
                
                if (value < 10) cout << "000" << value;
                else if (value < 100) cout << "0" << value;
                else if (value < 1000) cout << "00" << value;
                else cout << value;

                temp = temp->next;
            }
            cout << endl;
        }
};

int main(){
    string number = "99999999";
    bigNumber b1(number);
    b1.print();

    string number2 = "1";
    bigNumber b2(number2);
    b2.print();

    bigNumber b3 = b1 + b2;
    b3.print();
    return 0;
}