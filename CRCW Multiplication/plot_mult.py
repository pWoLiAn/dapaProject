import matplotlib.pyplot as plt 
import pandas as pd 
import numpy as np 

# Size,Parallel Time,Sequential Time

data = pd.read_csv("res_mult.csv")

data = data[data['Size']%10 == 0]

sizes = data['Size']
para_times = data['Parallel Time']
seq_times = data['Sequential Time']

plt.plot(sizes, para_times, '--.b', label='CRCW Multiplication')
plt.plot(sizes, seq_times, '--.g', label='Sequential Multiplication')
plt.xlabel('Size of Matrix (N)')
plt.ylabel('Execution Time (s)')
plt.grid()
plt.legend()
plt.show()