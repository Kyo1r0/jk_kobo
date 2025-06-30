import matplotlib.pyplot as plt
import pandas as pd
import numpy as np

#フォント設定
plt.rcParams['font.family'] = 'DejaVu Serif' # font familyの設定 DejaVu Serif,Liberation Serif ->Times New Romanの代わりに
#plt.rcParams['mathtext.fontset'] = 'stix' # math fontの設定
plt.rcParams["font.size"] = 10 # 全体のフォントサイズが変更されます。
#plt.rcParams['xtick.labelsize'] = 9 # 軸だけ変更されます。
#plt.rcParams['ytick.labelsize'] = 24 # 軸だけ変更されます


#軸設定
plt.rcParams['xtick.direction'] = 'in' #x軸の目盛りの向き
plt.rcParams['ytick.direction'] = 'in' #y軸の目盛りの向き
#plt.rcParams['axes.grid'] = True # グリッドの作成
#plt.rcParams['grid.linestyle']='--' #グリッドの線種
plt.rcParams["xtick.minor.visible"] = True  #x軸補助目盛りの追加
plt.rcParams["ytick.minor.visible"] = True  #y軸補助目盛りの追加
#plt.rcParams['xtick.top'] = True  #x軸の上部目盛り
#plt.rcParams['ytick.right'] = True  #y軸の右部目盛り


#軸大きさ
#plt.rcParams["xtick.major.width"] = 1.0             #x軸主目盛り線の線幅
#plt.rcParams["ytick.major.width"] = 1.0             #y軸主目盛り線の線幅
#plt.rcParams["xtick.minor.width"] = 1.0             #x軸補助目盛り線の線幅
#plt.rcParams["ytick.minor.width"] = 1.0             #y軸補助目盛り線の線幅
#plt.rcParams["xtick.major.size"] = 10               #x軸主目盛り線の長さ
#plt.rcParams["ytick.major.size"] = 10               #y軸主目盛り線の長さ
#plt.rcParams["xtick.minor.size"] = 5                #x軸補助目盛り線の長さ
#plt.rcParams["ytick.minor.size"] = 5                #y軸補助目盛り線の長さ
#plt.rcParams["axes.linewidth"] = 1.0                #囲みの太さ


#凡例設定
plt.rcParams["legend.fancybox"] = False  # 丸角OFF
plt.rcParams["legend.framealpha"] = 1  # 透明度の指定、0で塗りつぶしなし
plt.rcParams["legend.edgecolor"] = 'black'  # edgeの色を変更
plt.rcParams["legend.markerscale"] = 5 #markerサイズの倍率
plt.rcParams['lines.linewidth'] = 0
plt.rcParams['lines.linestyle'] = ''
plt.rcParams['lines.marker'] = '.'

input_csv = pd.read_csv('./input_csv_file.csv', header=None)    #********使用するcsvファイルの指定********
first_column_data = input_csv[0]
second_column_data = input_csv[1]

#複数のCSVファイルを追加
r_input_csv = pd.read_csv('./Red_ave_py.csv', header=None)
r_first_column_data = r_input_csv[0]
r_second_column_data = r_input_csv[1]
o_input_csv = pd.read_csv('./Orange_ave_py.csv', header=None)
o_first_column_data = o_input_csv[0]
o_second_column_data = o_input_csv[1]
y_input_csv = pd.read_csv('./Yellow_ave_py.csv', header=None)
y_first_column_data = y_input_csv[0]
y_second_column_data = y_input_csv[1]
b_input_csv = pd.read_csv('./Blue_ave_py.csv', header=None)
b_first_column_data = b_input_csv[0]
b_second_column_data = b_input_csv[1]

plt.xlim(0, 1.6)
plt.ylim(0, 1200)

plt.scatter(r_first_column_data, r_second_column_data, s=15, marker='o', c='w', ec='k', label='赤色')
plt.scatter(o_first_column_data, o_second_column_data, s=15, marker=',', c='w', ec='k', label='オレンジ色')
plt.scatter(y_first_column_data, y_second_column_data, s=15, marker='^', c='w', ec='k', label='黄色')
plt.scatter(b_first_column_data, b_second_column_data, s=15, marker='v', c='w', ec='k', label='青色')

plt.xlabel("$\it{V}$/V")
plt.ylabel("$\mathregular{\overline{\mathit{I}}}$/nA")

plt.legend(prop={'family':'Yu Gothic'})

#近似曲線の追加
x = np.arange(0, 50, 0.1)
y = 2 * x - 1
plt.plot(x, y, marker='', color='black')

plt.xlim(0, 25)     #********x軸の範囲(最小値,最大値)********
plt.ylim(0, 500)    #********y軸の範囲(最小値,最大値)********

#plt.figure(dpi=300)
plt.plot(first_column_data, second_column_data, markeredgecolor='k')
plt.xlabel("x")     #********x軸ラベルの指定********
plt.ylabel("y")     #********y軸ラベルの指定********
#plt.legend()

#plt.show()
plt.savefig('my_plot3.png', dpi=300) # ← この行を追加します。'my_plot.png'という名前で保存されます。

print("グラフを 'my_plot3.png' として保存しました。")