import pandas as pd
import matplotlib.pyplot as plt
import os

def create_table_image():
    """
    ユーザーからCSVファイル名と出力先のPNGファイル名を受け取り、
    CSVの内容を表形式の画像として保存する関数。
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
        # header=None は、CSVの1行目をヘッダーではなくデータとして扱うための設定です。
        df = pd.read_csv(input_csv_file, header=None)

        # --- 画像の生成 ---
        # 空の図（figure）と軸（axes）を作成
        fig, ax = plt.subplots(figsize=(10, 5)) # figsizeは出力画像のサイズ。必要に応じて調整してください。

        # 軸を非表示にする
        ax.axis('off')
        ax.axis('tight')

        # DataFrameからテーブルを作成
        the_table = ax.table(cellText=df.values, loc='center', cellLoc='center')
        
        # フォントサイズとスケールを調整
        the_table.auto_set_font_size(False)
        the_table.set_fontsize(12)
        the_table.scale(1.2, 1.2)

        # --- 画像の保存 ---
        # bbox_inches='tight'で余白を最小限にする
        plt.savefig(output_png_file, bbox_inches='tight', pad_inches=0.1)
        
        # オブジェクトを閉じてメモリを解放
        plt.close(fig)

        print(f"\n成功: 表を '{output_png_file}' として保存しました。")

    except Exception as e:
        print(f"エラーが発生しました: {e}")

# --- メイン処理 ---
if __name__ == '__main__':
    create_table_image()
