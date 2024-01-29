        #include <bits/stdc++.h>
        using namespace std;
        int main(){
            int n;
            cin >> n;
            vector<int> v(6,0);
            for(int i=0; i<n; i++){
                v[i]=i+1;
            }
            n%=30;
            for(int i=0; i<n; i++){
                int tmp = i%5;
                int e1 = v[tmp+1];
                int e2 = v[tmp+2];
                v[tmp+1]=e2;
                v[tmp+2]=e1;
            }          
            for(auto e : v){
                cout << e;
            }
            cout << endl;
        }