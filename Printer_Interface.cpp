#include <iostream>

using namespace std;

template<typename T>
class Queue {
    private:
    T Q[100];
    int start = -1;
    int end = -1;
    
    public:
    void enqueue(T x){
        Q[end+1] = x;
        end++;
        if(start == -1) start = 0;
    }
    
    T dequeue(){
        T x = Q[start];
        start++;
        return x;
    }
    
    int size(){
        if(start == -1) return 0;
        return end-start+1;
    }
    
    bool isEmpty(){
        if(start == -1 || end < start) return true;
        return false;
    }
    
    /*void print(){
        if(start == -1){
            cout << endl;
            return;
        }
        for(int i=start; i<=end; i++){
            cout << Q[i] << endl;
        }
    }*/
};

template<typename T>
class Printer{
    private:
    Queue<T> Q;
    int capacity;
    int ink;
    
    public:
    class Insufficient{
        public:
        string str;
        Insufficient(string reason){
            str = reason;
        }
    };
    
    class PrinterBusy{
        public:
        string str;
        PrinterBusy(string reason){
            str = reason;
        }
    };
    
    class NoDocument{
        public:
        string str;
        NoDocument(string reason){
            str = reason;
        }
    };
    
    Printer(int capacity, int ink){
        this->capacity = capacity;
        this->ink = ink;
    }
    
    void addDocument(T doc){
        if(Q.size() == capacity) throw PrinterBusy("PRINTER_BUSY");
        Q.enqueue(doc);
    }
    
    void printDocument(){
        if(Q.isEmpty()) throw NoDocument("NO_DOCUMENT");
        if(ink == 0) throw Insufficient("INSUFFICIENT_INK");
        ink--;
        cout << Q.dequeue() << endl;
    }
    
    void fillInk(int ink){
        this->ink = ink;
    }
    
};

template<typename T>
void Mission(int m, int n, int q){
    Printer<T> P(m,n);
    while(q--){
        int op;
        cin >> op;
        switch(op){
            case 1:{
                T x;
                cin >> x;
                try{
                    P.addDocument(x);
                }
                catch(typename Printer<T>::PrinterBusy){
                    cout << "PRINTER_BUSY" << endl;
                }
                break;
            }
                
            case 2:{
                try{
                    P.printDocument();
                }
                catch(typename Printer<T>::NoDocument){
                    cout << "NO_DOCUMENT" << endl;
                }
                catch(typename Printer<T>::Insufficient){
                   cout << "INSUFFICIENT_INK" << endl;
                }
                break;
            }
                
            case 3:{
                int x;
                cin >> x;
                P.fillInk(x);
                break;
            }
        }
    }
}

int main() {
    int m,n,q;
    char t;
    cin >> m >> n >> t >> q;
    if(t == 'I') Mission<int>(m,n,q);
    if(t == 'C') Mission<char>(m,n,q);
    if(t == 'F') Mission<float>(m,n,q);
    return 0;
}
