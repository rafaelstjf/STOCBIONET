# libraries
import numpy as np
import matplotlib.pyplot as plt
 
# Choose the height of the bars
height = [132506, 142111, 133353]
 
# Choose the names of the bars
bars = ('Lista circular', 'Heap', 'Lista ordenada')
y_pos = np.arange(len(bars))
 
# Create bars
plt.bar(y_pos, height)
 
# Create labels
plt.ylabel('Atualizações por segundo')
plt.title('Atualizações por segundo por estrutura de dados')
# Create names on the x-axis
plt.xticks(y_pos, bars, color='black')
plt.yticks(color='black')
 
# Show graphic
plt.show()
