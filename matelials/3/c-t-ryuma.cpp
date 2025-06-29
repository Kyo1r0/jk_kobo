#include <bits/stdc++.h> //とりあえずグランディ数を求めている
using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++)
int mex(const unordered_set<int>& s) { //順番がないset sの値を参照
    int m = 0;
    while (s.count(m)) ++m;
    return m;
}



int main() {//コーナーザ馬
    int n;
    cin >> n; //求めたいグランディ数(正方形)
    vector<vector<int>> vec(n+1,vector<int>(n+1,0)); //配列の初期化
    vector<vector<int>> check(n+1,vector<int>(n+1,0)); //配列の初期化
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

            for (int k = 1; i - k >= 0 && j - k >= 0; ++k) {//左上
                m.insert(vec[i - k][j - k]);
            }

            
            

            vec[i][j] = mex(m);
        }
    }


    check[0][0]=1;
    for(int i=1;i<=n;i++){
        if(vec[i][0]==0)check[i][0]=1;
        if(vec[i-1][0]==0)check[i][0]=1; //上
        if(vec[0][i]==0)check[0][i]=1;
        if(vec[0][i-1]==0)check[0][i]=1;//左
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(vec[i][j]==0)check[i][j]=1;
            else{
                    
                        //上
                    if(vec[i-1][j]==0)check[i][j]=1;
                

                for (int k = 1; i - k >= 0 && j - k >= 0; ++k) {//左上
                    if(vec[i-k][j-k]==0)check[i][j]=1;
                }

                            //左
                    if(vec[i][j-1]==0)check[i][j]=1;
            
            

        }
    }
    }
    cout <<"コーナーザ竜馬のグランディ数"<<endl;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            cout << vec[i][j];
            if(j!=n)cout << " ";
            else cout << "\n";
        }
    }

    cout << "コーナーザ竜馬の各マスが一手でP局面になるのか" << endl;

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
