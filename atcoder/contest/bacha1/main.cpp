#include <bits/stdc++.h>
using namespace std;
int main(){
    int n;
    cin >> n;
    vector<int> a(n,-1);
    vector<int> b(n,-1);
    vector<int> c;
    for(int i=0; i<n; i++)cin >> a[i];
    for(int i=0; i<n; i++)cin >> b[i];
    vector<int> tmp1;
    vector<int> tmp2;
    for(int i=0; i<n; i++){
        tmp1.push_back(a[i]);
        tmp2.push_back(b[i]);
        sort(tmp1.begin(),tmp1.end());
        sort(tmp2.begin(),tmp2.end());
        int tmp=0;
        if(i==0)tmp=a[0]*b[0];
        else long long int tmp = max(tmp1[i]*tmp2[i],tmp1[i-1]*tmp2[i]);
        c.push_back(tmp);
        cout << tmp1[i]*tmp2[i] << endl;
    }
    // for(auto e:tmp2) cout << e << " ";
    cout << endl;
    // for(int i=0; i<c.size(); i++)cout << c[i] << " ";
    // cout << endl;
    return 0;
}