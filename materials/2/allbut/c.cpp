#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++)


int main() {
    
    int n; //Tの個数
    int goal; //終わりを作る どこまでもとめるか

    cout << "gの範囲:";
    cin >> goal; //どこまでgを求めたいか

    cout << "Tの個数n:";
    cin >> n; 
    
    unordered_set<int> T(n); //取れない集合Tを作る
    vector<int> g(goal+1,-1); //グランディ数を入れる配列
    int k=0; //グランディ数の値

    cout << "Tの要素:";
    for(int i=0;i<n;i++){ //Tを順序無し集合に入れる
        int a;
        cin >> a;
        T.insert(a); 
    }

    vector<int> vt(T.begin(), T.end());   // Tを昇順に並べ替え(2個目の条件で使う)
    sort(vt.begin(), vt.end());
    


   while(true){ //全部埋まるまで回す
    int m=-1;
    for(int i=0;i<=goal;i++){ //1つ目のg(m)=k
        if(g[i]==-1){
            m=i;
            break;
        }
    }
    if(m == -1) break;        // 終了条件:全部埋まったとき
    g[m]=k;//値確定1つめ
    for (int t : vt) { //Tで回すと後ろからになる (unoder-test.cpp)で確認
            int pos = m + t;
            if (pos > goal || g[pos] != -1) continue; // 範囲外 or 既に決定

            bool ok = true;
            for (int i = 0; i < pos; ++i) {           // m' < pos
                if (g[i] == k && !T.count(pos - i)) { // (pos-m')がTかどうか?
                    ok = false; break;
                }
            }
            if (ok) g[pos] = k;//2個目の値確定
        }

    
    //cout << k << endl;
    k++;    
   }

   
    


   for (int i = 0; i <= goal; ++i)
        cout << g[i]<< '\n';
    
    for (int i = 0; i <= goal; ++i)
        cout << g[i];
        
        cout<< '\n';
        return 0;
    
    return 0;
}