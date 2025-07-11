#include <bits/stdc++.h>

// bits/stdc++.h を使う場合、std名前空間をまとめて使用することが多い
using namespace std;

// 計算済みの局面とその値を保存するメモ化テーブル
map<vector<string>, string> memo;

// 関数の前方宣言
string generate_game_string(const vector<string>& board);

// set<string>の要素を","で連結するヘルパー関数
string join(const set<string>& s) {
    if (s.empty()) {
        return "";
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

/**
 * @brief 一般化コナネの盤面からそのゲームの値を文字列として再帰的に生成する
 * @param board 現在の盤面状態
 * @return ゲームの値を表す文字列
 */
string generate_game_string(const vector<string>& board) {
    if (memo.count(board)) {
        return memo[board];
    }

    int rows = board.size();
    if (rows == 0) return "0";
    int cols = board[0].size();

    set<string> left_options;
    set<string> right_options;
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            // --- 左プレイヤー (黒 'B') の手 ---
            if (board[r][c] == 'B') {
                for (int i = 0; i < 4; ++i) {
                    if (r + 2 * dr[i] >= 0 && r + 2 * dr[i] < rows && c + 2 * dc[i] >= 0 && c + 2 * dc[i] < cols &&
                        board[r + dr[i]][c + dc[i]] == 'W' && board[r + 2 * dr[i]][c + 2 * dc[i]] == '.') {
                        
                        vector<string> next_board = board;
                        int cur_r = r, cur_c = c;
                        
                        // 連続ジャンプの処理
                        while (cur_r + 2 * dr[i] >= 0 && cur_r + 2 * dr[i] < rows && cur_c + 2 * dc[i] >= 0 && cur_c + 2 * dc[i] < cols &&
                               next_board[cur_r + dr[i]][cur_c + dc[i]] == 'W' && next_board[cur_r + 2 * dr[i]][cur_c + 2 * dc[i]] == '.') {
                            
                            next_board[cur_r][cur_c] = '.';
                            next_board[cur_r + dr[i]][cur_c + dc[i]] = '.';
                            cur_r += 2 * dr[i];
                            cur_c += 2 * dc[i];
                            next_board[cur_r][cur_c] = 'B';
                        }
                        // 全ての連続ジャンプが終わった後に1回だけ再帰呼び出し
                        left_options.insert(generate_game_string(next_board));
                    }
                }
            }
            // --- 右プレイヤー (白 'W') の手 ---
            else if (board[r][c] == 'W') {
                for (int i = 0; i < 4; ++i) {
                    if (r + 2 * dr[i] >= 0 && r + 2 * dr[i] < rows && c + 2 * dc[i] >= 0 && c + 2 * dc[i] < cols &&
                        board[r + dr[i]][c + dc[i]] == 'B' && board[r + 2 * dr[i]][c + 2 * dc[i]] == '.') {
                        
                        vector<string> next_board = board;
                        int cur_r = r, cur_c = c;
                        
                        while (cur_r + 2 * dr[i] >= 0 && cur_r + 2 * dr[i] < rows && cur_c + 2 * dc[i] >= 0 && cur_c + 2 * dc[i] < cols &&
                               next_board[cur_r + dr[i]][cur_c + dc[i]] == 'B' && next_board[cur_r + 2 * dr[i]][cur_c + 2 * dc[i]] == '.') {
                            
                            next_board[cur_r][cur_c] = '.';
                            next_board[cur_r + dr[i]][cur_c + dc[i]] = '.';
                            cur_r += 2 * dr[i];
                            cur_c += 2 * dc[i];
                            next_board[cur_r][cur_c] = 'W';
                        }
                        // 全ての連続ジャンプが終わった後に1回だけ再帰呼び出し
                        right_options.insert(generate_game_string(next_board));
                    }
                }
            }
        }
    }
    
    string result = "{" + join(left_options) + "|" + join(right_options) + "}";
    if (result == "{|}") {
        result = "0";
    }
    memo[board] = result;
    return result; 
}

/**
 * @brief 3xNの「タイルパターン」盤面を生成する
 * @param rows 盤面の行数 (3を想定)
 * @param cols 盤面の列数 (3の倍数を想定)
 * @return 生成された盤面
 */
vector<string> generate_tiled_pattern_board(int rows, int cols) {
    vector<string> board(rows, string(cols, '.'));
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int local_row = i % 3;
            int local_col = j % 3;
            if (local_row == 1) {
                if (local_col == 0) board[i][j] = 'B';
                if (local_col == 1) board[i][j] = 'W';
            } else if (local_row == 2) {
                if (local_col == 0) board[i][j] = 'W';
                if (local_col == 1) board[i][j] = 'B';
            }
        }
    }
    return board;
}

int main() {
    // --- ファイルの準備 ---
    ofstream csv_file("konane_3xN_results.csv");
    if (!csv_file.is_open()) {
        cerr << "エラー: CSVファイルを開けませんでした。" << endl;
        return 1;
    }
    
    // ★修正点: 出力ファイルを .txt に変更
    ofstream txt_file("konane_3xN_results.txt");
    if (!txt_file.is_open()) {
        cerr << "エラー: TXTファイルを開けませんでした。" << endl;
        return 1;
    }

    // --- ヘッダーの書き込み ---
    csv_file << "n,string_length\n";
    
    // ★修正点: TeXのヘッダーを削除

    // --- ユーザー入力 ---
    int max_n;
    cout << "実験を実行する最大のNを入力してください (3の倍数): ";
    cin >> max_n;

    if (max_n < 3 || max_n % 3 != 0) {
        cerr << "エラー: Nは3以上の3の倍数である必要があります。" << endl;
        return 1;
    }

    // --- 実験ループ ---
    for (int n = 3; n <= max_n; n += 3) {
        cout << "\n--- 3 x " << n << " の盤面を計算中... ---" << endl;
        
        memo.clear();
        
        vector<string> board = generate_tiled_pattern_board(3, n);
        
        string ans = generate_game_string(board);
        
        // CSVファイルへの出力
        csv_file << n << "," << ans.length() << "\n";
        
        // ★修正点: TXTファイルへの出力形式を変更
        txt_file << "N = " << n << "\n"
                 << "String Length: " << ans.length() << "\n"
                 << "Value: " << ans << "\n\n"
                 << "----------------------------------------\n\n";
        
        // 標準出力への進捗表示
        cout << "N = " << n << " の計算が完了しました。" << endl;
    }
    
    // --- ファイルの後処理 ---
    csv_file.close();
    txt_file.close();
    
    cout << "\n実験結果を konane_3xN_results.csv および konane_3xN_results.txt に保存しました。" << endl;

    return 0;
}
