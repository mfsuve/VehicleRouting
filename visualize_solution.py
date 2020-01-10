from matplotlib import pyplot as plt
import numpy as np
import pandas as pd
import seaborn as sns
sns.set()


def load(filename):
    with open(filename, 'r') as file:
        [N, V, c] = map(int, file.readline().split())
        print(f'{N} customers, {V} vehicles with capacity {c}')
        customers = [list(map(float, line.split())) for line in file if line.strip()]
        return np.array(customers), V, c
    
    
def show_customers(customers, solution=None, filename=None):
    df = pd.DataFrame(customers, columns=['demand', 'x', 'y'])
    df['role'] = ['center'] + ['customer'] * (customers.shape[0] - 1)
    ax = sns.scatterplot(x='x', y='y', data=df, size='demand', hue='role', legend=False)
    if filename is not None:
        if '/' in filename:
            ax.set_title(' '.join(filename.split('/')[-1].split('_')))
        else:
            ax.set_title(' '.join(filename.split('\\')[-1].split('_')))
    if solution is not None:
        for vi, v in enumerate(solution):
            for i, j in zip(v, v[1:]):
                fromx = customers[i][1]
                fromy = customers[i][2]
                changex = customers[j][1] - fromx
                changey = customers[j][2] - fromy
                ax.arrow(fromx, fromy, changex, changey, color=f'C{vi}')
    plt.show()
    

solution = []
with open('sol2.txt', 'r') as file:
    file.readline()
    for line in file:
        v = []
        for c in map(int, line.split()):
            v.append(c)
        solution.append(v)
        

filename = 'data\\vrp_51_5_1'
customers, V, c = load(filename)
show_customers(customers, solution, filename)
