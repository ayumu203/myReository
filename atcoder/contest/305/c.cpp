#include <bits/stdc++.h>
using namespace std;
vector<int> dx={1,1,1,0,0,-1,-1,-1};
vector<int> dy={1,0,-1,1,-1,1,0,-1};
int main(){
    int h,w;
    cin >> h >> w;
    vector<string> s(h);
    for(int i=0; i<h; i++)cin >> s[i];
    int count=0;
    int size=0;
    int fx=0;
    int fy=0;
    bool first=true;
    for(int i=0; i<h; i++)for(int j=0; j<w; j++)if(s[i][j]=='#'){
        if(first){
            fx=j;
            fy=i;
            first=false;
        }
        count++;
        }
    for(int i=2; i<500; i++){
        if(i*i==count+1)size=i;
    }
    
    return 0;
}