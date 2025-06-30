#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++)

int main() {
    int n;                // T の個数
    cout << "Tの個数n:";
    cin >> n;

    unordered_set<int> T; // 取れない集合（要素自体を入れる）
    T.reserve(n);

    cout << "Tの要素:";
    rep(i,n){
        int a; cin >> a;
        T.insert(a);
    }

    int goal;
    cout << "gの範囲:";
    cin >> goal;

    vector<int> g(goal+1,-1); // ここで確保
    int k = 0;                // 現在付与中のグランディ数

    while(true){
        // ① m = 未確定で最小の i
        int m = -1;
        for(int i=0;i<=goal;i++){
            if(g[i] < 0){ m = i; break; }
        }
        if(m == -1) break;        // 全部埋まった
        g[m] = k;

        // ② t ∈ T について条件を満たす m+t にも g = k
        for(int t : T){
            int pos = m + t;
            if(pos > goal || g[pos] != -1) continue;

            bool ok = true;
            for(int i=0;i<pos;i++){
                if(g[i] == k && !T.count(pos - i)){
                    ok = false; break;
                }
            }
            if(ok) g[pos] = k;
        }
        ++k;
    }

    // 出力
    rep(i,goal+1) cout << g[i] << '\n';
}
