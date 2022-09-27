#include <iostream>

using namespace std;

class doubleLinkNode{
    private:
        int value;
        doubleLinkNode* next;
        doubleLinkNode* prev;

    public:
        doubleLinkNode(){
            next = prev = NULL;
        }

        doubleLinkNode(int value){
            this->value = value;
            this->next = this->prev = NULL;
        }

        friend class doublyLinkedList;
};

class doublyLinkedList{
    private:
        doubleLinkNode* header;
        doubleLinkNode* trailer;

    public:
        doublyLinkedList(){
            this->header = new doubleLinkNode();
            this->trailer = new doubleLinkNode();
            this->header->next = this->trailer;
            this->trailer->prev = this->header;
        }

        void addFront(int value){
            doubleLinkNode* temp = new doubleLinkNode(value);
            temp->next = header->next;
            temp->prev = header;
            header->next->prev = temp;
            header->next = temp;
        }

        void print() const{
            doubleLinkNode* temp = this->header->next;
            while (temp != this->trailer){
                cout << temp->value << " ";
                temp = temp->next;
            }
        }
};

int main(){
    doublyLinkedList dll;
    dll.addFront(4);
    dll.addFront(5);
    dll.addFront(6);
    dll.print();
}