#include <fstream>
#include <sstream>
#include <climits>
#include <vector>
#include <iostream>

using namespace std;

enum Color{WHITE, GREY, BLACK};

class Edge;

class Node{
    public:
        int id;
        int d;
        Color color;
        vector<Edge*> adj;
        Node* p;
        
        Node(int id) : id(id),d(INT_MAX),color(WHITE),p(nullptr) {}
};

class Edge{
    public:
        Node* u;
        Node* v;
        int w;
        
        Edge(Node* u,Node* v,int w) : u(u),v(v),w(w) {}
};

class Grafo{
  public:
    vector<Node*> V;
    vector<Edge*> E;
    
    void Resize(int n){
        V.resize(n,nullptr);
        for(int i=0;i<n;i++){
            V[i]=new Node(i);
        }
    }
    
    void Add_edge(int u_id,int v_id,int w){
        E.push_back(new Edge(V[u_id],V[v_id],w));
        
        V[u_id]->adj.push_back(new Edge(V[u_id],V[v_id],w));
    }
    
    void Relax(Node*u,Node* v,int w){
        if(v->d > u->d+w){
            v->d = u->d+w;
            v->p=u;
        }
    }
    
    void InitializeSingleSource(int s_id){
        for(auto v : V){
            if(v->id==s_id){
                v->d=0;
                v->p=nullptr;
            }else{
                v->d=INT_MAX;
                v->p=nullptr;
            }
        }
    }
    
    bool BellmanFord(int s_id){
        InitializeSingleSource(s_id);
        for(int i=0;i<V.size();i++){
            for(auto e : E){
                Relax(e->u,e->v,e->w);
            }
        }
        for(auto e:E){
            if(e->v->d > e->u->d + e->w){
                cout<<"Ciclo Negativo trovato : "<<e->u->id<<" -> "<<e->v->id<<endl;
                return false;
            }
        }
        return true;
    }
    
    void stampa(){
        ofstream file("out.txt");
        if(!file.is_open()){
            cout<<"Errore nell' apertura del File OUT.txt..."<<endl;
            return;
        }
        for(auto v:V){
            if(v->d==INT_MAX){
                file<<"Nodo : "<<v->id<<", Distanza : INFINITO, Predecessore: NULL"<<endl;
            }else{
                file<<"Nodo : "<<v->id<<", Distanza : "<<v->d;
                if(v->p!=nullptr){
                    file<<" ,Predecessore : "<<v->p->id<<endl;
                }else{
                    file<<" ,Predecessore : NULL"<<endl;
                }
            }
        }
        file<<endl;
        file.close();
    }
    
};


int main(){
    Grafo G;
    ifstream f("bf.txt");
    
    int numNodes,numEdges;
    f>>numNodes>>numEdges;
    G.Resize(numNodes);
    
    int u,v,w;
    for(int i=0;i<numEdges;i++){
        f>>u>>v>>w;
        G.Add_edge(u,v,w);
    }
    
    if(G.BellmanFord(0)){
        cout<<"Nessun ciclo negativo trovato!"<<endl;
    }
    
    G.stampa();
    
    f.close();
    
    return 0;
}