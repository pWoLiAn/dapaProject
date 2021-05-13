import matplotlib.pyplot as plt 
import pandas as pd 
import numpy as np 

# Size,Parallel Time,Sequential Time

data = pd.read_csv("res_trans.csv")

data = data[data['Size']%50 == 0]

sizes = data['Size']
para_times = data['Parallel Time']
seq_times = data['Sequential Time']

plt.plot(sizes, para_times, '--.b', label='EREW Transpose')
plt.plot(sizes, seq_times, '--.g', label='Sequential Transpose')
plt.xlabel('Size of Matrix (N)')
plt.ylabel('Execution Time (s)')
plt.grid()
plt.legend()
plt.show()
