#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++)
static vector<vector<int>> memo; //既に出したものを保存しておく

int mex(const unordered_set<int>& s) { //順番がないset 最小除外数を返す
    int m = 0;
    while (s.count(m)) ++m;
    return m;
}


int sum(int a, int b){ //定義どおりの足し算
    if(a==b) return 0;
    if(a!=0 &&b==0) return a;
    if(a==0 && b!=0) return b;
    if(memo.empty()){ //配列を作成初期条件でつくる
        int N = max(a,b) +1;
        memo.assign(N,vector<int>(N,-1));
    }
    if(a < (int)memo.size() && b < (int)memo[a].size() && memo[a][b] != -1){ //既に求めているものがあったら返す
        return memo[a][b];
    }
    unordered_set<int> S; //mex({})の中かっこの中身
    for (int a2 = 0; a2 < a; ++a2) {
        for (int b2 = 0; b2 < b; ++b2) {
             int v1=sum(a2,b);
             int v2=sum(a,b2);
             S.insert(v1);
             S.insert(v2);
        }
    }

    int ans = mex(S);
    memo[a][b]=ans;
    return ans;
}

int main() {  //p31の定義に配列を追加し、高速にした
    int a,b;
    cin >> a >> b;
    cout << sum(a,b) << endl;
    return 0;
}