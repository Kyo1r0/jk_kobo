# やったこと
- n保持二ムのルーピーグランディ数を求めるプログラム
- n保持Wythoffの二ムのルーピーグランディ数を求めるプログラム(コードの再現が出来なかった)


# n保持二ムのルーピーグランディ数を求めるプログラム

## 原理
定理7.1.17(p.184)




$$
\begin{cases} x \oplus y & (x \oplus y \leq 2 \text{のとき}), \\ \infty(\{0, 1, 2\}) & (x \oplus y \geq 3 \text{のとき}) \end{cases}  
$$


を試して確認する


## プログラム

$ \infty(\{0, 1, 2\})$ として出力されるようにした

また、scvファイルで出力されるようにした

参考にしてたページ(https://jp-seemore.com/iot/24027/)

- ofstreamを使うことでstringの内容を出力ファイルにできる


<details>
  <summary> コード</summary>

```
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;    // XORした値の比較対象
    int w;    // 表のサイズ（範囲）
    string filename; // CSVファイル名を格納する変数

    int n;//n保持のn
    int w;//求めたい範囲w
    cout << "nを入力してください:";
    cin >> n;
    cout << "範囲を求めてください:";
    cin >> w;
    cout << "出力するCSVファイル名を入力してください (例: output.csv): ";
    cin >> filename;


    ofstream ofs(filename); // 入力されたファイル名でファイルを開く

    if (!ofs) {　// ファイルが開けなかった場合のエラー処理
        cout << "エラー: ファイル " << filename << " を開けませんでした。" << endl;
        return 1; // 異常終了
    }


    vector<vector<string>> g(w, vector<string>(w));
    for (int i = 0; i < w; i++) {
        for (int j = 0; j < w; j++) {
            int a = i ^ j;

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

```
</details>


## 実行結果
```
0 1 2inf inf inf inf inf inf inf 
1 0 inf2 inf inf inf inf inf inf 
2 inf 01 inf inf inf inf inf inf 
inf 2 10 inf inf inf inf inf inf 
inf inf infinf 0 1 2 inf inf inf 
inf inf infinf 1 0 inf 2 inf inf 
inf inf infinf 2 inf 0 1 inf inf 
inf inf infinf inf 2 1 0 inf inf 
inf inf infinf inf inf inf inf 0 1 
inf inf infinf inf inf inf inf 1 0
```
![](./materials/mk_csv/hozi(3).png)


## 1~100保持二ムを行った

### コード

<details>
<summary>　開く　 </summary>



```
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
```
</details>

- 1~100まで実装した
- 特徴があるものを載せていく

### 全てのせる

<details><summary>　開く　 </summary>

#### 0保持二ム
![](./materials/mk_csv/hozi(0).png)

#### 1保持二ム
![](./materials/mk_csv/hozi(1).png)

#### 2保持二ム
![](./materials/mk_csv/hozi(2).png)

#### 3保持二ム
![](./materials/mk_csv/hozi(3).png)

#### 4保持二ム
![](./materials/mk_csv/hozi(4).png)

#### 5保持二ム
![](./materials/mk_csv/hozi(5).png)

#### 6保持二ム
![](./materials/mk_csv/hozi(6).png)

#### 7保持二ム
![](./materials/mk_csv/hozi(7).png)

#### 8保持二ム
![](./materials/mk_csv/hozi(8).png)

#### 9保持二ム
![](./materials/mk_csv/hozi(9).png)

#### 10保持二ム
![](./materials/mk_csv/hozi(10).png)

#### 11保持二ム
![](./materials/mk_csv/hozi(11).png)

#### 12保持二ム
![](./materials/mk_csv/hozi(12).png)

#### 13保持二ム
![](./materials/mk_csv/hozi(13).png)

#### 14保持二ム
![](./materials/mk_csv/hozi(14).png)

#### 15保持二ム
![](./materials/mk_csv/hozi(15).png)

#### 16保持二ム
![](./materials/mk_csv/hozi(16).png)

#### 17保持二ム
![](./materials/mk_csv/hozi(17).png)

#### 18保持二ム
![](./materials/mk_csv/hozi(18).png)

#### 19保持二ム
![](./materials/mk_csv/hozi(19).png)

#### 20保持二ム
![](./materials/mk_csv/hozi(20).png)

#### 21保持二ム
![](./materials/mk_csv/hozi(21).png)

#### 22保持二ム
![](./materials/mk_csv/hozi(22).png)

#### 23保持二ム
![](./materials/mk_csv/hozi(23).png)

#### 24保持二ム
![](./materials/mk_csv/hozi(24).png)

#### 25保持二ム
![](./materials/mk_csv/hozi(25).png)

#### 26保持二ム
![](./materials/mk_csv/hozi(26).png)

#### 27保持二ム
![](./materials/mk_csv/hozi(27).png)

#### 28保持二ム
![](./materials/mk_csv/hozi(28).png)

#### 29保持二ム
![](./materials/mk_csv/hozi(29).png)

#### 30保持二ム
![](./materials/mk_csv/hozi(30).png)

#### 31保持二ム
![](./materials/mk_csv/hozi(31).png)

#### 32保持二ム
![](./materials/mk_csv/hozi(32).png)

#### 33保持二ム
![](./materials/mk_csv/hozi(33).png)

#### 34保持二ム
![](./materials/mk_csv/hozi(34).png)

#### 35保持二ム
![](./materials/mk_csv/hozi(35).png)

#### 36保持二ム
![](./materials/mk_csv/hozi(36).png)

#### 37保持二ム
![](./materials/mk_csv/hozi(37).png)

#### 38保持二ム
![](./materials/mk_csv/hozi(38).png)

#### 39保持二ム
![](./materials/mk_csv/hozi(39).png)

#### 40保持二ム
![](./materials/mk_csv/hozi(40).png)

#### 41保持二ム
![](./materials/mk_csv/hozi(41).png)

#### 42保持二ム
![](./materials/mk_csv/hozi(42).png)

#### 43保持二ム
![](./materials/mk_csv/hozi(43).png)

#### 44保持二ム
![](./materials/mk_csv/hozi(44).png)

#### 45保持二ム
![](./materials/mk_csv/hozi(45).png)

#### 46保持二ム
![](./materials/mk_csv/hozi(46).png)

#### 47保持二ム
![](./materials/mk_csv/hozi(47).png)

#### 48保持二ム
![](./materials/mk_csv/hozi(48).png)

#### 49保持二ム
![](./materials/mk_csv/hozi(49).png)

#### 50保持二ム
![](./materials/mk_csv/hozi(50).png)

#### 51保持二ム
![](./materials/mk_csv/hozi(51).png)

#### 52保持二ム
![](./materials/mk_csv/hozi(52).png)

#### 53保持二ム
![](./materials/mk_csv/hozi(53).png)

#### 54保持二ム
![](./materials/mk_csv/hozi(54).png)

#### 55保持二ム
![](./materials/mk_csv/hozi(55).png)

#### 56保持二ム
![](./materials/mk_csv/hozi(56).png)

#### 57保持二ム
![](./materials/mk_csv/hozi(57).png)

#### 58保持二ム
![](./materials/mk_csv/hozi(58).png)

#### 59保持二ム
![](./materials/mk_csv/hozi(59).png)

#### 60保持二ム
![](./materials/mk_csv/hozi(60).png)

#### 61保持二ム
![](./materials/mk_csv/hozi(61).png)

#### 62保持二ム
![](./materials/mk_csv/hozi(62).png)

#### 63保持二ム
![](./materials/mk_csv/hozi(63).png)

#### 64保持二ム
![](./materials/mk_csv/hozi(64).png)

#### 65保持二ム
![](./materials/mk_csv/hozi(65).png)

#### 66保持二ム
![](./materials/mk_csv/hozi(66).png)

#### 67保持二ム
![](./materials/mk_csv/hozi(67).png)

#### 68保持二ム
![](./materials/mk_csv/hozi(68).png)

#### 69保持二ム
![](./materials/mk_csv/hozi(69).png)

#### 70保持二ム
![](./materials/mk_csv/hozi(70).png)

#### 71保持二ム
![](./materials/mk_csv/hozi(71).png)

#### 72保持二ム
![](./materials/mk_csv/hozi(72).png)

#### 73保持二ム
![](./materials/mk_csv/hozi(73).png)

#### 74保持二ム
![](./materials/mk_csv/hozi(74).png)

#### 75保持二ム
![](./materials/mk_csv/hozi(75).png)

#### 76保持二ム
![](./materials/mk_csv/hozi(76).png)

#### 77保持二ム
![](./materials/mk_csv/hozi(77).png)

#### 78保持二ム
![](./materials/mk_csv/hozi(78).png)

#### 79保持二ム
![](./materials/mk_csv/hozi(79).png)

#### 80保持二ム
![](./materials/mk_csv/hozi(80).png)

#### 81保持二ム
![](./materials/mk_csv/hozi(81).png)

#### 82保持二ム
![](./materials/mk_csv/hozi(82).png)

#### 83保持二ム
![](./materials/mk_csv/hozi(83).png)

#### 84保持二ム
![](./materials/mk_csv/hozi(84).png)

#### 85保持二ム
![](./materials/mk_csv/hozi(85).png)

#### 86保持二ム
![](./materials/mk_csv/hozi(86).png)

#### 87保持二ム
![](./materials/mk_csv/hozi(87).png)

#### 88保持二ム
![](./materials/mk_csv/hozi(88).png)

#### 89保持二ム
![](./materials/mk_csv/hozi(89).png)

#### 90保持二ム
![](./materials/mk_csv/hozi(90).png)

#### 91保持二ム
![](./materials/mk_csv/hozi(91).png)

#### 92保持二ム
![](./materials/mk_csv/hozi(92).png)

#### 93保持二ム
![](./materials/mk_csv/hozi(93).png)

#### 94保持二ム
![](./materials/mk_csv/hozi(94).png)

#### 95保持二ム
![](./materials/mk_csv/hozi(95).png)

#### 96保持二ム
![](./materials/mk_csv/hozi(96).png)

#### 97保持二ム
![](./materials/mk_csv/hozi(97).png)

#### 98保持二ム
![](./materials/mk_csv/hozi(98).png)

#### 99保持二ム
![](./materials/mk_csv/hozi(99).png)

#### 100保持二ム
![](./materials/mk_csv/hozi(100).png)



</details>

###  予想

- 指数乗のときは形が似ているように見えた(2,4,8,16,32,)

<details>
<summary>　2^n　 </summary>

#### 2^0保持二ム
![](./materials/mk_csv/hozi(1).png)

#### 2^1保持二ム
![](./materials/mk_csv/hozi(2).png)

#### 2^2保持二ム
![](./materials/mk_csv/hozi(4).png)

#### 2^3保持二ム
![](./materials/mk_csv/hozi(8).png)

#### 2^4保持二ム
![](./materials/mk_csv/hozi(16).png)

#### 2^5保持二ム
![](./materials/mk_csv/hozi(32).png)

#### 2^6保持二ム
![](./materials/mk_csv/hozi(64).png)

</details>


<details>
<summary>　3^n　 </summary>

#### 3^0保持二ム
![](./materials/mk_csv/hozi(1).png)

#### 3^1保持二ム
![](./materials/mk_csv/hozi(3).png)

#### 3^2保持二ム
![](./materials/mk_csv/hozi(9).png)

#### 3^3保持二ム
![](./materials/mk_csv/hozi(27).png)

#### 3^4保持二ム
![](./materials/mk_csv/hozi(81).png)

</details>

<details>
<summary>　5^n　 </summary>

#### 5^0保持二ム
![](./materials/mk_csv/hozi(1).png)

#### 5^1保持二ム
![](./materials/mk_csv/hozi(5).png)

#### 5^2保持二ム
![](./materials/mk_csv/hozi(25).png)

</details>


<details>
<summary>　n^2　 </summary>

#### 0^2保持二ム
![](./materials/mk_csv/hozi(0).png)

#### 1^2保持二ム
![](./materials/mk_csv/hozi(1).png)

#### 2^2保持二ム
![](./materials/mk_csv/hozi(4).png)

#### 3^2保持二ム
![](./materials/mk_csv/hozi(9).png)

#### 4^2保持二ム
![](./materials/mk_csv/hozi(16).png)

#### 5^2保持二ム
![](./materials/mk_csv/hozi(25).png)

#### 6^2保持二ム
![](./materials/mk_csv/hozi(36).png)

#### 7^2保持二ム
![](./materials/mk_csv/hozi(49).png)

#### 8^2保持二ム
![](./materials/mk_csv/hozi(64).png)

#### 9^2保持二ム
![](./materials/mk_csv/hozi(81).png)

#### 10^2保持二ム
![](./materials/mk_csv/hozi(100).png)

</details>


# ~ここからはうまくいかなかった~

# n保持Wythoffの二ムのルーピーグランディ数を求めるプログラム

## 原理
定義7.1.9(p.178)

$$
G_{0}(G) =
\begin{cases}
0 & (G \text{が終了局面のとき}), \\
\infty & (\text{それ以外})
\end{cases}
$$

$$
G_{n+1}(G) =
\begin{cases}
m_n(G) & (G \text{の任意の選択肢 } G' \text{ で } G_n(G') > m_n(G) \text{ を} \\
& \text{満たすものについて, ある選択肢 } G'' \text{ が存在して} \\
& G_n(G'') = m_n(G) \text{ のとき}), \\
\infty & (\text{それ以外})
\end{cases}
$$




を使うことでグランディ数を求める

## 実行結果(3保持wythoff二ム)

```

```
![](./plot/hozi1.png)


100まで回す
![](./plot/wythof_hozi2.png)