#include <vector>
#include <queue>
#include <fstream>
#include <sstream>
#include <climits>
#include <iostream>

using namespace std;

class Edge;

class Node{
    public:
        int id;
        int d;
        int key;
        bool in_Q;
        vector<Edge*> adj;
        Node* p;
        
        Node(int id) : id(id),d(INT_MAX),key(INT_MAX),p(nullptr) {}
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
            E.push_back(new Edge(V[v_id],V[u_id],w));
            
            V[u_id]->adj.push_back(new Edge(V[u_id],V[v_id],w));
            V[v_id]->adj.push_back(new Edge(V[v_id],V[u_id],w));
        }
        
        struct Compare{
            bool operator()(Node* u,Node* v){
                return u->key > v->key;
            }
        };
        
        void Prim(int s_id){
            for(auto u : V){
                u->key=INT_MAX;
                u->p=nullptr;
            }
            V[s_id]->key=0;
            priority_queue<Node*,vector<Node*>,Compare> Q;
            Q.push(V[s_id]);
            vector<bool> in_Q(V.size(), true);
            
            while(!Q.empty()){
                Node* u=Q.top();
                Q.pop();
                in_Q[u->id] = false; 
                
                for(auto edge : u->adj){
                    Node* v = (edge->u == u) ? edge->v : edge->u;
                        if (in_Q[v->id] && edge->w < v->key){
                        v->p = u;        
                        v->key = edge->w;  
                        Q.push(v); 
                    }
                }
            }
        }
        
        void stampa(const string& file){
            ofstream f(file);
            if(!f.is_open()){
                cout<<"Errore nel apertura del file OUT.txt..."<<endl;
                return ;
            }
            
            for(auto v:V){
                f<<"Nodo : "<<v->id<<", Peso Arco Minimo : "<<v->key;
                if(v->p!=nullptr){
                    f<<", Predecessore : "<<v->p->id<<endl;
                }else{
                    f<<", Predecessore : NULL"<<endl;
                }
            }
        }
        
};


int main(){
    Grafo G;
    ifstream form("gpr.txt");
    if(!form.is_open()){
        cout<<"Errore nell apertura del file gpr.txt"<<endl;
        return 1;
    }
    
    int numNodes,numEdges;
    form>>numNodes>>numEdges;
    
    G.Resize(numNodes);
    
    int u,v,w;
    for(int i=0;i<numEdges;i++){
        form>>u>>v>>w;
        G.Add_edge(u,v,w);
    }
    cout<<"Inserimento Dati nel file OUT.txt..."<<endl;
    form.close();
    
    int s=0;
    G.Prim(s);
    
    G.stampa("out.txt");
    
    return 0;
}