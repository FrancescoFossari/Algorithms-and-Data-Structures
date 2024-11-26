/*
Utilizzando il paradigma della programmazione ad oggetti ed il linguaggio C++ 11, progettare ed 
implementare, come classe, una struttura dati hashtable con indirizzamento aperto che consente 
di memorizzare le coppie < int, string > contenute nel file IN.txt. 
Dotare la classe di un metodo PRINT per scrivere nel file OUT.txt il contenuto della hash table. (pt 18)

.Implementare il metodo FIND(int) che restituisce in output la stringa 
associata alla chiave passata come argomento.(pt. 6)

.Implementare il metodo DELETE(int) che consente di eliminare la coppia < int, string > 
associata alla chiave passata come argomento (dopo la cancellazione visualizzare a video 
il contenuto della hash table). (parte 6)
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

class Cella{
    public:
    int chiave;
    string val;
    
    Cella(int chiave,string val) : chiave(chiave),val(val) {}
};


class HashTable{
    
    public:
        vector<Cella*> T;
        int m;

    void Resize(int n){
        m=n;
        T.resize(n,nullptr);
    }

    int fun_hash(int i,int chiave){
        return (i+chiave)%m;
    }  
    
    
    int Insert(int chiave,string val){
        int j;
        for(int i=0;i<m;i++){
            j=fun_hash(i,chiave);
            if(T[j] == nullptr){
                T[j]= new Cella(chiave,val);
                return j;
            }
        }
        return -1;
    }
    
    int Search(int chiave){
        int j;
        int i=0;
        do{
            j=fun_hash(i,chiave);
            if(T[j]!=nullptr && T[j]->chiave==chiave){
                return j;
            }i++;
        }while(i<m && T[j]!=nullptr);
        return -1;
    }
    
    void Delete(int chiave){
        int i=0;
        int j;
        do{
            j=fun_hash(i,chiave);
            if(T[j]!=nullptr && T[j]->chiave==chiave){
                delete T[j];
                T[j]=nullptr;
                break;
            }i++;
        }while(i<m);
         // Stampa il contenuto della hash table
        cout << "Hash table dopo Delete:" << endl;
        stampa();
    }
    
    void stampa(){
        ofstream file("out.txt");
        for(auto v : T){
            if(v!=nullptr){
            cout<<v->chiave<<" "<<v->val<<endl;
            file<<v->chiave<<" , "<<v->val<<endl;
            }
        }
        file.close();
    }
    
};



int main()
{
    HashTable ht;
    ifstream f("hash.txt");
    char p1,p2,virgola;
    string nome;
    int chiave;
    string rigo;
    
    ht.Resize(4);
    while(getline(f,rigo)){
        istringstream f(rigo);
        f>>p1>>chiave>>virgola>>nome>>p2;
        nome.pop_back();
        ht.Insert(chiave,nome);
    }
    f.close();
    
    int h = ht.Search(1010);
    if(h==-1){
        cout<<"Errore chiave !"<<endl;
    }else{
        cout<<"chiave trovata : "<<ht.T[h]->chiave<<" ,all'indice : "<<h<<endl;
    }
    
    ht.Delete(1671);

    return 0;
}