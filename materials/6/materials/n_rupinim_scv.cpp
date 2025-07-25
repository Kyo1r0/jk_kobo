#include <bits/stdc++.h>
using namespace std;//makecsv が実行ファイル

int main() {
    int n;    // XORした値の比較対象
    int w;    // 表のサイズ（範囲）
    string filename; // CSVファイル名を格納する変数

    cout << "nを入力してください:";
    cin >> n;
    cout << "範囲を求めてください:";
    cin >> w;
    cout << "出力するCSVファイル名を入力してください (例: output): ";
    cin >> filename;

    filename=filename+ ".csv";

    ofstream ofs(filename); // 入力されたファイル名でファイルを開く

    if (!ofs) {// ファイルが開けなかった場合のエラー処理
        cout << "エラー: ファイル " << filename << " を開けませんでした。" << endl;
        return 1; // 異常終了
    }


    vector<vector<string>> g(w, vector<string>(w));
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < w; j++) {
            int a = i^j;

            if (a < n) {
                g[i][j] = to_string(a);
            } else {
                g[i][j] = "inf";
            }

      
            ofs << g[i][j];
            if (j != w - 1) {
                ofs << ","; 
            }
        }
        ofs << endl; 
    }

  
    ofs.close(); //csvの終わり
    cout << "配列の内容を " << filename << " に出力しました。" << endl;

    return 0;
}