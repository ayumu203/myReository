#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m;
    vector<string> Sn;
    cin >> n >> m;
    for(int i=0; i<n; i++){
        string tmp;
        cin >> tmp;
        Sn.push_back(tmp);
    }
    sort(Sn.begin(),Sn.end());
    do{
        bool ok=true;
        for(int i=0; i<n-1; i++){
            int cnt=0;
            for(int j=0; j<m; j++)if(Sn[i][j]!=Sn[i+1][j])cnt++;
            if(cnt!=1)ok=false;
        }
        if(ok){
            cout << "Yes" << endl;
            return 0;
        }
    } while(next_permutation(Sn.begin(),Sn.end()));
    cout << "No" << endl;
    return 0;
}