//g++ -std=c++17 -Wall -Wextra vs-cpu1.cpp -o vs-cpu1 でビルドする
//「待った」ができるようにしたい　実装は初期条件にしてキューから
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


void str() {//先手(CPU)の戦略:残っているマスをランダムに１つ食べる。ただし、そこを食べた結果、盤面が１列ストリップ状になる手は避ける」
    vector<pair<int,int>> candidates;
    candidates.reserve(H * W);
    for (int r = 0; r < H; r++) {
        for (int c = 0; c < W; c++) {// 毒の位置 (H-1,0) は除外
            if (r == H - 1 && c == 0) continue;
            if (board[r][c] == 1) {
                candidates.emplace_back(r, c);
            }
        }
    }

    // 2. 「１列ストリップ状になる手」を除外
    auto isOneColumnAfter = [&](int rr, int cc) {
        // ここでは、(rr,cc) を食べたあとに残る盤面が
        // "列 c>=1 がすべて 0 になる" →「c=0 列だけが残る 1 列形」かどうかを判定する。
        //
        // Chomp のルールに従って (rr,cc) を食べると、
        //  「r<=rr かつ c>=cc」の部分がすべて 0 になる。
        //  そのため、残るマスは「r>rr の行にかつ c<cc」の部分。
        //
        // すべて r>rr かつ c<cc の範囲で、c>=1 のマスが1つでも残っていれば
        // 「１列形 (c=0 だけ)」にはならない。なければ「１列形になる」。
        //
        for (int r2 = rr + 1; r2 < H; r2++) {
            for (int c2 = 1; c2 < cc; c2++) {
                // c2 < cc: かつ c2>=1 なので「残る可能性がある列」をチェック
                if (board[r2][c2] == 1) return false; // c>=1 のマスが残る → １列形にならない
            }
        }
        // もし上ループで一度も return しなかったら
        // c>=1 の残るマスが一切ない → 残るのは c=0 列のみ → 「１列ストリップ状」
        return true;
    };

    vector<pair<int,int>> filtered;
    filtered.reserve(candidates.size());
    for (auto &p : candidates) {
        int r = p.first;
        int c = p.second;
        // 「(r,c) を食べると１列形になるか？」をテスト
        if (!isOneColumnAfter(r, c)) {
            filtered.emplace_back(r, c);
        }
    }

    // 3. フィルタリング後の候補リストが空なら、仕方なく元の候補からランダムに取る
    vector<pair<int,int>> &pool = (filtered.empty() ? candidates : filtered);

    if (pool.empty()) {
        printf("CPU は 毒のチョコを食べた\n");
        eat_choco(0,0);
        check_choco();
        return;
    }

    // 4. ランダムに１つ選ぶ
    int idx = rand() % static_cast<int>(pool.size());
    int rr = pool[idx].first;
    int cc = pool[idx].second;

    // 5. 実際に食べる。eat_choco は (x:列, y:行 from 0-based/bottom-based) を期待しているため、
    //    r=board上の「行インデックス = 0:上行／H-1:下行」 → y = H-1 - r で変換
    int y = H -1 - rr;
    int x = cc;

    eat_choco(x, y);

    // ログ出力：人間にわかりやすいように 1-based 座標で表示
    printf("CPU は x座標 %d, y座標 %d のチョコを食べた\n", x + 1, y + 1);

    check_choco();
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