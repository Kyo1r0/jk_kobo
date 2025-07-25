import pandas as pd
import matplotlib.pyplot as plt
import os

def create_table_image():
    """
    ユーザーからCSVファイル名と出力先のPNGファイル名を受け取り、
    CSVの内容を表形式の画像として保存する関数。
    表のサイズに応じて画像サイズを自動調整する。
    """
    # --- ファイル名の入力 ---
    input_csv_file = input("読み込むCSVファイル名を入力してください (例: data.csv): ")

    # ファイルが存在するかチェック
    if not os.path.exists(input_csv_file):
        print(f"エラー: ファイル '{input_csv_file}' が見つかりません。")
        return

    output_png_file = input("出力するPNGファイル名を入力してください (例: table.png): ")

    try:
        # --- CSVデータの読み込み ---
        df = pd.read_csv(input_csv_file, header=None)

        # --- 画像とフォントのサイズを動的に計算 ---
        # DataFrameの行数と列数を取得
        num_rows, num_cols = df.shape

        # 列数に基づいて画像の幅を決定 (最低10インチ)
        # 1列あたり約0.7インチを割り当てる
        fig_width = max(10, num_cols * 0.7)
        
        # 行数に基づいて画像の高さを決定 (最低5インチ)
        # 1行あたり約0.4インチを割り当てる
        fig_height = max(5, num_rows * 0.4)

        # 全体のセル数に応じてフォントサイズを決定
        # 基本フォントサイズを12とし、セルが増えるごとに少し小さくする
        fontsize = max(6, 14 - (num_cols * num_rows) // 100)

        # --- 画像の生成 ---
        # 計算したサイズで図（figure）と軸（axes）を作成
        fig, ax = plt.subplots(figsize=(fig_width, fig_height))

        # 軸を非表示にする
        ax.axis('off')
        ax.axis('tight')

        # DataFrameからテーブルを作成 (列・行ラベルも表示)
        the_table = ax.table(
            cellText=df.values,
            colLabels=[f' {i}' for i in range(num_cols)], # 列ラベルを追加
            rowLabels=[f' {i}' for i in range(num_rows)], # 行ラベルを追加
            loc='center',
            cellLoc='center'
        )
        
        # フォントサイズとスケールを調整
        the_table.auto_set_font_size(False)
        the_table.set_fontsize(fontsize)
        the_table.scale(1, 1.5) # スケールを調整 (幅, 高さ)

        # --- 画像の保存 ---
        plt.savefig(output_png_file, bbox_inches='tight', pad_inches=0.2, dpi=150) # 解像度(dpi)も指定
        
        plt.close(fig)

        print(f"\n成功: 表を '{output_png_file}' として保存しました。")
        print(f"画像サイズ: 幅={fig_width:.2f}インチ, 高さ={fig_height:.2f}インチ | フォントサイズ: {fontsize}pt")

    except Exception as e:
        print(f"エラーが発生しました: {e}")

# --- メイン処理 ---
if __name__ == '__main__':
    create_table_image()
