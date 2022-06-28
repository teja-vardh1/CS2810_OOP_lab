#include<bits/stdc++.h>

using namespace std;

template<typename T>
class Node{
public:
    T key;
    T value;
    int level;
    Node<T>* next;
    Node<T>* prev;
    Node<T>* up;
    Node<T>* down;
    Node(T k,T v){
        key = k;
        value = v;
        next = NULL;
        prev = NULL;
        up = NULL;
        down = NULL;
        level = 0;
    }
};

template<typename T>
class skiplist{
public:

    Node<T>* ptr[11][2];

    void skiplist_do(){
        for(int i=0; i<=10; i++){
            ptr[i][0]->next = ptr[i][1];
            ptr[i][0]->level = i;
            ptr[i][1]->prev = ptr[i][0];
            ptr[i][1]->level = i;
            if(i>0){
                ptr[i][0]->down = ptr[i-1][0];
                ptr[i][1]->down = ptr[i-1][1];
            }
            if(i<10){
                ptr[i][0]->up = ptr[i+1][0];
                ptr[i][1]->up = ptr[i+1][0];
            }
        }
    }

    virtual void insert(T k,T v){
        Node<T>* n = new Node<T>(k,v);
        Node<T>* bf = search(k);
        Node<T>* af = bf->next;
        bf->next = n;
        n->prev = bf;
        n->next = af;
        af->prev = n;
        n->level = 0;
        
        for(int i=0; i<10; i++){
            srand(time(0));
            int rem = rand()%2;
            if(rem == 0) break;
            Node<T>* p = new Node<T>(k,v);
            n->up = p;
            p->down = n;
            p->level = n->level+1;
            Node<T>* p1 = bf;
            while(1){
                if(p1->up != NULL){
                    p1 = p1->up;
                    break;
                }
                p1 = p1->prev;
            }
            Node<T>* p2 = p1->next;
            p1->next = p;
            p->prev = p1;
            p->next = p2;
            p2->prev = p;
        }
    }


    virtual void delete_me(T k){
        Node<T>* x = search(k);
        if(x->key != k) return;
        while(x != NULL){
            Node<T>* bf = x->prev;
            Node<T>* af = x->next;
            bf->next = af;
            af->prev = bf;
            x = x->up;
            delete x;
        }
    }

    Node<T>* search(T k){
        Node<T>* n = ptr[10][0];
        while(1){
            if(n->next->key > k){
                if(n->level == 0) break;
                n = n->down;
            }
            else n = n->next;
        }
        return n;
    }
};

template<typename T>
class dictionary : public skiplist<T> {
    public:

    void empty(){
        if(skiplist<T>::ptr[0][0]->next == skiplist<T>::ptr[0][1]){
            cout << "True" << endl;
        }
        else{
            cout << "False" << endl;
        }
    }

    void insert(T k,T v){
        skiplist<T>::insert(k,v);
    }

    void delete_me(T k){
        skiplist<T>::delete_me(k);
    }

    void find(T k){
        Node<T>* n = skiplist<T>::search(k);
        if(n->key == k){
            cout << n->value << endl;
        }
        else cout << "NOT FOUND" <<endl;
    }

    void size(){
        Node<T>* x = skiplist<T>::ptr[0][0];
        int size = 0;
        while(x->next != NULL){
            size++;
            x = x->next;
        }
        cout << size-1 << endl;
    }
};

template<typename T>
void functioni(){
    
}

int main(){
    string x;
    cin >> x;
    if(x == "STRINGDICT"){
        dictionary<string> d;
        for(int i=0; i<=10; i++){
            d.ptr[i][0] = new Node<string>("?","teja");
            d.ptr[i][1] = new Node<string>("}","vardhan");
        }
        d.skiplist_do();
        int p;
        cin >> p;
        while(p--){
            string s;
            cin >> s;
            if(s == "INSERT"){
                string k,v;
                cin >> k >> v;
                d.insert(k,v);
            }
            if(s == "ISEMPTY"){
                d.empty();
            }
            if(s == "DELETE"){
                string k;
                cin >> k;
                d.delete_me(k);
            }
            if(s == "FIND"){
                string k;
                cin >> k;
                d.find(k);
            }
            if(s == "SIZE"){
                d.size();
            }
        }
    }
    if(x == "INTEGERDICT"){
        dictionary<int> d;
        for(int i=0; i<=10; i++){
            d.ptr[i][0] = new Node<int>(-1000000,0);
            d.ptr[i][1] = new Node<int>(1000000,0);
        }
        d.skiplist_do();
        int p;
        cin >> p;
        while(p--){
            string s;
            cin >> s;
            if(s == "INSERT"){
                int k,v;
                cin >> k >> v;
                d.insert(k,v);
            }
            if(s == "ISEMPTY"){
                d.empty();
            }
            if(s == "DELETE"){
                int k;
                cin >> k;
                d.delete_me(k);
            }
            if(s == "FIND"){
                int k;
                cin >> k;
                d.find(k);
            }
            if(s == "SIZE"){
                d.size();
            }
        }
    }
    return 0;
}
