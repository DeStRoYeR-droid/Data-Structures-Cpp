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

        void setValue(int newVal){
            this->value = newVal;
        }

        void setNext(int value){
            Node* temp = new Node(value);
            this->next = temp;
        }

        void setNext(Node* nextNode){
            this->next = nextNode;
        }

        int getValue(){
            return this->value;
        }

        Node* getNext(){
            return this->next;
        }
    
        friend class LinkedList;
};

class LinkedList{
    private:
        Node* head;
        Node* tail;

    public:
        LinkedList(){
            head = tail = NULL;
        }

        LinkedList(int value){
            Node* temp = new Node(value);
            head = tail = temp;
        }

        LinkedList(const LinkedList& l1){
            this->head = l1.head;
        }

        void addFront(int value){
            Node* temp = new Node(value);
            
            if (head == NULL){
                head = tail = temp;
                return;
            }

            temp->next = head;
            head = temp;
        }

        void addBack(int value){
            Node* temp = new Node(value);

            if (tail == NULL){
                head = tail = temp;
            }

            tail->next = temp;
            tail = temp;
        }

        void print(){
            Node* temp = head;
            while (temp->next != NULL){
                cout << temp->value << "->";
                temp = temp->next;
            }
            cout << temp->value << endl;
        }

        int getLength() const{
            if (head == NULL){
                return 0;
            }

            int length = 1;
            Node* temp = head;
            while (temp->next != NULL){
                length++;
                temp = temp->next;
            }

            return length;
        }

        int getValue(int pos) const {
            if (pos > getLength()) throw "OutOfBoundsException";
            if (pos == 1) return head->value;

            int cur_pos = 1;
            Node* temp = head;
            while (cur_pos != pos){
                temp = temp->next;
                cur_pos++;
            }
            return temp->value;
        }

        LinkedList merge(const LinkedList& l1){
            int chosen_this = 1;
            int chosen_oth = 1;

            LinkedList temp;

            while (chosen_this <= getLength() && chosen_oth <= l1.getLength()){
                int val_this = getValue(chosen_this);
                int val_oth = l1.getValue(chosen_oth);

                if (val_this > val_oth){
                    temp.addBack(val_oth);
                    chosen_oth++;
                }

                else {
                    temp.addBack(val_this);
                    chosen_this++;
                }
            }

            if (chosen_this <= getLength()){
                while (chosen_this <= getLength()){
                    temp.addBack(getValue(chosen_this));
                    chosen_this++;
                }
            }

            if (chosen_oth <= l1.getLength()){
                while (chosen_oth <= getLength()){
                    temp.addBack(l1.getValue(chosen_oth));
                    chosen_oth++;
                }
            }

            return temp;
        }
        
};

int main(){
    LinkedList l1(20);
    l1.addFront(10);
    l1.addBack(30);

    l1.print();

    LinkedList l2(5);
    l2.addBack(15);
    l2.addBack(25);

    l2.print();
    
    LinkedList l3 = l1.merge(l2);


    l3.print();
    return 0;
}