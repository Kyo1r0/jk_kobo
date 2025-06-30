#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;                       // |T|
    cout << "Tの個数n:";  cin >> n;

    unordered_set<int> T;
    T.reserve(n);

    cout << "Tの要素:";
    for (int i = 0; i < n; ++i){
        int a; cin >> a;
        T.insert(a);
    }

    int goal;
    cout << "gの範囲:";   cin >> goal;

    vector<int> g(goal + 1, -1);          // g[0..goal]
    vector<int> vt(T.begin(), T.end());   // 昇順に並べ替え
    sort(vt.begin(), vt.end());

    int k = 0;                            // 現在付与中の Grundy 数
    while (true) {
        /*--- ① まだ未確定の最小 m を探す ---*/
        int m = -1;
        for (int i = 0; i <= goal; ++i) {
            if (g[i] == -1) { m = i; break; }
        }
        if (m == -1) break;               // 全部決まった
        g[m] = k;

        /*--- ② t ∈ T について g[m+t] を埋める ---*/
        for (int t : vt) {
            int pos = m + t;
            if (pos > goal || g[pos] != -1) continue; // 範囲外 or 既に決定

            bool ok = true;
            for (int i = 0; i < pos; ++i) {           // m' < pos
                if (g[i] == k && !T.count(pos - i)) { // (pos-m') ∈ T ?
                    ok = false; break;
                }
            }
            if (ok) g[pos] = k;
        }
        ++k;
    }

    /*--- 出力 ---*/
    for (int i = 0; i <= goal; ++i)
        cout << g[i]<< '\n';
    
    for (int i = 0; i <= goal; ++i)
        cout << g[i];
        
        cout<< '\n';
        return 0;
}
