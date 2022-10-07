#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Node{
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

template <typename T>
class CircularLinkedList{
    private:
        Node<T>* cursor;
    
    public:
        CircularLinkedList(){
            cursor= NULL;
        }

        ~CircularLinkedList(){
            
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
            delete temp;
        }

        void removeBack(){
            if (empty()) throw "UnderFlowError";

            Node<T>* temp = cursor;
            if (temp->next == cursor){
                cursor = NULL;
            }
            else{
                Node<T>* trailer = temp->next;

                cursor = cursor->next;
                while (trailer->next != temp){
                    trailer = trailer->next;
                }
                trailer->next = cursor;
            }

            delete temp;
        }

        void display(string start = "", string nextPtr = " ", string endPtr = ""){
            if (cursor == NULL) throw "EmptyList";

            Node<T>* traverser = cursor->next;

            do{
                cout << start << traverser->value << nextPtr << endPtr;
                traverser = traverser->next;
            } while (traverser != cursor->next);
        }
};

class Song{
    private:
        string song_name;
        string artist_name;

    public:
        Song(){
            this->song_name = "";
            this->artist_name = "";
        }
        
        Song(string song_name , string artist_name){
            this->song_name = song_name;
            this->artist_name = artist_name;
        }

        friend ostream& operator << (ostream& out, const Song& obj){
            out << "\t" << obj.song_name;
            int no_tabs = 5 - obj.song_name.size()/8;
            for (int i = 0; i < no_tabs; i++) out << "\t";
            out << "|\t\t" << obj.artist_name;

            no_tabs = 4 - obj.artist_name.size()/8;
            for (int i = 0; i < no_tabs; i++) out << "\t";
            return out;
        }

        friend class Playlist;
};

class Playlist : private CircularLinkedList<Song>{
    private:
    public:
        using CircularLinkedList<Song>::removeFront;
        using CircularLinkedList<Song>::removeBack;

        Playlist() : CircularLinkedList<Song>(){}

        void add(string song, string artist){
            Song s(song, artist);
            addBack(s);
        }

        void show(){ 
            for (int i = 0; i < 97; i++){ cout << "-";}
            cout << endl;
            
            cout << "|\t\t\t Song\t\t\t|\t\t\t Artist \t\t|" << endl;
            
            for (int i = 0; i < 97; i++){ cout << "-";}
            cout << endl;
            
            this->display("|" , "|" , "\n"); 
            
            for (int i = 0; i < 97; i++){ cout << "-";}
            cout << endl;
        }
};

int main(){
    Playlist p1;
    p1.add("The end is where we begin" , "Thousand Foot Krutch");
    p1.add("Give Me Back My Life" , "Papa Roach");
    p1.add("Lucky One" , "Simple Plan");
    p1.add("Coming Home" , "Avenged Sevenfold");

    p1.show();
    p1.removeFront();
    p1.show();
}