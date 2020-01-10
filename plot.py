from matplotlib import pyplot as plt
import numpy as np
import sys

if len(sys.argv) != 2:
    print('Enter a thread number')
    exit()

filename = 'C++/cpp/thread' + sys.argv[1] + '.txt'

costs = []
bestCosts = []
loops = []
mutations = []
with open(filename, 'r') as file:
    for line in file:
        if line.startswith('-'):
            mutations.append(float(line.split()[1]) / 1000000)
        else:
            [loop, cost, bestCost] = map(float, (line.split()))
            loops.append(loop / 1000000)
            costs.append(cost)
            bestCosts.append(bestCost)
        
fig, ax = plt.subplots(figsize=(20, 10))
ax.plot(loops, costs, label='Cost')
ax.plot(loops, bestCosts, label='Best Cost')
ax.legend()
for m in mutations:
    ax.axvline(x=m, color='r', dashes=(5, 5))
plt.show()
