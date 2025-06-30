import matplotlib.pyplot as plt
import numpy as np

print("--- ステップ1: スクリプトを開始しました ---")

# ステップ2: グラフに描画するための簡単なテストデータを作成します
# (このテストではCSVファイルは使いません)
x_data = np.array([0, 5, 10, 15, 20, 25])
y_data = np.array([10, 60, 110, 160, 210, 260])

print(f"--- ステップ2: テストデータを作成しました。y軸の範囲は {y_data.min()} から {y_data.max()} です ---")

# ステップ3: データをプロットします
# 点(marker='o')と線(linestyle='-')の両方を青色で描画します
plt.plot(x_data, y_data, marker='o', linestyle='-', color='b', label='テストデータ')

print("--- ステップ3: plt.plot() コマンドを実行しました ---")

# ステップ4: グラフの見た目を整えます
plt.xlabel("テストX軸")
plt.ylabel("テストY軸")
plt.title("最小構成テストグラフ")
plt.grid(True) # 見やすいようにグリッドを追加
plt.legend()

# ステップ5: グラフを画像ファイルとして保存します
output_filename = 'minimal_test.png'
plt.savefig(output_filename)

print(f"--- ステップ4: スクリプトが終了しました。'{output_filename}' という名前でグラフが保存されているはずです ---")