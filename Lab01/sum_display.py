import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

plt.rcParams['font.sans-serif'] = ['SimHei']  # 使用黑体（或改为 ['Microsoft YaHei']）
plt.rcParams['axes.unicode_minus'] = False  # 解决负号无法显示的问题

# 读取 CSV 文件
df = pd.read_csv('sum_results.csv')

# 设置 x 轴为 n，使用对数尺度
x = df['n']

# 需要绘制的列
columns = ['trivial_avg_time', 'multilink2_avg_time', 'multilink4_avg_time', 'logRecursion_avg_time', 'logLoop_avg_time']
legend = ['朴素算法', '2链路式', '4链路式', '递归函数', '二重循环']

# 绘制折线图
plt.figure(figsize=(10, 6))
for i in range(0, len(columns)):
    plt.plot(x, df[columns[i]], marker='o', label=legend[i])

# 设置对数尺度
plt.xscale('log')
plt.yscale('log')

# 添加标签和标题
plt.xlabel('n 的大小')
plt.ylabel('单次运行时间')
plt.title('n 个数求和：算法性能对比')
plt.legend()
plt.grid(True, which='both', linestyle='--', linewidth=0.5)

# 保存图片以插入 LaTeX
plt.savefig('sum_plot.pdf')
plt.show()
