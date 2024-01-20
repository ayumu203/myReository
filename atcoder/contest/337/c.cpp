#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n;
    map<int,int> m;
    for(int i=1; i<=n; i++){
        int tmp;
        cin >> tmp;
        if(tmp==-1){
            m[-1]=i;
        }
        else {
            m[tmp]=i;
        }
    }
    // cout << m[-1] << " ";
    if(n==1){
        cout << 1 << endl;
        return 0;
    }
    int tmp=m[-1];
    // cout << m[tmp] << endl;
    for(int i=0; i<n; i++){
        cout << tmp << " ";
        tmp=m[tmp];
    }
    cout << endl;
    return 0;
}