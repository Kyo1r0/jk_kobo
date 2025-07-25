#include <bits/stdc++.h>
using namespace std;

int mex(const set<int>& s) {
    int mex = 0;
    while (s.count(mex)) {
        mex++;
    }
    return mex;
}

int main() {
    int n;           // n保持
    int w;           // 幅
    string filename; // CSVファイル

   
    cout << "n を入力してください: "; //入力
    cin >> n;
    cout << "範囲(w): ";
    cin >> w;
    cout << "出力するCSVファイル名を入力してください (例: wythoff_output): ";
    cin >> filename;

    filename = filename + ".csv";

  

  
    vector<vector<int>> wythoff_grundy_table(w, vector<int>(w, 0));

    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < w; ++j) {
            set<int> reachable_grundy_numbers;

            //片方の山
            for (int k = 0; k < i; ++k) {
                reachable_grundy_numbers.insert(wythoff_grundy_table[k][j]);
            }

            //もう片方の山
            for (int k = 0; k < j; ++k) {
                reachable_grundy_numbers.insert(wythoff_grundy_table[i][k]);
            }

            //同時にとる
            for (int k = 1; k <= min(i, j); ++k) {
                reachable_grundy_numbers.insert(wythoff_grundy_table[i - k][j - k]);
            }
            
            // mexを計算して格納
            wythoff_grundy_table[i][j] = mex(reachable_grundy_numbers);
        }
    }
    
    


    ofstream ofs(filename); //エラー処理
    if (!ofs) {
        cout << "エラー: ファイル " << filename << " を開けませんでした。" << endl;
        return 1;
    }

    for (int i = 0; i < w; ++i) { //csvファイルの出力
        for (int j = 0; j < w; ++j) {
            int g = wythoff_grundy_table[i][j];

           
            if (g < n) {
                ofs << to_string(g);
            } else {
                ofs << "inf";
            }

            if (j != w - 1) {
                ofs << ",";
            }
        }
        ofs << endl;
    }

    ofs.close();
    cout << "n保持Wythoffのニムの値を " << filename << " に出力しました。" << endl;

    return 0;
}
