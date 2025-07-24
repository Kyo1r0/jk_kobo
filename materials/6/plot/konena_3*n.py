import matplotlib.pyplot as plt
import pandas as pd
import io

# ユーザーから提供されたCSVデータ
# ファイルが読み込めない問題を回避するため、データを直接コードに埋め込みます。
csv_data = """n,string_length
3,17
6,2505
9,999513
12,1031528275
"""

# 文字列データをファイルのように読み込んでDataFrameを作成します。
# これにより、実際のファイル読み込みと同じように処理できます。
try:
    df = pd.read_csv(io.StringIO(csv_data))
except Exception as e:
    print(f"データの読み込み中にエラーが発生しました: {e}")
    exit()

# データを抽出
x_data = df['n']
y_data = df['string_length']


# --- グラフ描画設定 ---

# フォント設定
plt.rcParams['font.family'] = 'DejaVu Serif'
plt.rcParams["font.size"] = 12

# 軸設定
plt.rcParams['xtick.direction'] = 'in'
plt.rcParams['ytick.direction'] = 'in'
plt.rcParams["xtick.minor.visible"] = True
plt.rcParams["ytick.minor.visible"] = True
plt.rcParams["axes.grid"] = True
plt.rcParams["grid.linestyle"] = '--'

# プロットスタイルを設定
plt.rcParams['lines.linewidth'] = 1.5
plt.rcParams['lines.linestyle'] = '-'
plt.rcParams['lines.marker'] = 'o'


# --- グラフ作成 ---

# ★★★ 解決策: Y軸を対数スケールに設定 ★★★
plt.yscale('log')

# 軸のラベルとタイトル
plt.xlabel("N (for 3xN board)")
plt.ylabel("String Length (Log Scale)")
plt.title("Konane: String Length vs. Board Size")

# 軸の範囲と目盛り
plt.xticks(x_data) # X軸の主目盛りをデータのN値に合わせる
plt.xlim(2, 13)    # X軸の表示範囲を調整

# データをプロット
plt.plot(x_data, y_data, markerfacecolor='w', markeredgecolor='k', label='String Length')

# 凡例を表示
plt.legend()

# ファイルに保存
# bbox_inches='tight' は、ラベルなどが画像外にはみ出ないように調整するオプションです。
plt.savefig('konane_3xN_plot.png', dpi=300, bbox_inches='tight')

print("グラフを 'konane_3xN_plot.png' として保存しました。")
