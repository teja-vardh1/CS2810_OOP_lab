#include<bits/stdc++.h>

using namespace std;

class Dictionary{
    private:
    map<int,vector<string>> M;

    public:
    void buildDict(vector<string> words){   //initialises the map
        for(int i=0; i<words.size(); i++){
            M[words[i].length()].push_back(words[i]);
        }        
    }

    void addWordToDict(string word){    //adds the word to the dict.
        M[word.length()].push_back(word);
    }

    bool search(string target){     //searches for the target in the map
        if(M.empty()) return false;
        bool b ;
        auto it = M.find(target.length());
        if(it == M.end()){      //no words of size same as target are found
            return false;
        }
        else{
            vector<string> v = it->second;
            for(int i=0; i<v.size(); i++){
                b = true;
                string s = v[i];
                for(int i = 0; i<target.length(); i++){
                    if(target[i] != s[i]) b = false;
                }
                if(b == true) return true;   
            }
            return b;
        }
    }

    set<string> getWordsAfterReplace(string target){    
        set<string> s;
        if(M.empty()) return s;
        vector<string> k = M[target.length()];
        for(int i=0; i<k.size(); i++){
            int count = 0;      //measures no.of diff.characters b/w word and target
            string x = k[i];
            for(int i=0; i<target.length(); i++){
                if(target[i] != x[i]) count++;
            }
            if(count == 1 || count == 0) s.insert(x);
        }
        return s;
    }

    set<string> getWordsAfterSwap(string target){
        set<string> s;
        if(M.empty()) return s;
        for(int i=0; i<target.length()-1; i++){
            char x = target[i];
            char y = target[i+1];
            string str = target;
            str[i] = y;
            str[i+1] = x;       //str is the modified string after swapping
            if(search(str)) s.insert(str);      //if present, add to the set
        }
        return s;
    }

    int maxChangeableWord(){
        int count = 0;
        for(auto itr = M.begin(); itr != M.end(); itr++){
            vector<string> v = itr->second;
            for(int i=0; i<v.size(); i++){
                string x = v[i];
                set<string> s = getWordsAfterReplace(x);
                if(s.size() > count) count = s.size();
            }
        }
        return count-1; //word itself is counted, so remove it.
    }

    int maxSwappableWord(){
        int count = 0;
        for(auto itr = M.begin(); itr != M.end(); itr++){
            vector<string> v = itr->second;
            for(int i=0; i<v.size(); i++){
                string x = v[i];
                set<string> s = getWordsAfterSwap(x);
                if(s.size() > count) count = s.size();
            }
        }
        return count;
    }
};

int main(){
    int N;
    cin >> N;
    Dictionary D;
    vector<string> v;
    string s;
    while(N--){
        cin >> s;
        v.push_back(s);
    }
    D.buildDict(v);
    int Q;
    cin >> Q;
    while(Q--){
        int val;
        cin >> val; 
        string x;
        switch(val){
            case 1:{
                cin >> x;
                D.addWordToDict(x);
                break;
            }
            case 2:{
                cin >> x;
                if(D.search(x)) cout << "true" << endl;
                else cout << "false" << endl;
                break;
            }
            case 3:{
                cin >> x;
                set<string> y = D.getWordsAfterReplace(x);
                for(auto itr=y.begin(); itr!=y.end(); itr++){
                    cout << *itr << " ";
                }
                if(y.empty()) cout << -1 ;
                cout << endl;
                break;
            }
            case 4:{
                cin >> x;
                set<string> y = D.getWordsAfterSwap(x);
                for(auto itr=y.begin(); itr!=y.end(); itr++){
                    cout << *itr << " ";
                }
                if(y.empty()) cout << -1;
                cout << endl;
                break;
            }
            case 5:{
                cout << D.maxChangeableWord() << endl;
                break;
            }
            case 6:{
                cout << D.maxSwappableWord() << endl;
                break;
            }
        }
    }

    return 0;
}
