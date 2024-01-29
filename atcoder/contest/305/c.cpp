#include <bits/stdc++.h>
using namespace std;
vector<int> dx={1,-1,0,0,};
vector<int> dy={0,0,1,-1};
int h,w;
bool ok(int x,int y){
    if(x>=0&&x<w&&y>=0&&y<h)return true;
    return false;
}
int main(){
    cin >> h >> w;
    vector<string> s(h);
    for(int i=0; i<h; i++)cin >> s[i];
    for(int i=0; i<h; i++){
        for(int j=0; j<w; j++){
            if(s[i][j]=='.'){
                int sharp=0;
                for(int k=0; k<4; k++){
                    int x=dx[k]+j;
                    int y=dy[k]+i;
                    if(ok(x,y)&&s[y][x]=='#')sharp++;
                }
                if(sharp>=2){
                    cout << i+1 << " " << j+1 << endl;
                    return 0;
                }
            }
        }
    }
    return 0;
}