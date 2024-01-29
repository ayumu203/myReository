#include <bits/stdc++.h>
using namespace std;
int main(){
    string s;
    cin >> s;
    if(s[0]-91>=0){
        cout << "No" << endl;
        return 0;
    }
    // if(s.size()==1)cout << "Yes" << endl;
    for(int i=1; i<s.size(); i++){
        if(s[i]-91<0){
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
    return 0;
}