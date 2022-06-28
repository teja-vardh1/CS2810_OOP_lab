#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

template<typename T>
class Node{
    public:
    T x;
    Node<T>* next;
    Node<T>* prev;
    
    Node(T y){
        x = y;
    }
};

template<typename T>
class DLL{
    private:
    Node<T>* head = NULL;
    Node<T>* tail = NULL;
    
    public:
    void push_front(T y){
        Node<T>* n = new Node<T>(y);
        n->prev = NULL;
        n->next = head;
        if(head == NULL){
            tail = n;
            head = n;
            return;
        }
        head->prev = n;
        head = n;
    }
    
    void push_end(T y){
        Node<T>* n = new Node<T>(y);
        n->next = NULL;
        n->prev = tail;
        if(head == NULL){
            head = n;
            tail = n;
            return;
        }
        tail->next = n;
        tail = n;
    }
    
    T pop_front(){
        T y = head->x;
        if(head == tail){
            delete head;
            head = NULL;
            tail = NULL;
            return y;
        }
        Node<T>* n = head->next;
        delete head;
        n->prev = NULL;
        head = n;
        return y;
    }
    
    T pop_end(){
        T y = tail->x;
        if(head == tail){
            delete tail;
            head = NULL;
            tail = NULL;
            return y;
        }
        Node<T>* n = tail->prev;
        delete tail;
        n->next = NULL;
        tail = n;
        return y;
    }
    
    long int size(){
        if(head == NULL) return 0;
        if(head == tail) return 1;
        long int n = 0;
        Node<T>* p = head;
        while(p != NULL){
            p = p->next;
            n++;
        }
        return n;
    }
    
};

template<typename T>
class Stack{
    public:
    DLL<T> D;
    
    void Push(T y){
        D.push_front(y);
    }
    
    T Pop(){
        return D.pop_front();
    }
    
    T Top(){
        T y = D.pop_front();
        D.push_front(y);
        return y;
    }
    
    long int size(){
        return D.size();
    }
    
    bool Compare(T n){
        T y = D.pop_front();
        D.push_front(y);
        if(n > y) return true;
        else return false;
    }
    
};

template<typename T>
void Encryption(long int n){
    Stack<T> S;
    while(n--){
        T y;
        cin >> y;
        if(S.size() == 0){
            S.Push(y);
        }
        else {
            if(S.Compare(y)){
                S.Push(y);
            }
            else{
                while(S.size() != 0 && !S.Compare(y)){
                    T z = S.Pop();
                    cout << z;
                }
                S.Push(y);
            }
         }
    }
    
    while(S.size() != 0){
        T z1 = S.Pop();
        cout << z1;
    }
}

int main() {
    long int n;
    char t;
    cin >> n >> t;
    
    if(t == 'I') Encryption<int>(n);
    if(t == 'C') Encryption<char>(n);
    if(t == 'F') Encryption<float>(n);
    
    return 0;
}
