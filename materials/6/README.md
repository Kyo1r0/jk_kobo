# やったこと
- n保持二ムのルーピーグランディ数を求めるプログラム
- n保持Wythoffの二ムのルーピーグランディ数を求めるプログラム


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

```


```
## 実行結果
```

```

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


