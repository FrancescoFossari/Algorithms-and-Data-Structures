#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>
#include <queue>
#include <vector>
#include <climits>

using namespace std;

enum Color{WHITE, GREY, BLACK};

class Edge;

class Node{
    public:
        int id;
        int d;
        int tempin;
        int tempfin;
        int time;
        Node* p;
        vector<Edge*> adj;
        Color color;

        Node(int id) : id(id), d(INT_MAX),p(nullptr),color(WHITE),tempin(0),tempfin(0) {}
};

class Edge{
    public: 
        Node* u;
        Node* v;
        int w;

        Edge(Node* u,Node*v,int w) : u(u),v(v),w(w) {}
};

class Grafo{
    public:
        vector<Node*> V;
        vector<Edge*> E;
        int time=0;

        void Resize(int n){
            V.resize(n,nullptr);
            for(int i=0;i<n;i++){
                V[i]=new Node(i);
            }
        }

        void Add_edge(int u_id,int v_id,int w){
            E.push_back(new Edge(V[u_id],V[v_id],w));
            E.push_back(new Edge(V[v_id],V[u_id],w));

            V[u_id]->adj.push_back(new Edge(V[u_id],V[v_id],w));
            V[v_id]->adj.push_back(new Edge(V[v_id],V[u_id],w));
        }

        stack<Node*> DFS(){
            stack<Node*> S;
            for(auto u : V){
                u->color=WHITE;
                u->p=nullptr;
            }
            time=0;
            for(auto u:V){
                if(u->color==WHITE){
                    DFSVISIT(u,S);
                }
            }
            return S;
        }

        void DFSVISIT(Node* u,stack<Node*>& S){
            time=time+1;
            u->tempin=time;
            u->color=GREY;
            for(auto edge:u->adj){
                Node* v = edge->v;
                if(v->color==WHITE){
                    v->p=u;
                    DFSVISIT(v,S);
                }
            }
            time=time+1;
            u->tempfin=time;
            u->color=BLACK;
            S.push(u);
        }

        void stampaDFS(const string& filename){
            ofstream file(filename);
            if(!file.is_open()){
                cout<<"Errore apertura file OUT.TXT..."<<endl;
                return;
            }

            for(auto v:V){
                file<<"Nodo : "<<v->id<<", Tempo Iniziale : "<<v->tempin<< ", Tempo Finale : " << v->tempfin;
                if(v->p!=nullptr){
                    file<<", Predecessore : "<<v->p->id<<endl;
                }else{
                    file<<", Predecessore : NULL"<<endl;
                }
                file<<endl;
            }
        }

};



int main(){
Grafo G;
ifstream f("gpr.txt");

int numNodes, numEdges;
f>>numNodes>>numEdges;
G.Resize(numNodes);

int u,v,w;
for(int i=0;i<numEdges;i++){
    f>>u>>v>>w;
    G.Add_edge(u,v,w);
}
f.close();

G.DFS();

int s=0;
G.stampaDFS("out.txt");

return 0;
}