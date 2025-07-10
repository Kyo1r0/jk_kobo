#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdexcept>

// string_viewはC++17から。文字列のスライスを効率的に扱える
#include <string_view>

using namespace std;

// 前方宣言
struct GameNode;

// 計算済みの局面を保存するメモ化テーブル
map<string, GameNode*> memo;

// 帰結類
enum class Outcome { UNKNOWN, N, P, L, R };

// ゲームの局面を表すノード
struct GameNode {
    vector<GameNode*> left_options;
    vector<GameNode*> right_options;
    Outcome outcome = Outcome::UNKNOWN;
    string str_rep; // このノードの文字列表現
};

// Outcomeを文字に変換
char outcome_to_char(Outcome o) {
    switch (o) {
        case Outcome::N: return 'N';
        case Outcome::P: return 'P';
        case Outcome::L: return 'L';
        case Outcome::R: return 'R';
        default: return '?';
    }
}

// 文字列をパースしてゲーム木のノードを返す再帰関数
GameNode* parse_game_string(string_view s) {
    // "0"は"{|}"のエイリアスとして特別扱い
    if (s == "0") {
        s = "{|}";
    }

    // メモ化チェック
    string s_key(s);
    if (memo.count(s_key)) {
        return memo[s_key];
    }

    // 基本的な形式チェック
    if (s.length() < 2 || s.front() != '{' || s.back() != '}') {
        throw invalid_argument("Invalid game string format: " + string(s));
    }

    auto* node = new GameNode();
    node->str_rep = s_key;
    memo[s_key] = node;

    // 中身の部分文字列を取得
    string_view content = s.substr(1, s.length() - 2);
    if (content.empty()) { // "{}" のような無効な形式
         return node;
    }

    // メインの'|'を探す
    size_t pipe_pos = string_view::npos;
    int brace_level = 0;
    for (size_t i = 0; i < content.length(); ++i) {
        if (content[i] == '{') brace_level++;
        else if (content[i] == '}') brace_level--;
        else if (content[i] == '|' && brace_level == 0) {
            pipe_pos = i;
            break;
        }
    }

    if (pipe_pos == string_view::npos) {
        throw invalid_argument("Main separator '|' not found in: " + string(content));
    }

    // 左右の選択肢の部分に分割
    string_view left_part = content.substr(0, pipe_pos);
    string_view right_part = content.substr(pipe_pos + 1);

    // ヘルパー関数: 選択肢を分割して再帰的にパースする
    auto parse_options = [&](string_view part, vector<GameNode*>& options) {
        if (part.empty()) return;
        size_t start = 0;
        brace_level = 0;
        for (size_t i = 0; i < part.length(); ++i) {
            if (part[i] == '{') brace_level++;
            else if (part[i] == '}') brace_level--;
            else if (part[i] == ',' && brace_level == 0) {
                options.push_back(parse_game_string(part.substr(start, i - start)));
                start = i + 1;
            }
        }
        options.push_back(parse_game_string(part.substr(start)));
    };

    parse_options(left_part, node->left_options);
    parse_options(right_part, node->right_options);

    return node;
}

// 帰結類を計算する再帰関数
void calculate_outcomes(GameNode* node) {
    if (node->outcome != Outcome::UNKNOWN) {
        return; // 計算済み
    }

    // 子ノードの帰結類を先に計算
    for (auto* child : node->left_options) calculate_outcomes(child);
    for (auto* child : node->right_options) calculate_outcomes(child);

    // ルール判定用のフラグ
    bool left_can_win = false; // 左にL or Pへの手があるか
    for (auto* opt : node->left_options) {
        if (opt->outcome == Outcome::L || opt->outcome == Outcome::P) {
            left_can_win = true;
            break;
        }
    }

    bool right_can_win = false; // 右にR or Pへの手があるか
    for (auto* opt : node->right_options) {
        if (opt->outcome == Outcome::R || opt->outcome == Outcome::P) {
            right_can_win = true;
            break;
        }
    }
    
    bool left_must_move_to_L_or_N = true; // 右の全ての選択肢がL or Nか
     for (auto* opt : node->right_options) {
        if (opt->outcome != Outcome::L && opt->outcome != Outcome::N) {
            left_must_move_to_L_or_N = false;
            break;
        }
    }

    bool right_must_move_to_R_or_N = true; // 左の全ての選択肢がR or Nか
    for (auto* opt : node->left_options) {
        if (opt->outcome != Outcome::R && opt->outcome != Outcome::N) {
            right_must_move_to_R_or_N = false;
            break;
        }
    }
    
    // 判定
    if (left_can_win && right_can_win) {
        node->outcome = Outcome::N;
    } else if (right_must_move_to_R_or_N && left_must_move_to_L_or_N) {
        node->outcome = Outcome::P;
    } else if (left_can_win && left_must_move_to_L_or_N) {
        node->outcome = Outcome::L;
    } else if (right_must_move_to_R_or_N && right_can_win) {
        node->outcome = Outcome::R;
    }
}


int main() {
    cout << "ゲーム木の文字列を入力してください (例: {{|0}|0,{0|}}):" << endl;
    string s;
    cin >> s;

    try {
        GameNode* root = parse_game_string(s);
        calculate_outcomes(root);

        cout << "\n--- 各局面の帰結類 ---" << endl;
        // メモ化テーブルの内容を表示することで、全てのユニークな局面の結果が見れる
        for (const auto& pair : memo) {
            cout << "局面: " << pair.first << "\t-> 帰結類: " << outcome_to_char(pair.second->outcome) << endl;
        }

    } catch (const exception& e) {
        cerr << "エラー: " << e.what() << endl;
    }

    // メモリ解放 (C++では手動で行う必要がある)
    for (auto& pair : memo) {
        delete pair.second;
    }
    memo.clear();

    return 0;
}