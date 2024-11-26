#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <algorithm>
#include <climits>
#include <vector>

using namespace std;

enum Color{WHITE, GREY, BLACK};

class Edge;

class Node{
  public:
    int id;
    int d;
    Node* p;
    vector<Edge*> adj;
    Color color;
    
    Node(int id) : id(id), d(INT_MAX), color(WHITE), p(nullptr) {}
};

class Edge{
  public:
    Node * u;
    Node* v;
    int w;
    
    Edge(Node* u, Node* v,int w) : u(u),v(v),w(w) {}
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
        Node* u = V[u_id];
        Node* v = V[v_id];
        Edge* edge = new Edge(u,v,w);
        
        u->adj.push_back(edge);
        v->adj.push_back(new Edge(v,u,w));
        E.push_back(edge);
    }
    
    
    void BFS(int s_id){
        for(auto u : V){
            u->color=WHITE,
            u->d=INT_MAX;
            u->p=nullptr;
        }
        Node* s= V[s_id];
        s->color = GREY;
        s->d=0;
        s->p=nullptr;
        
        queue<Node*> Q;
        Q.push(s);
        
        while(!Q.empty()){
            Node* u = Q.front();
            Q.pop();
            
            for(auto edge : u->adj){
                Node* v = edge->v;
                if(v->color==WHITE){
                    v->color=GREY;
                    v->d=u->d+1;
                    v->p=u;
                    Q.push(v);
                }
            }
            u->color = BLACK;
        }
    }
    
    void stampaBFS(int s_id,const string& filename){
       BFS(s_id);
       
       ofstream file(filename);
       if(!file.is_open()){
           cout<<"Errore nell' apertura del file "<<filename<<"..."<<endl;
           return;
       }
       
       for(auto v : V){
           file<<"Nodo : "<<v->id<<", Distanza : "<<v->d;
           if(v->p != nullptr){
               file<<", Predecessore : "<<v->p->id;
           }else{
               file<<", Predecessore : NULL";
           }
           file<<endl;
       }
       file.close();
    }

};



int main(){
    Grafo G;
    ifstream f("GPR.txt");
    if(!f.is_open()){
        cout<<"Errore nell apertura del file GPR..."<<endl;
        return 1;
    }
    
    int numNodes, numEdges;
    f>>numNodes>>numEdges;
    
    G.Resize(numNodes);
    
    int u,v,w;
    for(int i=0;i<numEdges;++i){
    f>>u>>v>>w;
    G.Add_edge(u,v,w);
    }
    
    f.close();
    
    int s = 0;
    G.stampaBFS(s,"out.txt");
    
    return 0;
}















