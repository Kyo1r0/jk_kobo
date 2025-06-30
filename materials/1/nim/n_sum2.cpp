#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++)



int main() { //C++のXORを使った　これが一番速い
    int a,b;
    cin >> a >> b;
    int ans = a ^ b;
    cout << ans << endl;
    return 0;
}