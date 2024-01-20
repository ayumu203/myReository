#include <bits/stdc++.h>
using namespace std;
int h,w,k;
vector<string> s;
vector<bool> seen;
using Graph = vector<vector<int>>;
vector<int> dx={1,1,1,0,0,-1,-1,-1};
vector<int> dy={1,0,-1,1,-1,1,0,-1};
bool ok(int x,int y){
    if(x>=0&&x<w&&y>=0&&y<h)return true;
    return false;
}
int dfs(Graph G,int v,int count){
    seen[v]=true;
}
int main(){
    cin >> h >> w >> k;
    s.assign(h,"#");
    seen.assign(h*w,false);
    for(int i=0; i<h; i++)cin >> s[i];
    Graph G(h*w);
    for(int i=0; i<h; i++){
        for(int j=0; j<w; j++){
            if(s[i][j]=='o'){
                for(int k=0; k<8; k++){
                    int x=j+dx[k];
                    int y=i+dy[k];
                    if(ok(x,y)&&s[y][x]=='o'){
                        G[i*w+j].push_back(y*w+x);
                        // cout << i*w+j << " " << y*w+x << endl;
                    }
                }
            }
        }
    }
    return 0;
}