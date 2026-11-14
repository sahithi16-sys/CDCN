#include <bits/stdc++.h>
using namespace std;
struct Node {
    char d;
    Node* l;
    Node *r;
    Node(char ch, Node *a=0,Node *b = 0) : d(ch), l(a), r(b) {}
};

string s;
int pos=0,reg=0;

bool at(string ops) { return pos<(int)s.size() && ops.find(s[pos])!=string::npos;}

Node* expr();

Node *factor() {
    if(s[pos]!='(') return new Node(s[pos++]);
    pos++;
    Node *x = expr();
    pos++;
    return x;
}

Node *level(string ops,Node *(* next)()) {
    Node *x = next();
    while(at(ops)) {
        char op = s[pos++];
        x = new Node(op,x,next());
    }
    return x;
}

Node *term() {return level("*/",factor);}
Node *expr() {return level("+-",term);}

int gen(Node *n) {
    if(!n->l && !n->r) {
        cout << "MOV R" << reg << ", " << n->d << endl;
        return reg++;
    }
    int a = gen(n->l),b=gen(n->r);
    
    cout << (n->d=='+'? "ADD " : n->d=='-'? "SUB " : n->d=='*'? "MUL " : "DIV ") << "R" << a << " , R" << b << endl;
    return a;
}

int main()
{
    cout << "Enter expression : ";
    getline(cin,s);
    
    int i = 0;
    while(i<(int)s.size() && isalnum(s[i])) i++;
    string lhs = s.substr(0,i);
    if(lhs.empty() || i>=(int)s.size() || s[i]!='=') {
        cout << "Invalid Expression!" << endl;
        return 0;
    }
    
    s = s.substr(i+1);
    
    Node *root = expr();
    if(pos!=s.size()) {
        cout << "Invalid Expression" << endl;
        return 0;
    }
    int r = gen(root);
    cout << "MOV " << lhs << ", R" << r << endl;

    return 0;
}