#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <sstream>

// using namespace std; はグローバルスコープでは非推奨なため、個別に宣言します
using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::set;
using std::map;
using std::stringstream;
using std::ofstream;

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
                        // ★修正点: 全ての連続ジャンプが終わった後に1回だけ再帰呼び出し
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
                        
                        while (r + 2 * dr[i] >= 0 && r + 2 * dr[i] < rows && cur_c + 2 * dc[i] >= 0 && cur_c + 2 * dc[i] < cols &&
                               next_board[cur_r + dr[i]][cur_c + dc[i]] == 'B' && next_board[cur_r + 2 * dr[i]][cur_c + 2 * dc[i]] == '.') {
                            
                            next_board[cur_r][cur_c] = '.';
                            next_board[cur_r + dr[i]][cur_c + dc[i]] = '.';
                            cur_r += 2 * dr[i];
                            cur_c += 2 * dc[i];
                            next_board[cur_r][cur_c] = 'W';
                        }
                         // ★修正点: 全ての連続ジャンプが終わった後に1回だけ再帰呼び出し
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

// チェッカー盤を生成する関数
vector<string> generate_checkerboard(int n) {
    vector<string> board(n, string(n, '.'));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            board[i][j] = ((i + j) % 2 == 0) ? 'B' : 'W';
        }
    }
    return board;
}

int main() {
    // CSVファイルを開く
    ofstream csv_file("konane_results.csv");
    if (!csv_file.is_open()) {
        cerr << "エラー: CSVファイルを開けませんでした。" << endl;
        return 1;
    }
    
    // CSVヘッダーを書き込む
    csv_file << "n,string_length\n";

    int max_n;
    cout << "実験を実行する最大のNを入力してください (例: 4): ";
    cin >> max_n;

    // N=2から指定された最大Nまでループ
    for (int n = 2; n <= max_n; ++n) {
        cout << "\n--- N = " << n << " の盤面を計算中... ---" << endl;
        
        memo.clear(); // 新しいサイズの計算の前にメモ化テーブルをクリア
        
        vector<string> board = generate_checkerboard(n);
        
        string ans = generate_game_string(board);
        
        // 結果をCSVファイルに書き込む
        csv_file << n << "," << ans.length() << "\n";
        
        // 結果を標準出力にも表示
        cout << "この局面の値は: " << ans << endl;
    }
    
    csv_file.close();
    cout << "\n実験結果を konane_results.csv に保存しました。" << endl;

    return 0;
}