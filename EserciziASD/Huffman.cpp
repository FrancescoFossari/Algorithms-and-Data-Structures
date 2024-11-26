#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <queue>
#include <climits>

using namespace std;

class Node{
    public:
    int freq;
    char val;
    Node* left;
    Node* right;
    Node* p;

    Node(char val, int freq) : freq(freq), val(val), left(nullptr), right(nullptr), p(nullptr) {}
};

class Huffman{
    public:
    Node* root;
    vector<Node*> foglie;

    struct Compare{
        bool operator()(Node* u, Node* v){
            return u->freq > v->freq;
        }
    };
    
    Node* Insert_Huffman(vector<Node*> V){
        int N=V.size();
        priority_queue<Node*,vector<Node*>,Compare> Q;
        for(auto v : V){
            Q.push(v);
            foglie.push_back(v);
        }
        for(int i=0; i<N-1; i++){
            Node* z=new Node('*',INT_MAX);
            z->left=Q.top();
            Q.pop();
            z->left->p=z;
            z->right=Q.top();
            Q.pop();
            z->right->p=z;
            z->freq=z->left->freq + z->right->freq;
            Q.push(z);
        }
        Node* r=Q.top();
        Q.pop();
        return r;
    }
    
   void preorder(Node* v){
        if(v!=nullptr){
            cout<<v->val<<" "<<v->freq<<endl;
            preorder(v->left);
            preorder(v->right);
        }
    } 
 
    void Codifica_c(char c, string& cod){
        Node* x;
        string out;
        for(auto v : foglie){
                if(v->val==c){
                    x=v;
                    break;
                }
            }
            while(x->p!=nullptr){
                if(x==x->p->left){
                    out='0'+out;
                }else if(x->p->right==x){
                    out='1'+out;
                }
                x=x->p;
            }
            cod+=out+' ';
    }

    string codifica(string cod){
        string out;
        char c;
        istringstream stream(cod);
        while(stream>>c){
            Codifica_c(c,out);
        }
        return out;
    }

    void Decodifica_s(string c, string& out){
        Node* v=root;
        for(auto d : c){
            if(d=='0'){
                v=v->left;
            }else if(d=='1'){
                v=v->right;
            }
        }
        out=out+v->val;
    }
    
    string decodifica(string dec){
        string out;
        string c;
        istringstream stream(dec);
        while(stream>>c){
            Decodifica_s(c,out);
        }
        return out;
    }
};

int main(){
    fstream F("huff.txt");
    Huffman H;
    vector<Node*> V;
    char lett;
    int freq;
    while(F>>lett>>freq){
        if(lett=='*'){
            continue;
        }else{
            V.push_back(new Node(lett,freq));
        }
    }
    H.root=H.Insert_Huffman(V);
    H.preorder(H.root);

    string cod=H.codifica("ABBACDEF");
    cout<<cod<<endl;

    string dec=H.decodifica(cod);
    cout<<dec<<endl;
    
    return 0;
}









