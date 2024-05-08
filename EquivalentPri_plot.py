import re
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
import pandas as pd
from matplotlib.colors import Normalize
from matplotlib.cm import ScalarMappable

SaveFigPath = "./INFO/same3D_scatter.png"

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
    df['gPri'] = pd.to_numeric(df['gPri'], errors='coerce')
    df['priority'] = pd.to_numeric(df['priority'], errors='coerce')
    df['prefix_lengths0'] = pd.to_numeric(df['prefix_lengths0'], errors='coerce')
    df['prefix_lengths1'] = pd.to_numeric(df['prefix_lengths1'], errors='coerce')
    df['prefix_lengths2'] = pd.to_numeric(df['prefix_lengths2'], errors='coerce')
    df['prefix_lengths3'] = pd.to_numeric(df['prefix_lengths3'], errors='coerce')
    df['prefix_lengths4'] = pd.to_numeric(df['prefix_lengths4'], errors='coerce')

    df['range0_start'] = pd.to_numeric(df['range0_start'], errors='coerce')
    df['range0_end'] = pd.to_numeric(df['range0_end'], errors='coerce')
    df['range1_start'] = pd.to_numeric(df['range1_start'], errors='coerce')
    df['range1_end'] = pd.to_numeric(df['range1_end'], errors='coerce')
    df['range2_start'] = pd.to_numeric(df['range2_start'], errors='coerce')
    df['range2_end'] = pd.to_numeric(df['range2_end'], errors='coerce')
    df['range3_start'] = pd.to_numeric(df['range3_start'], errors='coerce')
    df['range3_end'] = pd.to_numeric(df['range3_end'], errors='coerce')
    df['range4_start'] = pd.to_numeric(df['range4_start'], errors='coerce')
    df['range4_end'] = pd.to_numeric(df['range4_end'], errors='coerce')

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
    # 僅選擇出現次數大於1的數據
    plot_data = df[df['3dCount'] > 1]
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
    ax.set_xlim(plot_data['prefix_lengths0'].min(), plot_data['prefix_lengths0'].max())
    ax.set_ylim(plot_data['prefix_lengths1'].min(), plot_data['prefix_lengths1'].max())
    ax.set_zlim(plot_data['gPri'].min(), plot_data['gPri'].max())
    ax.set_title('Scatter Plot of same eq_pri num')

    ax.set_xlabel('SIP')
    ax.set_ylabel('DIP')
    ax.set_zlabel('eq_pri')
    # 新增顏色條
    plt.colorbar(mappable, ax=ax, label='3dCount')
    plt.savefig(SaveFigPath)
    plt.show()



if __name__ == "__main__":
    df = extract_data("./INFO/EquivalentPri.txt")
    write_df_to_file(df, "./INFO/EquivalentPri_py.txt")

    plot3D(df)
