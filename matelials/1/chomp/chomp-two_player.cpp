#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++)


vector<vector<int>> board;   
int H,W; 

int cnt=0; //回数をカウントする。奇数は先手、偶数は後手

void mk_choco(int a,int b){ //初期配列設定
    H=a; W=b;
    board.assign(H, vector<int>(W,1)); // 1:残っている, 0:食べられた borad[H-1][0]がどく
}



void show_choco(){ //チョコの表示
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            cout << board[i][j];
        }
        cout << endl;
    }

    
    
}   

void eat_choco(int a,int b){ //チョコ食べる たべるときは座標で見ている(毒が(0,0))
    for(int i=0;i<H-b;i++){
        for(int j=a;j<W;j++){
            board[i][j]=0;
        }
    }

    if(board[H-1][0]==0 && cnt%2==1){
        cout << "先手の負け" << endl;
    }

    if(board[H-1][0]==0 &&cnt%2==0){
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
    
 
    while(board[H-1][0]!=0){ //毒が食べられない条件で回す
        cnt++;
        int x,y;
        show_choco();
       cout << ((cnt % 2 == 1) ? "先手は" : "後手は");
        cout << "食べる座標を入力してください(毒は0,0)"<<endl;
        cout << "x座標:";
        cin >> x;
        cout << "y座標:";
        cin >> y;

        if(x<0||x>=W||y<0||y>=H){ 
            cout <<"error-----------------範囲外------------------error\n"; 
            cnt--;
            continue; 
        }
        eat_choco(x,y);
        
    }


    return 0;
}