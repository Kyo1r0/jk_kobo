#include <bits/stdc++.h>
using namespace std;
map<vector<string>, string> memo;
string generate_game_string(const vector<string>& board);


string join(const set<string>& s) {
    if (s.empty()) {
        return ""; //何もなかったら何も出さないということ
    }
    stringstream ss;
    for (auto it = s.begin(); it != s.end(); ++it) {
        if (it != s.begin()) {
            ss << ",";
        }
        ss << *it;
    }
    return ss.str();
}



string generate_game_string(const vector<string>& board) {
   
    if (memo.count(board)) { //メモ化再帰
        return memo[board];
    }

    int rows = board.size();
    if (rows == 0) return "0"; //{|}->0にした
    int cols = board[0].size();

    // 左右のプレイヤーの選択肢を格納する
    set<string> left_options;  // 黒 'B' の手
    set<string> right_options; // 白 'W' の手

    // 移動方向 (上, 下, 左, 右)
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    // 2. 盤面全体を探索し、すべての可能な手を探す
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            // --- 左プレイヤー (黒 'B') の手を探す ---
            if (board[r][c] == 'B') {
                for (int i = 0; i < 4; ++i) {
                    int jump_over_r = r + dr[i];
                    int jump_over_c = c + dc[i];
                    int land_on_r = r + 2 * dr[i];
                    int land_on_c = c + 2 * dc[i];

                    // ジャンプ可能かチェック
                    if (0 <= land_on_r  && land_on_r < rows && 0 <= land_on_c && land_on_c < cols &&
                        board[jump_over_r][jump_over_c] == 'W' && board[land_on_r][land_on_c] == '.') {
                        
                        vector<string> next_board = board;
                        int cur_r = r, cur_c = c;
                        // 連続ジャンプの処理
                        while (0 <= cur_r + 2 * dr[i]  && cur_r + 2 * dr[i] < rows &&
                               0 <= cur_c + 2 * dc[i]  && cur_c + 2 * dc[i] < cols &&
                               next_board[cur_r + dr[i]][cur_c + dc[i]] == 'W' &&
                               next_board[cur_r + 2 * dr[i]][cur_c + 2 * dc[i]] == '.') {
                            
                            next_board[cur_r][cur_c] = '.';
                            next_board[cur_r + dr[i]][cur_c + dc[i]] = '.'; // 飛び越えられた駒を消す
                            cur_r += 2 * dr[i];
                            cur_c += 2 * dc[i];
                            next_board[cur_r][cur_c] = 'B';
                        left_options.insert(generate_game_string(next_board));// 再帰呼び出し
                        }
                       
                    }
                }
            }
            // 右プレイヤー (白 'W') の手を探す 
            else if (board[r][c] == 'W') {
                for (int i = 0; i < 4; ++i) {
                     int jump_over_r = r + dr[i];
                    int jump_over_c = c + dc[i];
                    int land_on_r = r + 2 * dr[i];
                    int land_on_c = c + 2 * dc[i];

                    if (0 <= land_on_r  && land_on_r < rows && 0 <= land_on_c  && land_on_c < cols &&
                        board[jump_over_r][jump_over_c] == 'B' && board[land_on_r][land_on_c] == '.') {
                        
                        vector<string> next_board = board;
                        int cur_r = r, cur_c = c;
                        
                        while (0 <= cur_r + 2 * dr[i]  && cur_r + 2 * dr[i] < rows &&
                               0 <= cur_r + 2 * dr[i]  && cur_c + 2 * dc[i] < cols &&
                               next_board[cur_r + dr[i]][cur_c + dc[i]] == 'B' &&
                               next_board[cur_r + 2 * dr[i]][cur_c + 2 * dc[i]] == '.') {
                            
                            next_board[cur_r][cur_c] = '.';
                            next_board[cur_r + dr[i]][cur_c + dc[i]] = '.';// 飛び越えられた駒を消す
                            cur_r += 2 * dr[i];
                            cur_c += 2 * dc[i];
                            next_board[cur_r][cur_c] = 'W';
                             right_options.insert(generate_game_string(next_board)); //再帰呼び出し
                        }
                       
                    }
                }
            }
        }
    }
    

    string result = "{" + join(left_options) + "|" + join(right_options) + "}";
    if(result=="{|}") result ="0"; //重要で{|}を0に直している(定義から)
    memo[board] = result;//メモ化再帰
    return result; 
}


int main() {
    int a, b;
    cout << "盤面のサイズを入力してください" << endl;
    cout << "縦: ";
    cin >> a;
    cout << "横: ";
    cin >> b;

    vector<string> board(a);
    cout << "盤面を入力してください (B: 黒, W: 白, .: 空マス)" << endl;
    for (int i = 0; i < a; i++) {
        cin >> board[i];
    }
    
    cout << "\n--- 計算結果 ---" << endl;
    string ans = generate_game_string(board);
    cout << "この局面の値は: " << ans << endl;

    return 0;
}