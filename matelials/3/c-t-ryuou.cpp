#include <bits/stdc++.h> //とりあえずグランディ数を求めている
using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++)
int mex(const unordered_set<int>& s) { //順番がないset sの値を参照
    int m = 0;
    while (s.count(m)) ++m;
    return m;
}



int main() { //コーナーザ竜王
    int n;
    cin >> n; //求めたいグランディ数(正方形)
    vector<vector<int>> vec(n+1,vector<int>(n+1,0)); //配列の初期化
    vector<vector<int>> check(n+1,vector<int>(n+1,0)); //配列の初期化
    vec[0][0]=0;
    for(int i=1;i<=n;i++) vec[0][i]=i,vec[i][0]=i; //外枠の値を決まる

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            unordered_set<int> m(n*n); 
            int x,y;
            x=j,y=i;
           for (int k = i - 1; k >= 0; --k) {//上
                m.insert(vec[k][j]);
            }
           for (int k = j - 1; k >= 0; --k) {//左
                m.insert(vec[i][k]);
            }
           m.insert(vec[i-1][j-1]);//左上
            vec[i][j] = mex(m);
        }
    }




    check[0][0]=1;
    for(int i=1;i<=n;i++){
        check[i][0]=1; //上 明らかに正しいから
        check[0][i]=1;//左　明らかに正しいから
    }

 
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(vec[i][j]==0)check[i][j]=1;
            for (int k = i - 1; k >= 0; --k) {//上
                    if(vec[k][j]==0)check[i][j]=1;
                }
            for (int k = j - 1; k >= 0; --k) {//左
                    if(vec[i][k]==0)check[i][j]=1;
                }
            if(vec[i-1][j-1]==0)check[i][j]=1; //左上
        }
    }


  cout <<"コーナーザ竜王のグランディ数"<<endl;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            cout << vec[i][j];
            if(j!=n)cout << " ";
            else cout << "\n";
        }
    }

    cout << "コーナーザ竜王の各マスが一手でP局面になるのか" << endl;

    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            cout << check[i][j];
            if(j!=n)cout << " ";
            else cout << "\n";
        }
    }

    int cnt_0=0;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            if(check[i][j]==0) cnt_0++;
        }
    }

    cout << "先手必勝でないマス(n->pができないマス)は" << cnt_0 << "個" << endl;
    return 0;
}
