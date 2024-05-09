import re
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import pandas as pd
from matplotlib.colors import Normalize
from matplotlib.cm import ScalarMappable

SaveFigPath = "./INFO/same3D_scatter.png"
SaveFigPath2 = "./INFO/plot_Pri_VS_equPri.png"
SaveFigPath3 = "./INFO/plot_Pri_VS_equPri_slocal.png"
SaveFigPath4 = "./INFO/plot_Pri_VS_equPri_biglocal.png"
EquPriPath = "./INFO/EquivalentPri.txt"
EquPriTestPath="./INFO/EquivalentPri_py.txt"

def extract_data(file_path):
    with open(file_path, 'r') as file:
        data = file.read()

    # 使用正規表示式提取資訊
    pattern = r'gPri: (\d+)\npriority: (\d+)\nprefix_length: (\d+ \d+ \d+ \d+ \d+) \nrange: \[(\d+, \d+)\] \[(\d+, \d+)\] \[(\d+, \d+)\] \[(\d+, \d+)\] \[(\d+, \d+)\] \n'
    matches = re.findall(pattern, data)

    extracted_data = []
    for match in matches:
        gPri = match[0]
        priority = match[1]
        prefix_lengths = match[2].split()
        ranges = [tuple(map(int, rng.split(', '))) for rng in match[3:]]
        extracted_data.append({
            'gPri': gPri,
            'priority': priority,
            'prefix_lengths': prefix_lengths,
            'ranges': ranges
        })

    # 將extracted_data中的每個元素（字典）展平為一個更長的字典
    flat_data = []
    for item in extracted_data:
        flat_item = {
            'gPri': item['gPri'],
            'priority': item['priority']
        }
        flat_item.update({f'prefix_lengths{i}': int(length) for i, length in enumerate(item['prefix_lengths'])})
        for i, rng in enumerate(item['ranges']):
            flat_item.update({f'range{i}_start': rng[0], f'range{i}_end': rng[1]})
        flat_data.append(flat_item)

    # 建立DataFrame
    df = pd.DataFrame(flat_data)
    numeric_columns = ['gPri', 'priority', 'prefix_lengths0', 'prefix_lengths1',
                   'range0_start', 'range0_end', 'range1_start', 'range1_end', 'range2_start', 'range2_end', 'range3_start', 'range3_end', 'range4_start', 'range4_end']
    # 'prefix_lengths2', 'prefix_lengths3', 'prefix_lengths4' : not used
    for col in numeric_columns:
        df[col] = pd.to_numeric(df[col], errors='coerce')


    return df



def write_df_to_file(df, output_file_path):
    with open(output_file_path, 'w') as output_file:
        for index, row in df.iterrows():
            output_file.write(f"Row {index}:\n")
            for column_name, value in row.items():
                output_file.write(f"    {column_name}: {value}\n")

    print("Output written to", output_file_path)


def count_rules(df, prefix_lengths0, prefix_lengths1, gPri):
    # 選擇符合條件的行
    filtered_df = df[(df['prefix_lengths0'] == prefix_lengths0) &
                     (df['prefix_lengths1'] == prefix_lengths1) &
                     (df['gPri'] == gPri)]

    # 返回符合條件的行數（即rule個數）
    return len(filtered_df)



def plot3D(df):
    # 計算每個點的rule個數
    df['3dCount'] = df.apply(lambda row: count_rules(df, row['prefix_lengths0'], row['prefix_lengths1'], row['gPri']), axis=1)
    df['3dCount'] = pd.to_numeric(df['3dCount'], errors='coerce')
    # 僅選擇出現次數大於0的數據
    plot_data = df[df['3dCount'] > 0]
    if plot_data.empty:
      print("No data to plot.")
      return
    # 歸一化數量以進行顏色對映
    norm = Normalize(vmin=np.log2(plot_data['3dCount'].min()), vmax=np.log2(plot_data['3dCount'].max()))
    # 選擇紅色調色板，顏色由淺到深
    cmap = plt.get_cmap('Reds')
    mappable = ScalarMappable(norm=norm, cmap=cmap)
    colors = mappable.to_rgba(plot_data['3dCount'])
    # 繪製3D點陣圖
    fig = plt.figure(figsize=(20, 12))
    # 設定散點的大小和顏色
    size = 10
    ax = fig.add_subplot(111, projection='3d')
    ax.scatter(plot_data['prefix_lengths0'], plot_data['prefix_lengths1'], plot_data['gPri'], s=size, c=colors, alpha=0.6)
    # 設定軸顯示範圍
    ax.set_xlim(plot_data['prefix_lengths0'].min()-1, plot_data['prefix_lengths0'].max()+1)
    ax.set_ylim(plot_data['prefix_lengths1'].min()-1, plot_data['prefix_lengths1'].max()+1)
    ax.set_zlim(plot_data['gPri'].min()-1, plot_data['gPri'].max()+1)
    ax.set_title('Scatter Plot of same equ_pri num')

    ax.set_xlabel('SIP')
    ax.set_ylabel('DIP')
    ax.set_zlabel('equ_pri')
    # 新增顏色條
    plt.colorbar(mappable, ax=ax, label='x-y-z same rule')
    plt.savefig(SaveFigPath)
    plt.show()

    ### Plot
    fig = plt.figure(figsize=(20, 14))
    ax = fig.add_subplot(111)
    ax.scatter(df['priority'], df['gPri'], color='red', marker='o',s=4, label='nums')
    ax.set_xlabel("Pri")
    ax.set_ylabel('equ_pri')
    ax.set_xlim(df['priority'].min()-1, df['priority'].max()+1)
    ax.set_ylim(df['gPri'].min()-1, df['gPri'].max()+1)
    ax.set_title('Plot of pri vs equ_pri')
    # 添加圖例
    ax.legend()

    plt.savefig(SaveFigPath2)
    plt.show()

    ### Plot local
    fig = plt.figure(figsize=(20, 14))
    ax = fig.add_subplot(111)
    ax.scatter(df['priority'], df['gPri'], color='red', marker='o',s=2, label='nums')
    ax.set_xlabel("Pri")
    ax.set_ylabel('equ_pri')
    ax.set_xlim(df['priority'].min()-1, df['priority'].max()-10)
    ax.set_ylim(df['gPri'].min()-1, df['gPri'].max()/10)
    ax.set_title('Plot of pri vs equ_pri')
    # 添加圖例
    ax.legend()

    plt.savefig(SaveFigPath3)
    plt.show()

    fig = plt.figure(figsize=(20, 14))
    ax = fig.add_subplot(111)
    ax.scatter(df['priority'], df['gPri'], color='red', marker='o',s=2, label='nums')
    ax.set_xlabel("Pri")
    ax.set_ylabel('equ_pri')
    ax.set_xlim(df['priority'].max()/2, df['priority'].max()+1)
    ax.set_ylim(df['gPri'].max()/10, df['gPri'].max()+1)
    ax.set_title('Plot of pri vs equ_pri')
    # 添加圖例
    ax.legend()

    plt.savefig(SaveFigPath4)
    plt.show()


if __name__ == "__main__":
    df = extract_data(EquPriPath)
    write_df_to_file(df,EquPriTestPath )

    plot3D(df)
