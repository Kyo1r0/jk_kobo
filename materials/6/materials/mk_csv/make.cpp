#include <bits/stdc++.h>
using namespace std;//makecsv が実行ファイル

int main() {
    int m;
    int n;    // XORした値の比較対象
    int w;    // 表のサイズ（範囲）
    string filename; // CSVファイル名を格納する変数

    cout << "nを入力してください(nまですべて求める):";
    cin >> m;
    cout << "範囲を求めてください:";
    cin >> w;

    for(int i=0;i<=m;i++){
     n=i;
     filename= "hozi(" + to_string(i) + ").csv";


    ofstream ofs(filename); // 入力されたファイル名でファイルを開く

    if (!ofs) {// ファイルが開けなかった場合のエラー処理
        cout << "エラー: ファイル " << filename << " を開けませんでした。" << endl;
        return 1; // 異常終了
    }


    vector<vector<string>> g(w, vector<string>(w,"-1"));
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
    }

    cout << "---------------すべての計算が終了------------------" << endl;
    return 0;
}