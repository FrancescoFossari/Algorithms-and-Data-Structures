#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

class Edge;

class Node{
  public:
    int id;
    int d;
    Node* p;
    vector<Edge*> adj;
    
    Node(int id) : id(id),p(nullptr),d(INT_MAX) {}
};

class Edge{
  public:
    Node* u;
    Node* v;
    int w;
    
    Edge(Node* u,Node* v,int w): u(u),v(v),w(w) {}
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
    
    void Add_Edge(int u_id,int v_id,int w){
        E.push_back(new Edge(V[u_id],V[v_id],w));
        
        V[u_id]->adj.push_back(new Edge(V[u_id],V[v_id],w));
        V[v_id]->adj.push_back(new Edge(V[v_id],V[u_id],w));
    }
    
    struct Compare{
      bool operator()(Node* u,Node* v){
          return u->d > v->d;
      }  
    };
    
    void InitializeSingleSource(int s_id){
        for(auto v:V){
            if(v->id==s_id){
                v->d=0;
                v->p=nullptr;
            }else{
                v->d=INT_MAX;
                v->p=nullptr;
            }
        }
    }
    
    void Dijkstra(int s_id) {
    InitializeSingleSource(s_id);
    priority_queue<Node*, vector<Node*>, Compare> Q;
    Q.push(V[s_id]);

    while (!Q.empty()) {
        Node* u = Q.top();
        Q.pop();
        
        if (u->d == INT_MAX) continue;

        for (auto edge : u->adj) {
            Node* v = (edge->u == u) ? edge->v : edge->u;
            if (v->d > u->d + edge->w) {
                v->d = u->d + edge->w;
                v->p = u;
                Q.push(v);
                }
            }
        }
    }
    
    void Stampa(){
        ofstream file("out.txt");
        if(!file.is_open()){
            cout<<"Errore nell'apertura del file OUT.txt..."<<endl;
            return;
        }
        
        for(auto v:V){
            if(v!=nullptr){
                file<<"Nodo : "<<v->id<<", Distanza : "<<v->d;
            }
            if(v->p!=nullptr){
                file<<", Nodo Padre : "<<v->p->id;
            }else{
                file<<", Nodo Padre : NULL";
            }
            file << ", Percorso: ";
            if (v->d == INT_MAX) {
                file << "Non raggiungibile";
            } else {
                Node* curr = v;
                while (curr != nullptr) {
                    file << curr->id << " ";
                    curr = curr->p;
                }
            }
            file << endl;
        }
        file<<endl;
        file.close();
    }
    
};


int main(){
    Grafo G;
    ifstream f("gpr.txt");
    if(!f.is_open()){
        cout<<"Errore nell'apertura del file GPR.txt..."<<endl;
        return 1;
    }
    
    int numNodes,numEdges;
    f>>numNodes>>numEdges;
    G.Resize(numNodes);
    
    int u,v,w;
    for (int i = 0; i < numEdges; i++) {
    if (!(f >> u >> v >> w)) {
        cout << "Errore: formato del file gpr.txt non valido!" << endl;
        return 1;
    }
    G.Add_Edge(u, v, w);
}

    
    cout<<"Scrittura nel file OUT.txt avvenuta con successo..."<<endl;
    f.close();
    
    G.Dijkstra(0);
    
    G.Stampa();
    
    return 0;
}