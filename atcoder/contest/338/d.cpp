#include <bits/stdc++.h>
using namespace std;
int dfs(const vector<vector<int>> &G,int v,vector<int> &root,int point,int goal,int count){
    for(auto next_v:G[v]){
        count++;
        if(next_v==root[point]){
            point++;
            if(point==goal){
                return count;
            }
        }
        dfs(G,next_v,root,point,goal,count);
    }
}
int main(){
    int n,m;
    cin >> n >> m;
    vector<int> root(m);
    for(int i=0; i<m; i++)cin >> root[i];

    vector<vector<int>> G(n+1);
    for(int i=1; i<n; i++){
        G[i].push_back(i+1);
    }
    G[n].push_back(1);
    int ans=0;
    for(int i=1; i<=n; i++){
        int banRoot=i;
        ans = max(ans,dfs(G,root[0],root,1,m-1,0));
    }
    cout << ans << endl;
    return 0;
}