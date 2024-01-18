#include <bits/stdc++.h>
using namespace std;
int main(){
    int n,m,h,k;
    string s;
    cin >> n >> m >> h >> k >> s;
    map<int,vector<int>> items;
    map<int,vector<bool>> get;
    int x=0;
    int y=0;
    for(int i=0; i<m; i++){
        int x,y;
        cin >> x >> y;
        vector<int> v;
        for(int j=0; j<items[x].size(); j++)v.push_back(items[x][j]);
        v.push_back(y);
        items[x]=v;
        get[x].push_back(true);
    }
    for(int i=0; i<n; i++){
        //移動
        char c = s[i];
        if(c=='R')x++;
        else if(c=='L')x--;
        else if(c=='U')y++;
        else if(c=='D')y--;
        //体力
        h--;
        if(h<0){
            cout << "No" << endl;
            return 0;
        }
        for(int j=0; j<items[x].size(); j++)if(h<k&&y==items[x][j]&&get[x][j]){
            h=k;
            get[x][j]=false;
        }
        if(h<0){
            cout << "No" << endl;
            return 0;
        }
    }
    cout << "Yes" << endl;
    return 0;
}