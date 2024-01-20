#include <bits/stdc++.h>
using namespace std;
int main(){
    long long int n,d;
    cin >> n >> d;
    vector<vector<int>> p(n,vector<int>(n,2));
    for(int i=0; i<n; i++){
        cin >> p[i][0] >> p[i][1];
    }
    vector<vector<int>> g(n);
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i==j)continue;
            long long int dist = (p[i][0]-p[j][0])*(p[i][0]-p[j][0])+(p[i][1]-p[j][1])*(p[i][1]-p[j][1]);
            long long int d2 = d*d;
            if(dist<=d2){
                // cout << i << " " << j << endl;
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    }
    vector<bool> infe(n,false);
    infe[0]=true;
    queue<int> que;
    que.push(0);
    while(!que.empty()){
        int v = que.front();
        que.pop();
        for(auto next_v:g[v]){
            if(infe[next_v])continue;
            que.push(next_v);
            infe[next_v]=true;
        }
    }
    for(int i=0; i<n; i++){
        if(infe[i])cout << "Yes" << endl;
        else cout << "No" << endl;
    }
    return 0;
}