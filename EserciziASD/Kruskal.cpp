#include <iostream>
#include <fstream>
#include <queue>
#include <climits>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

enum Color{WHITE, GREY, BLACK};

class Edge;

class Node{
  public:
    int id;
    int d;
    vector<Edge*> adj;
    Color color;
    int rank;
    Node* p;
    
    Node(int id) : id(id),color(WHITE), p(nullptr), d(INT_MAX), rank(0) {}
    
};

class Edge{
    public:
        Node* u;
        Node* v;
        int w;
        
        Edge(Node* u, Node* v, int w) : u(u), v(v), w(w) {}
};

class Grafo{
  public:
    vector<Node*> V;
    vector<Edge*> E;
    
    void Resize(int n){
        V.resize(n, nullptr);
        for(int i = 0; i < n; ++i){
            V[i] = new Node(i);
        }
    }
    
    void Add_edge(int u_id, int v_id, int w){
        E.push_back(new Edge(V[u_id],V[v_id],w));

        V[u_id]->adj.push_back(new Edge(V[u_id],V[v_id],w));
    }
    
    static bool Compare_Edge(Edge* e1, Edge* e2){
          return e1->w < e2->w;
    }
    
    void MakeSet(Node* v){
        v->rank = 0;
        v->p = v;
    }
    
    Node* FindSet(Node* x){
        if(x->p != x){
            x->p = FindSet(x->p);
        }
        return x->p;
    }
    
    void Union(Node* u, Node* v){
        Link(FindSet(u), FindSet(v));
    }
    
    void Link(Node* u, Node* v){
        if(u->rank > v->rank){
            v->p = u;
        } else {
            u->p = v;
            if(u->rank == v->rank){
                v->rank++;
            }
        }
    }
    
    vector<Edge*> Kruskal() {
        vector<Edge*> A;
        for (auto v : V) {
            MakeSet(v);
        }
        sort(E.begin(), E.end(), Compare_Edge);  
        for (auto e : E) {
            if (FindSet(e->u) != FindSet(e->v)) {
                Union(e->u, e->v);
                A.push_back(e);
            }
        }
        return A;
    }
    
    void StampaKruskal(vector<Edge*> MST) {
        ofstream file("out.txt");
        if (!file.is_open()) {
            cout << "Errore nell'apertura del file OUT.txt..." << endl;
            return;
        }
        
        for(auto edge : MST){
            file<<"Nodo u : "<<edge->u->id<<", Peso : "<<edge->w<<", Nodo v : "<<edge->v->id<<endl;
            cout<<"Nodo u : "<<edge->u->id<<", Peso : "<<edge->w<<", Nodo v : "<<edge->v->id<<endl;
        }
        file.close();
    }
};

int main() {
    ifstream f("gpr.txt");
    if (!f.is_open()) {
        cout << "Errore nell'apertura del file GPR.txt..." << endl;
        return 1;
    }
    Grafo G;
    
    int numNodes, numEdges;
    f >> numNodes >> numEdges;
    G.Resize(numNodes);
    
    int u, v, w;
    for (int i = 0; i < numEdges; i++) {
        f >> u >> v >> w;
        G.Add_edge(u, v, w);
        }
    f.close();
    
    vector<Edge*> MST = G.Kruskal();
    G.StampaKruskal(MST);
    
    return 0;
}