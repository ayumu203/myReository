#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n;
    int x=0;
    int y=0;
    for(int i=0; i<n; i++){
        int a,b;
        cin >> a >> b;
        x+=a;
        y+=b;
    }
    if(x>y)cout << "Takahashi" << endl;
    else if(x==y)cout << "Draw" << endl;
    else cout << "Aoki" << endl;
    return 0;
}