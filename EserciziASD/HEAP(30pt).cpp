/*
1.Utilizzando il paradigma della programmazione ad oggetti ed il linguaggio C++ 11, progettare ed implementare, come 
classe, una struttura dati MIN HEAP che consenta di caricare i numeri interi contenuti nel file HEAP.txt. Dotare la classe 
di un metodo per scrivere nel file OUT.txt il contenuto del MIN HEAP.(pt. 18)

2.Dotare la classe MIN_HEAP del metodo DECREASE_KEY (i, key ) che decrementi a key l'elemento i e lo 
riposizioni nel MIN HEAP. Mostrare a video il contenuto del MIN HEAP dopo la chiamata DECREASE KEY(53,30). (pt. 6)

3.Dotare la classe MIN HEAP del metodo HEAP SORT() che ordini in ordine decrescente i numeri contenuti nel MIN HEAP. 
Mostrare a video il contenuto del MIN HEAP dopo la chiamata HEAP SORT()(pt. 6)
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <climits>

using namespace std;

class Heap{
    public:
        vector<int> A;
        int heapsize;
    public:
        Heap() : heapsize(0) {}

void buildMinHeap(vector<int>& A){
    heapsize=A.size();
    for(int i=(A.size()/2)-1;i>=0;i--){
            MinHeapify(A,i);
    }
}

void MinHeapify(vector<int>& A,int i){
    int l=Left(i);
    int r=Right(i);
    int min=0;

    if(l<heapsize && A[l]<A[i]){
        min=l;
    }else{
        min=i;
    }
    if(r<heapsize && A[r]<A[min]){
        min =r;
    }
    if(min!=i){
        swap(A[i],A[min]);
        MinHeapify(A,min);
    }
}

void DecreaseKey(vector<int>& A,int i,int key){
    if(key>A[i]){
        cout<<"errore chiave DecreaseKey !"<<endl;
        exit(1);
    }
    A[i]=key;
    while(i>=0 && A[parent(i)]>A[i]){
        swap(A[parent(i)],A[i]);
        i=parent(i);
    }
}

void Heapsort(vector<int>& A){
    buildMinHeap(A);
    for(int i=A.size()-1;i>=1;i--){
        swap(A[0],A[i]);
        heapsize--;
        MinHeapify(A,0);
    }
}

void stampa(vector<int>& A){
    ofstream file("out.txt");
    for(auto v : A){
        file<<v<<" "<<endl;
    }
    file.close();
}

int parent(int i) {return (i-1)/2;}
int Left(int i){return 2 * i + 1;}
int Right(int i) {return 2 * i + 2;}

};


int main(){

    Heap hp;
    vector<int> B;

    ifstream dio("cazz.txt");
    string rigo;
    while(getline(dio,rigo)){
        B.push_back(stoi(rigo));
    }

    hp.buildMinHeap(B);
    hp.stampa(B);

    hp.DecreaseKey(B,0,11);
    hp.stampa(B);

    hp.Heapsort(B);
    cout<<"Stampa dell' Heap Ordinato : "<<endl;
    for(auto b : B){
        cout<<b<<" "<<endl;
    }

    return 0;
}