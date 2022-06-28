#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Matrix {
    private:
        int rows;
        int columns;
        int** mat;
        
    public:
    Matrix(){
        rows = 0;
        columns = 0;
        mat = NULL;
    }
    
    Matrix(int row, int column){
        rows = row;
        columns = column;
        mat = new int*[rows];
        for(int i=0; i<rows; i++){
            *(mat+i) = new int[columns];
        }
        for(int i = 0; i<row; i++){
            for(int j = 0; j<column; j++){
                setValue(i+1,j+1,0); 
            }
        }
    }
    
    Matrix(int row, int column, int** matrix){
        rows = row;
        columns = column;
        mat = matrix;
    }
    
    void setValue(int row,int col,int val){
        row = row - 1;
        col = col - 1;
        *(*(mat+row)+col) = val;
    }
    
    int getValue(int row,int col){
        row = row - 1;
        col = col - 1;
        return *(*(mat+row)+col);
    }
    
    int getNoRows(){
        return rows;
    }
    
    int getNoColumns(){
        return columns;
    }
    
    void printSpiral(){
        int startR = 0;
        int startC = 0;
        int endR = rows - 1;
        int endC = columns - 1;
        while(startR < endR && startC < endC){
            PrintMe(startR , startC, endR, endC);
            startR++;
            startC++;
            endR--;
            endC--;
        }
        if(startR == endR){
            for(int i= startC; i <= endC; i++){
                cout << getValue(startR+1,i+1) << " ";
            }
        }
        else{
            if(startC == endC){
                for(int i= startR; i <= endR; i++){
                    cout << getValue(i+1,startC+1) << " ";
                }
            }
        }
    }
    
    void PrintMe(int sR, int sC, int eR, int eC){
        for(int i = sC; i <= eC; i++){
            cout << getValue(sR+1,i+1) << " ";
        }
        for(int i = sR+1; i <= eR; i++){
            cout << getValue(i+1,eC+1) << " ";
        }
        for(int i = eC-1; i >= sC; i--){
            cout << getValue(eR+1,i+1) << " ";
        }
        for(int i = eR-1; i >= sR+1; i--){
            cout << getValue(i+1,sC+1) << " ";
        }
    }
    
    int trace(){
        if(rows != columns || rows == 0){
            return -1;
        }
        
        int n = rows;
        int trace = 0;
        for(int i=0; i<n; i++){
            trace = trace + getValue(i+1,i+1);
        }
        return trace;
    }
    
    bool checkTriangular(){
        if(rows != columns || rows == 0){
            return false;
        }
        int n = rows;
        if(n == 1) return true;
        if(getValue(1,2) == 0){
            for(int i = 1; i<=n; i++){
                for(int j = i+1; j<=n; j++){
                    if(getValue(i,j) != 0) return false;
                }
            }
            return true;
        }
        else{
            for(int i = 1; i<=n; i++){
                for(int j = 1; j<i; j++){
                    if(getValue(i,j) != 0) return false;
                }
            }
            return true;
        }
    }
    
    bool isSpecialMatrix(){
        int sum = 0;
        for(int j=1; j<=columns; j++){
            sum += getValue(1,j);
        }
        
        int check = 0;
        for(int i=1; i<=rows; i++){
            for(int j=1; j<=columns; j++){
                check += getValue(i,j);
            }
            if(check != sum) return false;
            check = 0;
        }
        for(int i=1; i<=columns; i++){
            for(int j=1; j<=rows; j++){
                check += getValue(j,i);
            }
            if(check != sum) return false;
            check = 0;
        }
        return true;
    }
    
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */ 
    
    int n,m;
    cin >> n >> m;
    
    
    int ** arr = new int*[n];
    for(int i=0; i<n; i++){
        *(arr+i) = new int[m];
    }
    
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            cin >> *(*(arr+i)+j);
        }
    }
    
    Matrix M(n,m,arr);
    
    int Q;
    cin >> Q;
    
    while(Q--){
        int cmd;
        cin >> cmd;
        switch(cmd){
            case 1:{
                M.printSpiral();
                cout << endl;
                break;
            }
            case 2:{
                cout << M.trace() << endl;
                break;
            }
            case 3:{
                if(M.checkTriangular())
                    cout << "true" << endl;
                
                else
                    cout << "false" << endl;
                
                break;
            }
            case 4:{
                if(M.isSpecialMatrix())
                    cout << "true" << endl;
                
                else
                    cout << "false" << endl;
                
                break;
            }
        }
    }
    
    return 0;
}
