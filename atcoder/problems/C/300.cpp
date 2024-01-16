#include <bits/stdc++.h>
using namespace std;
int H,W;
vector<vector<char>> s;
vector<int> DX={1,1,-1,-1};
vector<int> DY={1,-1,1,1};

bool ok(int x,int y){
    if(x>=0&&x<W&&y>=0&&y<H)return true;
    return false;
}

bool test(int x,int y,int n){
    for(int i=0; i<DX.size(); i++){
        int targetX = x+DX[i]*n;
        int targetY = y+DY[i]*n;
        if(!ok(targetX,targetY)||s[targetY][targetX]=='.')return false;
    }
    return true;
}

int main(){
    cin >> H;
    cin >> W;
    s.assign(H,vector<char>(W,'.'));
    int N = min(H,W);
    vector<int> ans(N);
    for(int i=0; i<H; i++)for(int j=0; j<W; j++)cin >> s[i][j];
    for(int i=0; i<H; i++){
        for(int j=0; j<W; j++){
            if(s[i][j]=='.')continue;
            else {
                int tmp=0;
                int n=1;
                while(test(j,i,n)){
                    tmp++;
                    n++;
                }
                if(tmp!=0)ans[tmp-1]++;
            }
        }
    }
    for(auto e:ans)cout << e << " ";
    cout << endl;
}