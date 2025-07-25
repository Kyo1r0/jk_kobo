import pandas as pd
import matplotlib.pyplot as plt
import os
import glob # ファイル検索のために追加

def create_table_image(input_csv_file, output_png_file):
    """
    指定されたCSVファイルの内容を読み込み、表形式の画像として保存する関数。
    表のサイズに応じて画像サイズを自動調整し、'inf'のセルを色付けする。
    """
    try:
        # --- CSVデータの読み込み ---
        # dtype=str を指定して、'inf'が数値の無限大に変換されるのを防ぎ、文字列として扱う
        df = pd.read_csv(input_csv_file, header=None, dtype=str)

        # --- 画像とフォントのサイズを動的に計算 ---
        # DataFrameの行数と列数を取得
        num_rows, num_cols = df.shape

        # 列数に基づいて画像の幅を決定 (最低10インチ)
        fig_width = max(10, num_cols * 0.7)
        
        # 行数に基づいて画像の高さを決定 (最低5インチ)
        fig_height = max(5, num_rows * 0.4)

        # 全体のセル数に応じてフォントサイズを決定
        fontsize = max(6, 14 - (num_cols * num_rows) // 100)

        # --- 画像の生成 ---
        fig, ax = plt.subplots(figsize=(fig_width, fig_height))
        ax.axis('off')
        ax.axis('tight')

        # DataFrameからテーブルを作成
        the_table = ax.table(
            cellText=df.values,
            colLabels=[f' {i}' for i in range(num_cols)],
            rowLabels=[f' {i}' for i in range(num_rows)],
            loc='center',
            cellLoc='center'
        )
        
        # フォントサイズとスケールを調整
        the_table.auto_set_font_size(False)
        the_table.set_fontsize(fontsize)
        the_table.scale(1, 1.5)

        # セルの色を条件に応じて変更する
        for i in range(num_rows):
            for j in range(num_cols):
                cell = the_table.get_celld()[(i + 1, j)]
                if df.iloc[i, j] == 'inf':
                    cell.set_facecolor('#ffadad')

        # --- 画像の保存 ---
        plt.savefig(output_png_file, bbox_inches='tight', pad_inches=0.2, dpi=150)
        
        plt.close(fig)

        print(f"  -> 成功: '{output_png_file}' として保存しました。")

    except Exception as e:
        print(f"  -> エラーが発生しました: {e}")

# --- メイン処理 ---
if __name__ == '__main__':
    # 'hozi(数字).csv' のパターンに一致するファイルを探す
    file_pattern = "hozi(*).csv"
    csv_files = glob.glob(file_pattern)

    if not csv_files:
        print(f"処理対象のファイルが見つかりません。パターン: '{file_pattern}'")
    else:
        print(f"{len(csv_files)}個のファイルが見つかりました。処理を開始します...")
        
        # 見つかったファイルを一つずつ処理
        for input_csv in sorted(csv_files):
            # 出力ファイル名を生成 (例: hozi(1).csv -> hozi(1).png)
            output_png = os.path.splitext(input_csv)[0] + ".png"
            
            print(f"\n処理中: '{input_csv}'")
            # ファイル変換関数を呼び出し
            create_table_image(input_csv, output_png)
            
        print("\nすべての処理が完了しました。")
