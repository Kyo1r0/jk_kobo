#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++)
int main() {
    int n,ans=0;
    cin >> n;
    vector<int> a(n);
    for(auto & e:a)cin >> e;
    sort(a.begin(),a.end());
    int fin= a[n-1];
    vector<bool> check(fin,0);
    for(int i=0;i<n;i++){
        check[a[i]]=1;
    }

    for(int i=0;i<=fin;i++){
        if(check[i]==0){
            ans = i;
            break;
        }
        ans = fin+1;
    }
    


    cout << ans << endl;
    return 0;
}