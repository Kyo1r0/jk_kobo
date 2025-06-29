#include <bits/stdc++.h> //とりあえずグランディ数を求めている
using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++)
int mex(const unordered_set<int>& s) { //順番がないset sの値を参照
    int m = 0;
    while (s.count(m)) ++m;
    return m;
}



int main() { //コーナーザ金
    int n;
    cin >> n; //求めたいグランディ数(正方形)
    vector<vector<int>> vec(n+1,vector<int>(n+1,0)); //配列の初期化
    vec[0][0]=0;
    for(int i=1;i<=n;i++){ //外枠の値を決まる
        unordered_set<int> ml(n*n); 
        unordered_set<int> mu(n*n); 
        ml.insert(vec[0][i-1]);//左
        vec[0][i] = mex(ml);
        mu.insert(vec[i-1][0]);//上
        vec[i][0] = mex(mu);
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            unordered_set<int> m(n*n); 
            int x,y;
            x=j,y=i;
           m.insert(vec[i-1][j]); //上
           m.insert(vec[i][j-1]);//左
           m.insert(vec[i-1][j-1]);//左上
            vec[i][j] = mex(m);
        }
    }


    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            cout << vec[i][j];
            if(j!=n)cout << " ";
            else cout << "\n";
        }
        
        
    }
    
    return 0;
}