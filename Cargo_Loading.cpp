#include<bits/stdc++.h>

using namespace std;

class base{
    public:
    int optimum;
    int n;

    virtual int findMe(int k){
        return 0;
    };
};

class derived:public base{
    public:
    vector<int> r;
    vector<int> w;
    int W;
    int K[10000] = {-1};
    virtual int findMe(int k){
        if(k == 0){
            K[0] = 0;
            return 0;
        }
        int max, j;
        max = 0;
        for(int i=0; i<w.size(); i++){
            if(w[i] <= k){
                j = K[k-w[i]];
                if(r[i] + j > max) max = r[i] + j;
            }
        }
        K[k] = max;
        return max;
    }
};

int main(){
    int n,W;
    cin >> W >> n;
    vector<int> r;
    for(int i=0; i<n; i++){
        int x;
        cin >> x;
        r.push_back(x);
    }
    vector<int> w;
    for(int i=0; i<n; i++){
        int x;
        cin >> x;
        w.push_back(x);
    }
    derived D;
    D.n = n;
    D.W = W;
    D.r = r;
    D.w = w;
    for(int j=0; j<W; j++){
        D.K[j] = D.findMe(j);
    }
    D.optimum = D.findMe(W);
    cout << D.optimum << endl;

}
