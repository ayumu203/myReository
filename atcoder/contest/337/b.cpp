#include <bits/stdc++.h>
using namespace std;
int main(){
    string s;
    cin >> s;
    bool a=true;
    bool b=false;
    bool c=false;
    for(int i=0; i<s.size(); i++){
        if(a&&(s[i]=='A'))continue;
        else if(a&&(s[i]=='B')){
            a=false;
            b=true;
        }
        else if(a&&(s[i]=='C')){
            a=false;
            c=true;
        }
        else if(b&&(s[i]=='B'))continue;
        else if(b&&(s[i]=='C')){
            b=false;
            c=true;
        }
        else if(c&&(s[i]=='C'))continue;
        else {
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
    return 0;
}