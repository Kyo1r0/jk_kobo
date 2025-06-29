#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++)
int main() {
    unordered_set<int> T={1,2,3,4,5};
    for(int t:T){
        cout << t;
    }
    cout << "\n";
    unordered_set<char> C={'a','b','c'};
    for(char c:C) cout << c;
    cout << "\n";
    return 0;
}