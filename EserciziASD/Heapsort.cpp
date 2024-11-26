#include <iostream>
#include <fstream>
#include <vector>
#include <climits>
#include <string>

using namespace std;

class Heap{
    public:
        vector<int> A;
        int heapsize;
    public:
        Heap() : heapsize(0) {}
    
    void BuildMaxHeap(vector<int>& A){
        heapsize=A.size();
        for(int i=(A.size()/2)-1;i>=0;i--){
            MaxHeapify(A,i);
        }
    }
    
    void MaxHeapify(vector<int>& A, int i){
        int l=left(i);
        int r=right(i);
        int max;
        
        if(l<heapsize && A[l]>A[i]){
            max=l;
        }else{
            max=i;
        }
        if(r<heapsize && A[r]>A[max]){
            max=r;
        }
        if(max!=i){
            swap(A[i],A[max]);
            MaxHeapify(A,max);
        }
    }
    
    void Heapsort(vector<int>& A){
        BuildMaxHeap(A);
        for(int i=A.size()-1;i>=1;i--){
            swap(A[0],A[i]);
            heapsize--;
            MaxHeapify(A,0);
        }
    }
    
    
    void print(vector<int>& A){
        ofstream file("out.txt");
        for(auto v : A){
            file<< v <<endl;
        }
        file.close();
    }
    
    
    
    int parent(int i){return (i-1)/2;}
    int left(int i){return 2 * i + 1;}
    int right(int i){return 2 * i + 2;}
};



int main(){
    
    Heap hp;
    vector<int> V;
    
    fstream file1("heap.txt");
    string rigo;
    while(getline(file1,rigo)){
        V.push_back(stoi(rigo));
    }
    
    
    hp.Heapsort(V);
    hp.print(V);
    
    cout<<"Stampa vettore ordinato : "<<endl;
    for(auto x : V){
        cout<< x << endl;
    }
    
    return 0;
}