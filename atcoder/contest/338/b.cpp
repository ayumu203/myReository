#include <bits/stdc++.h>
using namespace std;
vector<char> c={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','s','s','t','u','v','w','x','y','z'};
int main(){
    string s;
    cin >> s;
    vector<int> v(26,0);
    // cout << 'a'-0 << endl;
    for(int i=0; i<s.size(); i++){
        v[s[i]-97]++;
        // cout << s[i]-97 << endl;
    }
    int m=0;
    int ans=0;
    for(int i=0; i<26; i++){
        if(v[ans]<v[i]){
            ans=i;
            m=v[i];
        }
    }
    cout << c[ans] << endl;
    return 0;
}