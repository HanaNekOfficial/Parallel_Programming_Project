import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

plt.rcParams['font.sans-serif'] = ['SimHei']  # 使用黑体（或改为 ['Microsoft YaHei']）
plt.rcParams['axes.unicode_minus'] = False  # 解决负号无法显示的问题

# 读取 CSV 文件
df = pd.read_csv('matrix_mul_results.csv')

# 提取数据
n = df['n'].values
trivial_avg_time = df['trivial_avg_time'].values
optimized_avg_time = df['optimized_avg_time'].values

# 画图
plt.figure(figsize=(10, 6))
plt.plot(n, trivial_avg_time, marker='o', linestyle='-', label='朴素算法')
plt.plot(n, optimized_avg_time, marker='s', linestyle='-', label='Cache优化算法')

# 设置对数坐标轴
plt.xscale('log')
plt.yscale('log')

# 添加标题和标签
plt.title('矩阵与向量的内积：算法性能对比')
plt.xlabel('n的大小')
plt.ylabel('单次运行时间')
plt.legend()
plt.grid(True, which="both", linestyle="--", linewidth=0.5)

plt.savefig('matrix_mul_plot.pdf', format='pdf', bbox_inches='tight')

# 显示图像
plt.show()


