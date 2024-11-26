#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>

using namespace std;


class Coda{
    public:
        vector<int> A;
        int heapsize;
    public:
        Coda() : heapsize(0) {}
        
        void MaxHeapify(vector<int>& A,int i){
            int heapsize = A.size();
            int l= left(i);
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
        
         void BuildMaxHeap(vector<int>& A) {
            heapsize = A.size();
            for (int i = (heapsize / 2) - 1; i >= 0; i--) {
                MaxHeapify(A, i);
            }
        }
        
        int HeapMaximum(vector<int>& A){
            return A[0];
        }
        
        int HeapExtractMax(vector<int>& A){
            int max= A[0];
            A[0]=A[heapsize-1];
            heapsize--;
            A.resize(heapsize);
            MaxHeapify(A,0);
            return max;
        }
        
        void HeapIncreaseKey(vector<int>& A, int i, int key){
            if(key<A[i]){
                cout<<"errore con la chiave!"<<endl;
                exit(1);
        }
            A[i]=key;
            while(i>0 && A[parent(i)]<A[i]){
                swap(A[parent(i)],A[i]);
                i=parent(i);
            }
        }
        
        void MaxHeapInsert(vector<int>& A, int key){
            heapsize++;
            A.resize(heapsize);
            A[heapsize-1]=INT_MIN;
            HeapIncreaseKey(A,heapsize-1,key);
            }
            
    void stampa(vector<int> &A){
        ofstream file("out.txt");
        cout<<"Heap stampato in ordine decrescente: "<<endl;
        while(heapsize>0){
            int max =HeapExtractMax(A);
            file<< max <<endl;
            cout<<max<<endl;
        }
        file.close();
    }
        
        
    int parent(int i){return (i-1)/2;}
    int left(int i){return 2 * i + 1;}
    int right(int i){return 2 * i + 2;}
    
};

int main(){
    Coda c;
    vector<int> V;
    
    ifstream f("coda.txt");
    string num;
    while(getline(f,num)){
        V.push_back(stoi(num));
    }
    f.close();
    
    // Costruzione dell'heap massimo
    c.BuildMaxHeap(V);

    // Stampa dei valori in ordine decrescente su out.txt
    c.stampa(V);

    
  
    return 0;
}