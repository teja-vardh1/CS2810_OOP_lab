#include <iostream>
#include <string>
using namespace std;

class Book{
public:
    string title;
    string author;
    int year;
    int price;
    Book* next;
    Book(string title, string author, int year, int price){
        this->title = title;
        this->author = author;
        this->year = year;
        this->price = price;
    }
    void print(){
        cout << title << "," << author << "," << year << "," << price << endl;
    }
};

class Bookshelf{
private:
    virtual void removeBook() = 0;

protected:
    Book* start = NULL;
    Book* end = NULL;
    bool checkEmpty(){
        if(start == NULL) return true;
        return false;
    }
};

class VerticalBookshelf: public Bookshelf{
public:
    void addBook(string title, string author, int year, int price){
        Book* b = new Book(title, author, year, price);
        b->next = start;
        start = b;
    }

    void removeBook(){
        if(start == NULL){
            cout << "e" << endl;
            return;
        }
        Book* b = start->next;
        delete start;
        start = b;
    }

    void list(){
        Book* b = start;
        if(b == NULL){
            cout << "e" << endl;
            return;
        }
        while(b != NULL){
            b->print();
            b = b->next;
        }
    }

    void findCheap(){
        if(start == NULL){
            cout << "e";
            return;
        }
        int min = start->price;
        Book* b = start;
        while(b != NULL){
            if(b->price > min){
                cout << min ;
            }
            else{
                cout << "-1" ;
                min = b->price;
            }
            b = b->next;
            if(b != NULL){
                cout << ",";
            }
        }
    }

    void reverseUnique(){
        if(start == NULL || start->next == NULL) return;
        Book* b1 = start;
        Book* b2 = start;
        while(b1 != NULL){
            while(b2->next != NULL){
                if(b1->title == b2->next->title && b1->author == b2->next->author && b1->year == b2->next->year && b1->price == b2->next->price){
                    Book* b3 = b2->next;
                    b2->next = b3->next;
                    delete b3;
                    continue;
                }
                b2 = b2->next;
            }
            b1 = b1->next;
            b2 = b1;
        }
        VerticalBookshelf v2;
        Book* b = start;
        while(b != NULL){
            v2.addBook(b->title,b->author,b->year,b->price);
            b = b->next;
        }
        start = v2.start;
    }
};

class HorizontalBookshelf: public Bookshelf {
public:

    void addBook(string title, string author, int year, int price){
        Book* b = new Book(title, author, year, price);
        end = start;
        if(end == NULL){
            end = b;
            start = b;
            return;
        }
        while(end->next != NULL){
            end = end->next;
        }
        end->next = b;
        end = b;
    }

    void removeBook(){
        if(start == NULL){
            cout << "e" << endl;
            return;
        }
        Book* b = start->next;
        delete start;
        start = b;
    }

    void list(){
        Book* b = start;
        if(b == NULL){
            cout << "e" << endl;
            return;
        }
        while(b != NULL){
            b->print();
            b = b->next;
        }
    }

    void findCheap(){
        if(start == NULL){
            cout << "e";
            return;
        }
        int min = start->price;
        Book* b = start;
        while(b != NULL){
            if(b->price > min){
                cout << min ;
            }
            else{
                cout << "-1" ;
                min = b->price;
            }
            b = b->next;
            if(b != NULL){
                cout << ",";
            }
        }
    }

    void reverseUnique(){
        if(start == NULL || start->next == NULL) return;
        Book* b1 = start;
        Book* b2 = start;
        while(b1 != NULL){
            while(b2->next != NULL){
                if(b1->title == b2->next->title && b1->author == b2->next->author && b1->year == b2->next->year && b1->price == b2->next->price){
                    Book* b3 = b2->next;
                    b2->next = b3->next;
                    delete b3;
                    continue;
                }
                b2 = b2->next;
            }
            b1 = b1->next;
            b2 = b1;
        }
        HorizontalBookshelf h2;
        Book* b = start;
        while(b != NULL){
            Book* bk = new Book(b->title, b->author, b->year, b->price);
            if(h2.start == NULL){
                h2.end = bk;
            }
            bk->next = h2.start;
            h2.start = bk;
            b = b->next;
        }
        start = h2.start;
        end = h2.end;
    }
};

int main(){
    int Q;
    cin >> Q;
    VerticalBookshelf V;
    HorizontalBookshelf H;
    while(Q--){
        string command;
        cin >> command;

        if(command == "ADD"){
            string x;
            cin >> x;
            string title, author;
            int year, price;
            cin >> title >> author >> year >> price;
            if(x == "v"){
                V.addBook(title,author,year,price);
            }
            if(x == "h"){
                H.addBook(title,author,year,price);
            }
        }

        if(command == "REMOVE"){
            int n;
            string x;
            cin >> n >> x;
            if(x == "v"){
                while(n--){
                    V.removeBook();
                }
            }
            if(x == "h"){
                while(n--){
                    H.removeBook();
                }
            }
        }

        if(command == "LIST"){
            string x;
            cin >> x;
            if(x == "v"){
                V.list();
            }
            if(x == "h"){
                H.list();
            }
        }

        if(command == "FINDC"){
            string x;
            cin >> x;
            if(x == "v"){
                V.findCheap();
            }
            if(x == "h"){
                H.findCheap();
            }
            cout << endl;
        }

        if(command == "REVUNI"){
            string x;
            cin >> x;
            if(x == "v"){
                V.reverseUnique();
            }
            if(x == "h"){
                H.reverseUnique();
            }
        }
    }

    return 0;
}
