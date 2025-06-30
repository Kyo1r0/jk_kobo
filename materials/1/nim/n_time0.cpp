#include <bits/stdc++.h>
using namespace std;
//真ん中が毒のチョンプ
static vector<vector<int>> memo; //既に求めたものを保存している

int mex(const unordered_set<int>& s) { //順番がないset 最小除外数を返す
    int m = 0;
    while (s.count(m)) ++m;
    return m;
}


int nim_times(int a, int b) { //nim積を計算

    if (a == 0 || b == 0) return 0;     // 終端条件
    if (memo.empty()) { //メモの初期化(一番はじめのみ)全て-1入れる
        int N = max(a, b) + 1;
        memo.assign(N, vector<int>(N, -1));
    }

    if (a < (int)memo.size() && b < (int)memo[a].size() && memo[a][b] != -1)
        return memo[a][b];

    unordered_set<int> S; //最後に関数mexに入れるための集合
    for (int a2 = 0; a2 < a; ++a2) {
        for (int b2 = 0; b2 < b; ++b2) {
            int v = nim_times(a2, b) ^ nim_times(a, b2) ^ nim_times(a2, b2);
            S.insert(v);
        }
    }

    int result = mex(S);
    memo[a][b] = result;
    return result;
}

int main() {
    int a, b;
    cin >> a >> b;
    cout << nim_times(a, b) << "\n";
    return 0;
}



