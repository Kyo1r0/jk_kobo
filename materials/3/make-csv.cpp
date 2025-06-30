#include <bits/stdc++.h>
#include <fstream> // ファイル出力のために追加

using namespace std;
#define rep(i,n) for(int i=0;i<(n);i++)

// mex関数: 集合に含まれない最小の非負整数を返す
int mex(const unordered_set<int>& s) {
    int m = 0;
    while (s.count(m)) ++m;
    return m;
}

int main() {
    int n;
    cout << "求めたいグランディ数のサイズ(n)を入力してください: ";
    cin >> n; // 求めたいグランディ数(正方形のサイズ)

    vector<vector<int>> vec(n + 1, vector<int>(n + 1, 0)); // グランディ数を格納する配列
    vector<vector<int>> check(n + 1, vector<int>(n + 1, 0)); // P局面(後手必勝)になるかのチェック用配列

    vec[0][0] = 0;

    // 外枠（i=0 または j=0）のグランディ数を計算
    for (int i = 1; i <= n; i++) {
        unordered_set<int> ml;
        ml.insert(vec[0][i - 1]); // 左のマス
        vec[0][i] = mex(ml);

        unordered_set<int> mu;
        mu.insert(vec[i - 1][0]); // 上のマス
        vec[i][0] = mex(mu);
    }

    // 内部のグランディ数を計算
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            unordered_set<int> m;
            m.insert(vec[i - 1][j]); // 上
            m.insert(vec[i][j - 1]); // 左

            // 左斜め上
            for (int k = 1; i - k >= 0 && j - k >= 0; ++k) {
                m.insert(vec[i - k][j - k]);
            }
            vec[i][j] = mex(m);
        }
    }

    // check配列の計算（各マスがP局面かどうかの判定）
    check[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        if (vec[i][0] == 0 || vec[i - 1][0] == 0) check[i][0] = 1;
        if (vec[0][i] == 0 || vec[0][i - 1] == 0) check[0][i] = 1;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (vec[i][j] == 0) {
                check[i][j] = 1;
            } else {
                if (vec[i - 1][j] == 0 || vec[i][j - 1] == 0) {
                    check[i][j] = 1;
                }
                for (int k = 1; i - k >= 0 && j - k >= 0; ++k) {
                    if (vec[i - k][j - k] == 0) {
                        check[i][j] = 1;
                        break;
                    }
                }
            }
        }
    }

    // --- ここからがvec配列をCSVファイルに保存する処理です ---

    // 1. "uma1.csv"という名前でファイルを開く
    ofstream outputFile("uma1.csv");

    // 2. ファイルが正常に開けたかを確認
    if (outputFile.is_open()) {
        // 3. vec配列の内容をループで書き込む
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                // 配列の要素をファイルに書き出す
                outputFile << vec[i][j];
                // 行の最後でなければコンマを追加する
                if (j != n) {
                    outputFile << ",";
                }
            }
            // 行の最後に改行を追加する
            outputFile << "\n";
        }
        // 4. ファイルを閉じる
        outputFile.close();
        cout << "\nvec配列の内容を uma1.csv に正常に保存しました。" << endl;
    } else {
        // ファイルが開けなかった場合のエラーメッセージ
        cerr << "エラー: ファイルを開けませんでした。" << endl;
    }
    // --- ファイル保存処理はここまで ---


    // 元のコードのコンソール出力部分
    cout << "\nコーナーザ竜馬のグランディ数" << endl;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            cout << vec[i][j];
            if (j != n) cout << " ";
            else cout << "\n";
        }
    }

    cout << "\nコーナーザ竜馬の各マスが一手でP局面になるのか" << endl;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            cout << check[i][j];
            if (j != n) cout << " ";
            else cout << "\n";
        }
    }

    int cnt_0 = 0;
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (check[i][j] == 0) cnt_0++;
        }
    }

    cout << "\n先手必勝でないマス(n->pができないマス)は" << cnt_0 << "個" << endl;

    return 0;
}