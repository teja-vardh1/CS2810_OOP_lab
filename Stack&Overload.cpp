#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Node{
public:
    int x;
    Node* next;
};

class Stack{
private:
    Node* top = NULL;           //points to top element of the stack
    
public:
    void Push(int y){           // pushes the integer y into the stack
        Node* p = new Node();
        p->x = y;
        if(top == NULL){
            p->next = NULL;
            top = p;
            return;
        }
        p->next = top;
        top = p;
    }
    
    int Pop(){                  //Pop the last element inserted and returns it
        if(top == NULL) return -1;  
        Node* p = top;
        int x = top->x;
        top = top->next;
        delete p;
        return x;
    }
    
    int Top(){                  // return the top element 
        if(top == NULL) return -1;
        return top->x;
    }
    
    int isEmpty(){              //checks whether stack is empty
        if(top == NULL) return 1;
        return 0;
    }
};

class Graph{
        
public:

    int a[100][100];            //adjacency matrix
    int n;                      //no.of vertices
    int visited[100] = {0};     //to keep a check of visited vertices
    int flag;

    Graph(int n){               //constructor: intialises adjacency matrix to 0 & gives a value to n
        this->n = n;
        for(int i=0; i<n; i++){
            for(int j=0; j<n; j++){
                a[i][j] = 0;
            }
        }
    }
    
    void operator += (pair<int,int> p){     //adds an edge to the graph
        int u = p.first;
        int v = p.second;
        a[u][v] = 1;
        a[v][u] = 1;
    }
    
    void operator -= (pair<int,int> p){     //deletes an edge from the graph
        int u = p.first;
        int v = p.second;
        a[u][v] = 0;
        a[v][u] = 0;
    }
    
    int checkFlag(int v, int u){   //checks if there is a path from v to flag
        for(int i=0; i<u ; i++){
            if(a[v][i] == 1){
                if(i == flag) return 1;
                if(checkFlag(i,v) == 1) return 1;
            }
        }
        for(int i=u+1; i<n ; i++){
            if(a[v][i] == 1){
                if(i == flag) return 1;
                if(checkFlag(i,v) == 1) return 1;
            }
        }
        return 0;
    }                               //parameter u is passed to avoid infinte loop
    
    int detectCycle(){              //detects if there is a cycle in the graph
        int ret = 0;
        for(int i=0; i<n; i++){
            flag = i;
            int j = checkFlag(i,i);
            if(j == 1){
                ret = 1;
                break;
            }
        }
        for(int i=0; i<n; i++) visited[i] = 0;
        return ret;
    }
    
    int reach(int u, int v){        //checks if there is a path from u to v
        int ret = 0;
        Stack s;
        s.Push(u);
        int current;
        visited[u] = 1;
        while(1){
            current = s.Pop();
            for(int i=0; i<n; i++){
                if(a[current][i] == 1 && visited[i] == 0){
                    visited[i] = 1;
                    if(i == v){
                        ret = 1;
                        break;
                    }
                    s.Push(i);
                }
            }
            if(s.isEmpty() == 1) break;
            if(ret == 1) break;
        }
        for(int i=0; i<n; i++) visited[i] = 0;
        return ret;
    }
    
};  

ostream & operator << (ostream &out, Graph &G){     //to print adj.matrix
    for(int i=0; i<G.n; i++){
        for(int j=0; j<G.n; j++){
            out << G.a[i][j] << " ";
        }
        out << endl;
    }
    return out;
}
        
int main() {
    int Q;
    cin >> Q;
    Stack S;
    
    while(Q--){
        string s;
        cin >> s;

        if(s == "push"){
            int x;
            cin >> x;
            S.Push(x);
        }

        if(s == "pop"){
            std::cout << S.Pop() << endl;
        }

        if(s ==  "top"){
            std::cout << S.Top() << endl;
        }

        if(s == "empty"){
            std::cout << S.isEmpty() << endl;
        }
    }
    
    
    int n;
    cin >> n;
    int m;
    cin >> m;
    
    Graph G(n);
    
    while(m--){
        string s;
        cin >> s;
        
        if(s == "add"){
            int u,v;
            cin >> u >> v;
            pair <int,int> p = {u,v};
            G += p;
        }
        
       if(s == "del"){
            int u,v;
            cin >> u >> v;
            pair <int,int> p = {u,v};
            G -= p;
        }
                
        if(s == "cycle"){
            std::cout << G.detectCycle() << endl;
        }
                
        if(s == "print"){
            cout<<G;
        }
                
        if(s == "reach"){
            int u,v;
            cin >> u >> v;
            std::cout << G.reach(u,v) << endl;
        }
    }
    
    return 0;
}
