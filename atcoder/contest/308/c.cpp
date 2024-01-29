#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n;
    vector<pair<double,int>> v;
    for(int i=0; i<n; i++){
        double a,b;
        cin >> a >> b;
        double tmp=a/(a+b);
        v.push_back({tmp,i+1});
    }
    stable_sort(v.begin(),v.end());
    reverse(v.begin(),v.end());
    for(int i=0; i<n; i--){
        cout << v[i].second << " ";
    }
    cout << endl;
    return 0;
}