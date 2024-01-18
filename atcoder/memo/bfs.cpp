#include <bits/stdc++.h>
using namespace std;

using Graph = vector<vector<int>>;
int main(){
    //n個の点とm本の辺と
    int n,m;
    cin >> n >> m;
    Graph g(n);
    for(int i=0; i<m; i++){
        int a,b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    //検索した場所をチェックにする
    vector<bool> check(n,false);
    //検索した場所を格納する
    queue<int> que;
    check[0]=true;
    que.push(0);
    while(!que.empty()){
        //頂点を取り出す
        int v = que.front();
        que.pop();
        for(auto next_v:g[v]){
            if(check[next_v]==true){
                continue;
            }
            check[next_v]=true;
            que.push(next_v);
        }
    }
    for(auto c:check)cout << c << endl;
    return 0;
}