#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++)

string input_s(){
    while(true){
    string s;
    cout << "ドミノをいれてください(W,Bのみで)" << endl; 
    cin >> s;

    bool  check=true;
    for(char &e:s) {
        if (e != 'W' && e != 'B') {
                check = false; // 不正な文字が見つかった
                break; // ループを抜ける
            }
    }
    if(check)return s;
    else cout << "W,B以外の文字は入れないでください" << endl;
    }
}


string game(int cnt,string s){
        char player = (cnt % 2 == 0) ? 'W' : 'B'; // ターン数からプレイヤーを決定
        int pos;
        char dir;

    while(true) {
        //盤面表示
        cout << "\n-------------------------------\n";
        cout << "現在の盤面:   " << s << endl;
        cout << "インデックス: ";
        for(int i = 0; i < s.length(); ++i) cout << (i+1);
        cout << endl;
        cout << "プレイヤー " << player << " のターンです。" << endl;

        //入力
        cout << "倒すドミノを選択してください(数字): ";
        cin >> pos;

        if (cin.fail()) {
            cout << "エラー: 数字を入力してください。\n";
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 不正な入力をバッファから捨てる
            continue; 
        }
        
        cout << "倒す方向を選択してください(L/R): ";
        cin >> dir;

        //入力値の検証
        dir = toupper(dir); // L, Rを大文字にする
        int pos2 = pos - 1;

        if (pos < 1 || pos > s.length()) {
            cout << "エラー: 番号が範囲外です。\n";
        } else if (s[pos2] != player) {
            cout << "エラー: 自分の色のドミノを選択してください。\n";
        } else if (dir != 'L' && dir != 'R') {
            cout << "エラー: 方向は L または R で入力してください。\n";
        } else {
            // 全てのチェックをパスしたらループを抜ける
            break;
        }
        cout << "もう一度入力してください。\n";

       

    }
         int pos2 = pos - 1;
     //ドミノを倒す
        for(int i=0;i<s.size();i++){
            if(dir=='R'&&pos2<=i) s[i]='.';
            else if(dir =='L'&& pos2>=i) s[i] ='.';
        }
        return s;    
}


bool check_fin(int cnt, string s){
    char next_player = ((cnt + 1) % 2 == 0) ? 'W' : 'B'; // 次のプレイヤーを決定

    
    for(int i=0; i < s.length(); i++){// 次のプレイヤーが動かせる手があるか探す
        if(s[i] == next_player){
            
            if(i > 0 && s[i-1] != '.'){// 左に倒せるか
                return true; 
            }
          
            if(i < s.length() - 1 && s[i+1] != '.'){// 右に倒せるか
                return true; 
            }
        }
    }

    return false; // ゲーム終了
}



int main() {
    string s = input_s();
    //cout << s << endl;
    int cnt =0; //先行後攻を管理
    while(true){
        cout << "先攻プレイヤーを選択してください(W,B):";
        char f;
        cin >> f;
        if(f=='W') break;
        else if(f=='B'){
            cnt++;
            break;
        }
        else cout << "W,B以外の文字は入れないでください" <<endl;
    }
    bool flag = true;

    while(true){ // メインのゲームループ
        s = game(cnt, s);
        if ( !check_fin(cnt, s) ) {
            break;
        }
        cnt++; // ターンを進める
    }

    //ゲーム終了
    char winner = (cnt % 2 == 0) ? 'W' : 'B';
    cout << "\n===============================\n";
    cout << "ゲーム終了！\n";
    cout << "最終盤面: " << s << endl;
    cout << "勝者はプレイヤー " << winner << " です！\n";
    cout << "===============================\n";

    return 0;
}