#include <bits/stdc++.h>
using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++)

list<char> to_list(const string& s) {
    list<char> l;
    for (char c : s) {
        l.push_back(c);
    }
    return l;
}


bool check_Z(list<char>& data) {
    static map<list<char>, list<char>> rules;// 整数に関する置換ルールを定義
    if (rules.empty()) { // 一番最初に生成
        rules[to_list("{|}")] = to_list("0");
        for (int i = 1; i <= 100; ++i) { // 100まで対応     
            rules[to_list("{" + std::to_string(i - 1) + "|}")] = to_list(std::to_string(i)); // 正の整数: n = {n-1|}
            rules[to_list("{|" + std::to_string(-(i - 1)) + "}")] = to_list(std::to_string(-i)); // 負の整数: n = {|-(n-1)}
        }
    }

  
    for (auto it = data.begin(); it != data.end(); ++it) {   // listを先頭からスキャン
        for (const auto& rule : rules) {
            const auto& pattern = rule.first; //{|0}みたいの
            const auto& replacement = rule.second; //数字

            auto temp_it = it;
            auto pattern_it = pattern.begin();//つまり'{'
            bool match = true;

           
            while (pattern_it != pattern.end()) { // 現在の位置からパターンが一致するか確認
                if (temp_it == data.end() || *temp_it != *pattern_it) {
                    match = false;
                    break;
                }
                ++temp_it;
                ++pattern_it;
            }

            
            if (match) {
                auto next_it = data.erase(it, temp_it);
                data.insert(next_it, replacement.begin(), replacement.end());
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

    
    while (check_Z(b_d)) {}// 置換が行われなくなるまでループ（関数がtrueを返す限りループが続く）


    cout << "結果: ";
    for (auto& e : b_d) {
        cout << e;
    }
    cout << "\n";

    return 0;
}