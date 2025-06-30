#include <bits/stdc++.h>
using namespace std;

int mex(const unordered_set<int>& s) { //順番がないset sの値を参照
    int m = 0;
    while (s.count(m)) ++m;
    return m;
}

int main(){
    int n;
    cin >> n; //n個の文字のmexを求める
    unordered_set<int> m(n); 
    for(int i=0;i<n;i++){
        int a;
        cin >> a;
        m.insert(a);
    }
    cout << mex(m) << endl;
}

