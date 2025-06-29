//g++ -std=c++17 -Wall -Wextra chomp.cpp -o chomp でビルドする
#include <bits/stdc++.h>
#include <stack>
using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++)

int cnt=0; //回数をカウントする。奇数は先手、偶数は後手
vector<vector<int>> board;   
int H,W; 


std::stack<pair<int,int>> stuck; //手を保存するためのスタックを作った


 


void mk_choco(int a,int b){ //初期配列設定
    H=a; W=b;
    board.assign(H, vector<int>(W,1)); // 1:残っている, 0:食べられた borad[H-1][0]がどく
}



void show_choco(){ //チョコの表示
    for(int i=0;i<H;i++){
          /*cout << H-i<<"+";*/
        for(int j=0;j<W;j++){
            cout << ((i == H-1 && j == 0)? 'p' : (board[i][j] ? '1' : '0'));
        }
        cout << endl;
    } 
    /*cout << "  " ;
    for(int i=0;i<W;i++){
        cout << "+";
    } 
        cout << endl;
    cout << "  ";
    for(int i=0;i<W;i++){
        cout << i+1;
    }
    cout << endl;
    */
}   

void eat_choco(int x,int y){ //チョコ食べる たべるときは座標で見ている(毒が(0,0)) また、スタックに追加
    stuck.push({x,y}); 
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

void throw_up_choco(int x, int y){
    for(int i = 0; i < H-y; i++){
        for(int j = x+1; j < W; j++){
            board[i][j] = 1;
        }
    }  
}


void back(){ //x座標に-1を入れたら作動する
    if(stuck.empty()){
        cout << "もう戻れません\n";
        cnt--;
        return;
    }
    auto [x1,y1] = stuck.top();
    stuck.pop();
    auto [x2,y2] = stuck.top();
    stuck.pop();
    throw_up_choco(x1,y1);
    board[H-y2-1][x2]=1;
    eat_choco(x2,y2);
    cnt -=2;
}

void check_choco(){
    if(board[H-1][0]==0 && cnt%2==1){
        show_choco();
        cout << "先手の負け" << endl;
    }

    if(board[H-1][0]==0 &&cnt%2==0){
        show_choco();
        cout << "後手の負け" << endl;
    }
}

int str(){ //戦略を入れる
    return 0;
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
       cout << ((cnt % 2 == 1) ? "先手は" : "後手は");
        cout << "食べる座標を入力してください(毒(p)のマスは(1,1))"<<endl;
        cout << "x座標:";
        cin >> x;
        if(x==-1){ //1手戻れる
            back();
            continue;
        }
         if(x<0||x-1>=W){ 
            cout <<"error-----------------範囲外------------------error\n"; 
            cnt--;
            continue; 
        }
        cout << "y座標:";
        cin >> y;
        
        if(y<0||y-1>=H){ 
            cout <<"error-----------------範囲外------------------error\n"; 
            cnt--;
            continue; 
        }
        
        eat_choco(x-1,y-1);
        check_choco();
    }


    return 0;
}