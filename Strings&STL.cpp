#include <bits/stdc++.h>

using namespace std;

class Node{
    private:
    bool isEnd = false;
    vector<Node *> next;

    public:
    Node(){
        next.resize(26,NULL);
    }

    Node* Access_next(int j){
        return this->next[j];
    }

    void changeisend(){
        isEnd = true;
    }

    bool Isend(){
        return isEnd;
    }

    void createnode(Node* ptr, int j){
        ptr->next[j] = new Node();
    }
};

class Sentence{
    Node* root = new Node();
    
    public:
    void AddWord(string word){
        char c;
        Node* current = root;
        for(int i=0; i<word.size(); i++){
            c = word[i];
            int j = c-97;
            if(current->Access_next(j) == NULL){
                current->createnode(current, j);
            }
            current = current->Access_next(j);
        }
        current->changeisend();
    }

    int PrintModified(string word){
        int flag = 0;
        char c;
        Node* current = root;
        int k = word[0]-97;
        if(root->Access_next(k) == NULL){
            return word.size();
        }
        int i;
        for(i=0; i<word.size(); i++){
            c = word[i];
            int j = c-97;
            if(current->Access_next(j) == NULL){
                if(flag == 0) return word.size();
                else return flag;
            }
            if(current->Access_next(j)->Isend()){
                flag = i+1;
            }
            current = current->Access_next(j);
        }
        if(flag!=NULL) return flag;
        else return i;
    }
};


int main() {
    int p;
    cin >> p;
    string prefix[p];
    Sentence S;

    for(int i=0; i<p; i++){
        cin >> prefix[i];
        S.AddWord(prefix[i]);
    }

    int n;
    cin >> n;
    string word[n];
    for(int i=0; i<n; i++){
        cin >> word[i];
    }
    
    for(int i=0; i<n; i++){
        int j = S.PrintModified(word[i]);
        for(int k=0; k<j; k++){
            cout << word[i][k];
        }
        cout << " ";
    }
    return 0;
}
