#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++) // 雛形にあったため残しておきます

// ドミノの文字列を入力させる関数
string input_s(){
    while(true){
        string s;
        cout << "ドミノをいれてください(W,Bのみで)" << endl; 
        cin >> s;

        bool check=true;
        for(char &e:s) {
            if (e != 'W' && e != 'B') {
                check = false;
                break;
            }
        }
        if(check) return s;
        else cout << "W,B以外の文字は入れないでください" << endl;
    }
}

// 1ターン分のゲーム進行を処理する関数
string game(int cnt, string s){
    char player = (cnt % 2 == 0) ? 'W' : 'B'; // ターン数からプレイヤーを決定
    int pos;
    char dir;

    while(true) {
        // --- 盤面表示 ---
        cout << "\n-------------------------------\n";
        cout << "現在の盤面:   " << s << endl;
        cout << "インデックス: ";
        for(int i = 0; i < s.length(); ++i) cout << (i+1);
        cout << endl;
        cout << "プレイヤー " << player << " のターンです。" << endl;

        // --- 入力 ---
        cout << "倒すドミノを選択してください(数字): ";
        cin >> pos;
        cout << "倒す方向を選択してください(L/R): ";
        cin >> dir;

        // --- 入力値の検証 ---
        dir = toupper(dir); // L, Rを大文字に統一
        int idx = pos - 1; // 1-based indexを 0-basedに変換

        if (pos < 1 || pos > s.length()) {
            cout << "エラー: 番号が範囲外です。\n";
        } else if (s[idx] != player) {
            cout << "エラー: 自分の色のドミノを選択してください。\n";
        } else if (dir != 'L' && dir != 'R') {
            cout << "エラー: 方向は L または R で入力してください。\n";
        } else if (dir == 'L' && (idx == 0 || s[idx-1] == '.')) {
            cout << "エラー: その方向には倒せません。\n";
        } else if (dir == 'R' && (idx == s.length() - 1 || s[idx+1] == '.')) {
            cout << "エラー: その方向には倒せません。\n";
        } else {
            // 全てのチェックをパスしたらループを抜ける
            break;
        }
        cout << "もう一度入力してください。\n";
    }

    // --- 盤面の更新 ---
    int idx = pos - 1;
    s[idx] = '.'; // 倒したドミノは消える
    if (dir == 'L') {
        s[idx-1] = player;
    } else { // dir == 'R'
        s[idx+1] = player;
    }
    return s;
}

// 次のプレイヤーが動けるかどうかをチェックし、ゲームが終了したかを判定する関数
// true: ゲーム続行 / false: ゲーム終了
bool check_fin(int cnt, string s){
    char next_player = ((cnt + 1) % 2 == 0) ? 'W' : 'B'; // 次のプレイヤーを決定

    // 次のプレイヤーが動かせる手があるか探す
    for(int i=0; i < s.length(); i++){
        if(s[i] == next_player){
            // 左に倒せるか
            if(i > 0 && s[i-1] != '.'){
                return true; // 動ける手があったのでゲーム続行
            }
            // 右に倒せるか
            if(i < s.length() - 1 && s[i+1] != '.'){
                return true; // 動ける手があったのでゲーム続行
            }
        }
    }

    // ループを抜けた = 動ける手が一つもなかった
    return false; // ゲーム終了
}

int main() {
    string s = input_s();
    int cnt = 0;

    // 先行プレイヤーの選択
    while(true){
        cout << "先攻プレイヤーを選択してください(W,B): ";
        char f;
        cin >> f;
        f = toupper(f);
        if(f == 'W') break;
        else if(f == 'B') {
            cnt++;
            break;
        }
        else cout << "W,B以外の文字は入れないでください" <<endl;
    }

    // メインのゲームループ
    while(true){
        s = game(cnt, s);

        // 次のプレイヤーが動けなければゲーム終了
        if ( !check_fin(cnt, s) ) {
            break;
        }
        cnt++; // ターンを進める
    }

    // --- 勝者発表 ---
    char winner = (cnt % 2 == 0) ? 'W' : 'B';
    cout << "\n===============================\n";
    cout << "ゲーム終了！\n";
    cout << "最終盤面: " << s << endl;
    cout << "勝者はプレイヤー " << winner << " です！\n";
    cout << "===============================\n";

    return 0;
}