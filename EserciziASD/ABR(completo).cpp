#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Node{
  public:
    int key;
    char lett;
    Node* left;
    Node* right;
    Node* p;
    
    Node(char lett,int key) : key(key),lett(lett),left(nullptr),right(nullptr),p(nullptr) {}
};

class Albero{
    public:
        Node* root;
        Albero(): root(nullptr){}
        
    void Insert(Node* z){
        Node* x=root;
        Node* y=nullptr;
        while(x!=nullptr){
            y=x;
            if(z->key<x->key){
                x=x->left;
            }else{
                x=x->right;
            }
        }
        z->p=y;
        if(y==nullptr){
            root=z;
        }else if(z->key < y->key){
            y->left=z;
        }else{
            y->right=z;
        }
    }
    
    void Preorder(Node* x,ofstream& file){
        if(x!=nullptr){
            file<<x->lett<<","<<x->key<<endl;
            Preorder(x->left,file);
            Preorder(x->right,file);
        }
    }
    
    Node* TreeSearch(Node* x,int key){
        if(x==nullptr || key==x->key){
            return x;
        }
        if(key<x->key){
            return TreeSearch(x->left,key);
        }else{
            return TreeSearch(x->right,key);
        }
    }
    
    Node* TreeMin(Node* x){
        Node* tmp=x;
        while(tmp->left!=nullptr){
            tmp=tmp->left;
        }
        return tmp;
    }
    
    Node* TreeMax(Node* x){
        Node* tmp=x;
        while(tmp->right!=nullptr){
            tmp=tmp->right;
        }
        return tmp;
    }
    
    Node* TreeSuccessor(Node* x){
        if(x->right!=nullptr)
            return TreeMin(x->right);
        Node* y=x->p;
        while(y!=nullptr && x==y->right){
            x=y;
            y=y->p;
        }
        return y;
    }
    
    Node* TreePredecessor(Node* x){
        if(x->left!=nullptr)
            return TreeMax(x->left);
        Node* y=x->p;
        while(y!=nullptr && x==y->left){
            x=y;
            y=y->p;
        }
        return y;
    }
    
    void Transplant(Node* u,Node* v){
        if(u->p==nullptr){
            root=v;
        }else if(u==u->p->left){
            u->p->left=v;
        }else{
            u->p->right=v;
        }if(v!=nullptr){
            v->p=u->p;
        }
    }
    
    
    void StampaABR(){
        ofstream file("out.txt");
        if(!file.is_open()){
            cerr<<"Errore nell'apertura del file OUT.txt"<<endl;
        }else{
        cout << "Inserimento visita Preorder nel file OUT.txt" << endl;
        Preorder(root,file);
        }
        file.close();
    }
    
    void StampaTransplant(){
        ofstream f1("out1.txt");
        if(!f1.is_open()){
            cerr<<"Errore nell'apertura del file OUT1.txt..."<<endl;
        }else{
        cout << "Transplant avvenuta con successo nel file OUT1.txt..." << endl;
        Preorder(root,f1);
        f1.close();
        }
    }
    
};


int main(){
    ifstream f("abr.txt");
    int chiave;
    char lettera;
    Albero A;
    
    while(f>>lettera>>chiave){
        Node* v=new Node(lettera,chiave);
        A.Insert(v);
    }
    f.close();
    
    A.StampaABR();
    
    Node* max=A.TreeMax(A.root);
    Node* min=A.TreeMin(A.root);
    
    cout<<"Stampa della chiave piu piccola : "<<min->key<<endl;
    cout<<"Stampa della chiave piu grande : "<<max->key<<endl;
    
    cout<<"Inserisci il nodo per Cercare il nodo e trovare il suo Predecessore e Successore :"<<endl;
    cin>>chiave;
    

    Node* cerca=A.TreeSearch(A.root,chiave);
    if(cerca){
    cout<<"Chiave "<<cerca->key<<" trovata!"<<endl;
    }else{
    cout<<"Chiave "<<chiave<<" NON trovata!"<<endl;
    return 0;
    }
    
    Node* pred=A.TreePredecessor(cerca);
    if(pred!=nullptr){
    cout<<"Il Predecessore di "<<chiave<<" e' : "<<pred->key<<endl;
    }else{
        cout<<"Il Predecessore NON esiste!"<<endl;
    }

    Node* succ=A.TreeSuccessor(cerca);
    if(succ!=nullptr){
    cout<<"Il Successore di "<<chiave<<" e' : "<<succ->key<<endl;
    }else{
        cout<<"Il Successore NON esiste ! "<<endl;
    }
    

    int chiave1,chiave2;
    cout<<"Inserisci chiave 1 : "<<endl;
    cin>>chiave1;
    Node* k1=A.TreeSearch(A.root,chiave1);

    cout<<"Inserisci chiave 2 : "<<endl;
    cin>>chiave2;
    Node* k2=A.TreeSearch(A.root,chiave2);
    
    if (k1 == nullptr || k2 == nullptr) {
    cout << "Uno dei due nodi non esiste! " << endl;
    return 0;
    }else if (k1 == k2) {
    cout << "Le chiavi devono essere diverse!" << endl;
    return 0;
    }else{
    A.Transplant(k1,k2);
    A.StampaTransplant();
    }
    return 0;
}
