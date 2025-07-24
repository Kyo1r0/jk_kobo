#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++)

int main() {
    int n;//n保持のn
    int w;//求めたい範囲w
    cout << "nを入力してください:";
    cin >> n;
    cout << "範囲を求めてください:";
    cin >> w;
    vector<vector<string>> g(w,vector<string>(w));
    for(int i=0;i<w;i++){
        for(int j=0;j<w;j++){
            int a= i^j;
            if (a<=n)g[i][j]= to_string(a);
            else g[i][j]="inf";

            cout << g[i][j];
            if(j!=n-1)cout << " ";
        }
        cout << endl;
    }

    return 0;
}