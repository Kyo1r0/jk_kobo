//g++ -std=c++17 -Wall -Wextra vs-cpu-maxmin.cpp -o maxmin でビルドする
//「待った」ができるようにしたい　実装は初期条件にしてキューから
//動いた
#include <bits/stdc++.h>
#include <stack>
#include <queue>
using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++)

int cnt=0; //回数をカウントする。奇数は先手、偶数は後手
vector<vector<int>> board;   
int H,W; 


std::queue<pair<int,int>> q; //手を保存するためのキュー

 


void mk_choco(int a,int b){ //初期配列設定
    H=a; W=b;
    board.assign(H, vector<int>(W,1)); // 1:残っている, 0:食べられた borad[H-1][0]がどく
    board[H-1][0]=2;
}



void show_choco(){ //チョコの表示
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            cout << ((i == H-1 && j == 0)? 'p' : (board[i][j] ? '1' : '0'));
        }
        cout << endl;
    } 
}   

void eat_choco(int x,int y){ //チョコ食べる たべるときは座標で見ている(毒が(0,0)) また、スタックに追加
    q.push({x,y}); 
    if(board[H-y-1][x]==0&&cnt%2==1){
        cout << "CPUの不具合が生じました" << endl;
        return;
    }
    if(board[H-y-1][x]==0){
        cnt--;
        cout << "!!!warning!!!--------既に食べてます!!--------!!!warning!!!" << endl;
        return;
    }
    for(int i=0;i<H-y;i++){
        for(int j=x;j<W;j++){
            board[i][j]=0;
        }
    }    
}




void back(){ //x座標に-1を入れたら作動する
    if(q.empty()){
        cout << "もう戻れません\n";
        cnt--;
        return;
    }
    mk_choco(H,W); //初期化
    for(int i=0;i<cnt-2;i++){
        auto[x,y]= q.front();
        eat_choco(x,y);
    }
    cnt -=2;
}

void check_choco(){
    if(board[H-1][0]==0 && cnt%2==1){
        show_choco();
        cout << "CPUの負け" << endl;
    }

    if(board[H-1][0]==0 &&cnt%2==0){
        show_choco();
        cout << "プレイヤーの負け" << endl;
    }
}

int M_INF=-1000000;
int INF = 1000000;
int eat_img(int x,int y,vector<vector<int>> a){ //チョコ食べたとして残ったチョコを返す
    vector<vector<int>> b(H,vector<int>(W));;
    int cnt =0;
    for(int i=0;i<H;i++){ //コピー
        for(int j=0;j<W;j++){
            b[i][j] = a[i][j];
        }
    }   
    
    for(int i=0;i<=y;i++){ //1食べる
        for(int j=x;j<W;j++){
            b[i][j]=0;
        }
    }  

    for(int i=0;i<H;i++){ //カウント
        for(int j=0;j<W;j++){
            if(b[i][j]==1)cnt++;
        }
    }  
    
    return cnt;
}

int search_min(int x,int y){ //一回食べて、相手の出方を全通り試してその最小値を返す(最小値が最善手)
    vector<vector<int>> check_min(H,vector<int>(W,INF));
    vector<vector<int>> Im_board1(H,vector<int>(W));

    for(int i=0;i<H;i++){ //コピー 　これは左上から見ている
        for(int j=0;j<W;j++){
            Im_board1[i][j]=board[i][j];
        }
    }

    for(int i=0;i<=y;i++){ //1回目の食べる(CPU)
        for(int j=x;j<W;j++){
            Im_board1[i][j]=0;
        }
    }
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            if(Im_board1[i][j]==1){
               check_min[i][j]= eat_img(j,i,Im_board1); //2回目の食べるところ(人間の手を全通り試す)
            }
        }
    }

    int ans=INF;
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            ans = min(ans,check_min[i][j]);
        }
    }

    return ans;
}


void str() { //max-min法を用いる また、毒のマスを2にしている。全探索で効いてくる ここでは左上を00にしている最後に変換
    vector<vector<int>> check_max(H,vector<int>(W,M_INF));
    int cnt_0=0;
    for(int i=0;i<H;i++){ //左上から見ている
        for(int j=0;j<W;j++){
            if(board[i][j]==1){
                check_max[i][j]= search_min(j,i);
                cnt_0++;
            }
        }
    }
    if(cnt_0==0){
        eat_choco(0, 0);

        // ログ出力：人間にわかりやすいように 1-based 座標で表示
        printf("CPU は 毒のチョコを食べた\n");

        check_choco();
    }
    else{
        int ans =0;
        for(int i=0;i<H;i++){ //最大値求めた
            for(int j=0;j<W;j++){
                ans =max(ans,check_max[i][j]);
            }
        }
        int x,y;
        for(int i=0;i<H;i++){ //最大値の場所探した
            for(int j=0;j<W;j++){
                if(check_max[i][j]==ans){
                    x=j;
                    y=i;
                    break;
                }
            }
        }

        
        y= (H - 1) - y;

        eat_choco(x, y);

    // ログ出力：人間にわかりやすいように 1-based 座標で表示
        printf("CPU は x座標 %d, y座標 %d のチョコを食べた\n", x + 1, y + 1);

        check_choco();
    }
}




int main() {
    cout << "初期配列を設定します(a×b)" << endl;
    int a,b; 
    cout << "行:";
    cin >> a ;
    cout << "列:";
    cin >> b;
    mk_choco(a,b);
    
    cout << "毒のチョコ(p)を食べたら負け" <<endl;

    while(board[H-1][0]!=0){ //毒が食べられない条件で回す
        cnt++;
        int x,y;
        show_choco();
        if(cnt %2==1){
            str();
        }
        else{
        cout << "プレイヤーは食べる座標を入力してください(毒(p)のマスは(1,1))"<<endl;
        cout << "x座標:";
        cin >> x;
        if(x==-1){ //1手戻れる
            back();
            continue;
        }
         if(x<=0||x-1>=W){ 
            cout <<"error-----------------範囲外------------------error\n"; 
            cnt--;
            continue; 
        }
        cout << "y座標:";
        cin >> y;
        
        if(y<=0||y-1>=H){ 
            cout <<"error-----------------範囲外------------------error\n"; 
            cnt--;
            continue; 
        }
        
        eat_choco(x-1,y-1);
        check_choco();
        }
    }


    return 0;
}