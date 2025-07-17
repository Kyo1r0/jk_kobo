#include <bits/stdc++.h>
using namespace std;

// 文字列をlist<char>に変換するヘルパー関数
list<char> to_list(const string& s) {
    list<char> l;
    for (char c : s) {
        l.push_back(c);
    }
    return l;
}

/**
 * @brief ゲーム文字列から、指定された開始・終了イテレータ間の部分をパースし、
 * 選択肢の集合(set)を生成する。
 * @param start パースを開始するイテレータ
 * @param end パースを終了するイテレータ
 * @param left_opts 左選択肢を格納するset
 * @param right_opts 右選択肢を格納するset
 * @return パースに成功したか
 */
bool parse_options(list<char>::iterator start, list<char>::iterator end, 
                   set<string>& left_opts, set<string>& right_opts) {
    
    if (distance(start, end) < 2) return false;

    auto current_pos = next(start); // '{' の次から
    auto content_end = prev(end);   // '}' の手前まで

    string current_option;
    int brace_level = 0;
    
    // メインの'|'を探す
    auto pipe_it = content_end;
    for (auto it = current_pos; it != content_end; ++it) {
        if (*it == '{') brace_level++;
        else if (*it == '}') brace_level--;
        else if (*it == '|' && brace_level == 0) {
            pipe_it = it;
            break;
        }
    }
    if (pipe_it == content_end) return false; // '|'が見つからない

    // 左選択肢をパース
    brace_level = 0;
    for (auto it = current_pos; it != pipe_it; ++it) {
        if (*it == '{') brace_level++;
        else if (*it == '}') brace_level--;

        if (*it == ',' && brace_level == 0) {
            if (!current_option.empty()) {
                left_opts.insert(current_option);
                current_option.clear();
            }
        } else {
            current_option += *it;
        }
    }
    if (!current_option.empty()) left_opts.insert(current_option);
    current_option.clear();

    // 右選択肢をパース
    brace_level = 0;
    for (auto it = next(pipe_it); it != content_end; ++it) {
        if (*it == '{') brace_level++;
        else if (*it == '}') brace_level--;

        if (*it == ',' && brace_level == 0) {
            if (!current_option.empty()) {
                right_opts.insert(current_option);
                current_option.clear();
            }
        } else {
            current_option += *it;
        }
    }
    if (!current_option.empty()) right_opts.insert(current_option);
    
    return true;
}


/**
 * @brief list内のスターパターン "{*0,...|*0,...}" を探し、1つ置換する
 * @param data 処理対象のlist<char>
 * @return 置換が行われた場合はtrue、何も変更がなければfalse
 */
bool to_star(list<char>& data) {
    // スキャン用のイテレータ
    for (auto it = data.begin(); it != data.end(); ++it) {
        if (*it != '{') continue; // '{'で始まる部分のみチェック

        // 対応する'}'を探す
        auto end_brace_it = it;
        int brace_level = 0;
        bool found = false;
        for (auto find_it = it; find_it != data.end(); ++find_it) {
            if (*find_it == '{') brace_level++;
            else if (*find_it == '}') brace_level--;
            if (brace_level == 0 && find_it != it) { // brace_levelが0に戻ったら
                end_brace_it = next(find_it);
                found = true;
                break;
            }
        }
        if (!found) continue;

        // パースして選択肢の集合を取得
        set<string> left_opts, right_opts;
        if (!parse_options(it, end_brace_it, left_opts, right_opts)) {
            continue;
        }

        // 左右の選択肢が同じでなければスターではない
        if (left_opts != right_opts) continue;

        // k=100から逆順にチェック (大きいものからマッチさせる)
        for (int k = 100; k >= 0; --k) {
            set<string> star_k_options;
            // 正しい*kの選択肢の集合を生成
            if (k > 0) {
                for (int i = 0; i < k; ++i) {
                     if (i == 0) star_k_options.insert("0");
                     else if (i == 1) star_k_options.insert("*");
                     else star_k_options.insert("*" + to_string(i));
                }
            }
            
            // 集合が一致するかチェック
            if (left_opts == star_k_options) {
                string replacement_str;
                if (k == 0) replacement_str = "0";
                else if (k == 1) replacement_str = "*";
                else replacement_str = "*" + to_string(k);

                // 置換処理
                auto next_it = data.erase(it, end_brace_it);
                list<char> replacement_list = to_list(replacement_str);
                data.insert(next_it, replacement_list.begin(), replacement_list.end());
                return true; // 置換したのでtrueを返す
            }
        }
    }
    return false; // 置換は行われなかった
}


int main() {
    string s;
    cout << "ゲーム木の文字列を入力してください: ";
    cin >> s;

    list<char> b_d = to_list(s);  // 文字列をlist<char>に変換

    // 置換が行われなくなるまでループ
    while (to_star(b_d)) {
        // 途中経過の表示 (デバッグ用)
        // cout << "  -> ";
        // for(auto& e : b_d) cout << e;
        // cout << "\n";
    }

    cout << "結果: ";
    for (auto& e : b_d) {
        cout << e;
    }
    cout << "\n";

    return 0;
}