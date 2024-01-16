#include <bits/stdc++.h>
using namespace std;
vector<int> v1(26,0);
vector<int> v2(26,0);
vector<int> c = {'a'-97,'t'-97,'c'-97,'o'-97,'d'-97,'e'-97,'r'-97};
int main(){
    string s,t;
    cin >> s >> t;
    sort(s.begin(),s.end());
    sort(t.begin(),t.end());
    int sAt=0;
    int tAt=0;
    for(int i=0; i<s.size(); i++){
        if(s[i]=='@'){
            sAt++;
        }
        else v1[s[i]-97]++;
        if(t[i]=='@'){
            tAt++;
        }
        else v2[t[i]-97]++;
    }
    for(int i=0; i<26; i++){
        bool flag=true;
        if(v1[i]==v2[i])continue;
        for(int j=0; j<c.size(); j++)if(v1[i]>v2[i]&&i==c[j]&&v1[i]-v2[i]<=tAt){
            tAt-=v1[i]-v2[i];
            flag=false;
            }
        for(int j=0; j<c.size(); j++)if(v1[i]<v2[i]&&i==c[j]&&v2[i]-v1[i]<=sAt&&flag){
            sAt-=v2[i]-v1[i];
            flag=false;
        }
        if(flag){
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
    return 0;
}