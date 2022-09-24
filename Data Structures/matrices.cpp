#include <iostream>

using namespace std;

class matrix{
    public:
        virtual int get(int x, int y) const = 0;
        virtual void set(int x, int y, int value) = 0;
        virtual void print_matrix() const = 0;
};

class diagonal_matrix : public matrix{
    private:
        int* arr;
        int size;

    public:
        diagonal_matrix(int n){
            if (n < 0) throw "Bad initialisation";
            this->size = n;
            this->arr = new int[size];

            for (int i = 0; i < n; i++){
                cout << "Please enter the element at position " << i+1 << "," << i+1 << " ";
                cin >> arr[i];
            }
        }

        int get(int x, int y) const override{
            if (x < 0 || x > size || y < 0 || y > size) throw "ArrayOutOfBoundsException";
            if (x != y) return 0;
            return arr[x-1];
        }

        void set(int x, int y, int value) override{
            if (x < 0 || x > size || y < 0 || y > size) throw "ArrayOutOfBoundsException";
            if (x!=y && value!=0) throw "ValueError : Value must be 0";
            arr[x-1] = value;
        }

        void print_matrix() const override{
            cout << "[" << endl;
            for (int i = 0; i < size; i++){
                cout << "[";
                for (int j = 0; j < size; j++){
                    cout << this->get(i+1 , j+1); 
                    if (j != size-1) cout << " \t\t";
                }
                cout << "]" << endl;
            }
            cout << "]" << endl;
        }
};

class lower_triangular_matrix : public matrix{
    private:
        int* arr;
        int size;

    public:
        lower_triangular_matrix(int n){
            if (n < 0) throw "Bad initialisation";
            this->size = n;
            this->arr = new int[size*(size+1)/2];

            for (int i = 0; i < size; i++){
                for (int j = 0; j < size; j++){
                    if (i >= j){
                        cout << "Please enter the element at position " << i+1 << "," << j+1 << " ";
                        cin >> arr[i*(i+1) / 2 + j];
                    }
                }
            }
        }

        int get(int x, int y) const override{
            if (x < 0 || x > size || y < 0 || y > size) throw "ArrayOutOfBoundsException";
            if (x < y) return 0;
            return arr[x*(x-1)/2  + (y-1)];
        }

        void set(int x, int y, int value) override{
            if (x < 0 || x > size || y < 0 || y > size) throw "ArrayOutOfBoundsException";
            if (x<y && value!=0) throw "ValueError : Value must be 0";
            arr[x*(x-1)/2  + (y-1)] = value;
        }

        void print_matrix() const override{
            cout << "[" << endl;
            for (int i = 0; i < size; i++){
                cout << "[";
                for (int j = 0; j < size; j++){
                    cout << this->get(i+1 , j+1); 
                    if (j != size-1) cout << " \t\t";
                }
                cout << "]" << endl;
            }
            cout << "]" << endl;
        }
};

class upper_triangular_matrix : public matrix{
    private: 
        int* arr;
        int size;
    
    public:
        upper_triangular_matrix(int n){
            if (n < 0) throw "Bad initialisation";
            this->size = n;
            this->arr = new int[size*(size+1)/2];

            for (int i = 0; i < size; i++){
                for (int j = 0; j < size; j++){
                    if (i <= j){
                        cout << "Please enter the element at position " << i+1 << "," << j+1 << " ";
                        cin >> arr[i*size + (j-i)];
                    }
                }
            }
        }

        int get(int x, int y) const override{
            if (x < 0 || x > size || y < 0 || y > size) throw "ArrayOutOfBoundsException";
            if (x > y) return 0;
            return arr[(x-1)*size + (y-x)];
        }

        void set(int x, int y, int value) override{
            if (x < 0 || x > size || y < 0 || y > size) throw "ArrayOutOfBoundsException";
            if (x>y && value!=0) throw "ValueError : Value must be 0";
            arr[(x-1)*size + (y-x)] = value;
        }

        void print_matrix() const override{
            cout << "[" << endl;
            for (int i = 0; i < size; i++){
                cout << "[";
                for (int j = 0; j < size; j++){
                    cout << this->get(i+1 , j+1); 
                    if (j != size-1) cout << " \t\t";
                }
                cout << "]" << endl;
            }
            cout << "]" << endl;
        }

};

class symmetric_matrix : public matrix{
    private:
        int* arr;
        int size;
    
    public:
        symmetric_matrix(int n){
            if (n < 0) throw "Bad initialisation";
            this->size = n;
            this->arr = new int[size*(size+1)/2];

            for (int i = 0; i < size; i++){
                for (int j = 0; j < size; j++){
                    if (i <= j){
                        if (i == j){
                             cout << "Please enter the element at position " << i+1 << "," << j+1 << " ";
                        }
                        else{
                            cout << "Please enter the element at position " << i+1 << "," << j+1 << " and " << 
                            j+1 << "," << i+1 << " ";
                        }
                        cin >> arr[i*size + (j-i)];
                    }
                }
            }
        }

        int get(int x, int y) const override{
            if (x < 0 || x > size || y < 0 || y > size) throw "ArrayOutOfBoundsException";
            if (x > y) swap(x,y);
            return arr[(x-1)*size + (y-x)];
        }

        void set(int x, int y, int value) override{
            if (x < 0 || x > size || y < 0 || y > size) throw "ArrayOutOfBoundsException";
            if (x>y) swap(x,y);
            arr[(x-1)*size + (y-x)] = value;
        }

        void print_matrix() const override{
            cout << "[" << endl;
            for (int i = 0; i < size; i++){
                cout << "[";
                for (int j = 0; j < size; j++){
                    cout << this->get(i+1 , j+1); 
                    if (j != size-1) cout << " \t\t";
                }
                cout << "]" << endl;
            }
            cout << "]" << endl;
        }
};

class tridiagonal_matrix : public matrix{
    private:
        int size;
        int* arr;
    
    public:
        tridiagonal_matrix(int n){
            if (n < 0) throw "Bad initialisation";
            this->size = n;
            this->arr = new int[3*size - 2];

            for (int i = 0; i < size; i++){
                for (int j = 0; j < size; j++){
                    if (abs(i-j) < 2){
                        cout << "Please enter the value at position " << i+1 << "," << j+1 << " ";
                        cin >> arr[i*3 + i-j];
                    }
                }
            }
        }

        int get(int x, int y) const override{
            if (x < 0 || x > size || y < 0 || y > size) throw "ArrayOutOfBoundsException";
            if (abs(x-y) > 1) return 0;
            return arr[(x-1)*3 + x-y];
        }

        void set(int x, int y, int value) override{
            if (x < 0 || x > size || y < 0 || y > size) throw "ArrayOutOfBoundsException";
            if (abs(x-y) > 1 && value != 0) throw "ValueError : Value must be 0";
            arr[(x-1)*3 + x-y] = value;
        }

        void print_matrix() const override{
            cout << "[" << endl;
            for (int i = 0; i < size; i++){
                cout << "[";
                for (int j = 0; j < size; j++){
                    cout << this->get(i+1 , j+1); 
                    if (j != size-1) cout << " \t";
                }
                cout << "]" << endl;
            }
            cout << "]" << endl;
        }
};

int main(){
    int c1, c2;         // Store users choice
    int n;              // Store order of matrix
    int x,y,value;      // Variables for handling matrix operations
    bool run = true;    // Store running state of program 
    matrix *a;          // Store the matrix object (abstract parent class)

    cout << "Please enter which type of matrix do you want ?" << endl;
    cout << "1. Diagonal Matrix (Chosen by default)" << endl;
    cout << "2. Symmetric Matrix" << endl;
    cout << "3. Upper triangular Matrix" << endl;
    cout << "4. Lower triangular Matrix" << endl;
    cout << "5. Tridiagonal Matrix" << endl;
    cout << "Please enter your choice (1/2/3/4/5) ";
    cin >> c1;
    cout << "Please enter the size of the matrix ";
    cin >> n;
    cout << endl;
    switch(c1){
        case 1:
            a = new diagonal_matrix(n);
            break;
        
        case 2:
            a = new symmetric_matrix(n);
            break;
        
        case 3:
            a = new upper_triangular_matrix(n);
            break;
        
        case 4:
            a = new lower_triangular_matrix(n);
            break;
        
        case 5:
            a = new tridiagonal_matrix(n);
            break;

        default:
            a = new diagonal_matrix(n);
    }

    
    while (run){
        try{
            cout << "Welcome to the main menu" << endl;
            cout << "1. Change the type of the matrix" << endl;
            cout << "2. Access certain element of the matrix" << endl;
            cout << "3. Change value of certain element of the matrix" << endl;
            cout << "4. Print the matrix" << endl;
            cout << "5. Exit the menu" << endl;

            cout << "Please enter your choice (1/2/3/4) ";
            cin >> c2;
            cout << endl;

            switch (c2)
            {
            case 1:
                cout << "Please enter which type of matrix do you want ?" << endl;
                cout << "1. Diagonal Matrix (Chosen by default)" << endl;
                cout << "2. Symmetric Matrix" << endl;
                cout << "3. Upper triangular Matrix" << endl;
                cout << "4. Lower triangular Matrix" << endl;
                cout << "5. Tridiagonal Matrix" << endl;
                cout << "Please enter your choice (1/2/3/4/5) ";
                cin >> c1;
                cout << "Please enter the size of the matrix ";
                cin >> n;
                switch(c1){
                    case 1:
                        *a = diagonal_matrix(n);
                        break;
                    
                    case 2:
                        *a = symmetric_matrix(n);
                        break;
                    
                    case 3:
                        *a = upper_triangular_matrix(n);
                        break;
                    
                    case 4:
                        *a = lower_triangular_matrix(n);
                        break;
                    
                    case 5:
                        *a = tridiagonal_matrix(n);
                        break;

                    default:
                        continue;
                }
                break;

            case 2:
                cout << "Please enter the coordinates of the element you want to access ";
                cin >> x >> y;
                x = a->get(x,y);
                cout << "Element at positon " << x << " " << y << " = " << x << endl;
                break;
            
            case 3:
                cout << "Please enter the coordinates of the element you want to change ";
                cin >> x >> y;
                cout << "Please enter the new value ";
                cin >> value; 
                a->set(x,y,value);
                break;
            
            case 4:
                cout << "Your matrix is " << endl;
                a->print_matrix();
                break;
            
            case 5:
                run = false;
                break;

            default:
                cout << "Please enter a valid choice " << endl;
            }
            cout << endl << endl;
        }
    
        catch (const char* exp){
            cout << "Exception occurred : " << exp << endl << endl;
        }
    }
    return 0;
}