/******************************************************************************

                              Online C++ Compiler.
               Code, Compile, Run and Debug C++ program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ifstream file("input.txt");

    if(!file) {
        cout << "File not found!";
        return 1;
    }

    set<string> kw = {"int","float","double","char","if","else","do","while"};
    string s;
    while(getline(file,s)) {
        for(int i = 0;i<s.size();) {
            char ch = s[i];
            
            if(isspace(ch)) i++;
            else if(ch=='/' && i+1<s.size() && s[i+1]=='/') break;

            else if(isalpha(ch) || ch=='_') {
                string w="";
                while(i<s.size() && (s[i]=='_' || isalnum(s[i]))) w+=s[i++];
                cout << w << " : " << (kw.count(w)? "KEYWORD" : "IDENTIFIER") << endl;
            }

            else if(isdigit(ch)) {
                string w = "";
                while(i<s.size() && isdigit(s[i])) w += s[i++];
                cout << w << " : NUMBER" << endl;
            }

            else {
                if(string("+-*/=^").find(ch)!= string::npos) cout << ch << " : " << "OPERATOR" << endl;
                else if(string(";,{}[]()").find(ch)!= string::npos) cout << ch << " : " << "DELIMETER" << endl;
                else cout << ch << " : " << "UNKNOWN" << endl;
                i++;
            }
        }
    }
    file.close();
    return 0;
}