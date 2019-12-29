import numpy as np
from matplotlib import pyplot as plt
import seaborn as sns; sns.set()
import pandas as pd
import sys

def load(filename):
    with open(filename, 'r') as file:
        [N, V, c] = map(int, file.readline().split())
        print(f'{N} customers, {V} vehicles with capacity {c}')
        customers = [list(map(float, line.split())) for line in file if line.strip()]
        return np.array(customers), V, c
    
    
def show_customers(customers, filename=None):
    df = pd.DataFrame(customers, columns=['demand', 'x', 'y'])
    df['role'] = ['center'] + ['customer'] * (customers.shape[0] - 1)
    ax = sns.scatterplot(x='x', y='y', data=df, size='demand', hue='role', legend=False)
    if filename is not None:
        ax.set_title(' '.join(filename.split('/')[-1].split('_')))
    plt.show()
    
    
def show_progress(customers, d, filename):
    filename = filename.split('/')[1]
    ii = 0
    bestKey, bestValue = list(d.items())[0]
    
    for key, value in d.items():
        if key[1] != 0:
            continue
        fig, (ax1, ax2) = plt.subplots(1, 2, figsize=(21, 10))
        ax1.set_title(f'Loop: {key[0]}, Iteration: {key[1]}, cost: {key[2]}')
        
        if bestKey[2] > key[2]:
            bestKey, bestValue = key, value
        if key[0] == -1:
            bestKey = (bestKey[0], bestKey[1], np.inf)
        
        df = pd.DataFrame(customers, columns=['demand', 'x', 'y'])
        df['role'] = ['center'] + ['customer'] * (customers.shape[0] - 1)
        sns.scatterplot(x='x', y='y', data=df, size='demand', hue='role', legend=False, ax=ax1)
        
        for i, vehicle in enumerate(value, len(value)):
            for c, n in zip(vehicle, vehicle[1:]):
                fromx = customers[c][1]
                fromy = customers[c][2]
                changex = customers[n][1] - fromx
                changey = customers[n][2] - fromy
                ax1.arrow(fromx, fromy, changex, changey, color=f'C{i}')
        
        ax2.set_title(f'Best {bestKey[2]}')
        
        df = pd.DataFrame(customers, columns=['demand', 'x', 'y'])
        df['role'] = ['center'] + ['customer'] * (customers.shape[0] - 1)
        sns.scatterplot(x='x', y='y', data=df, size='demand', hue='role', legend=False, ax=ax2)
        
        for i, vehicle in enumerate(bestValue, len(bestValue)):
            for c, n in zip(vehicle, vehicle[1:]):
                fromx = customers[c][1]
                fromy = customers[c][2]
                changex = customers[n][1] - fromx
                changey = customers[n][2] - fromy
                ax2.arrow(fromx, fromy, changex, changey, color=f'C{i}')#, head_width=0.6, head_length=0.2, width=0.2, fc='black', ec='black')
        
        plt.savefig(f'solution/{filename}/{ii:0>4}_loop_{key[0]}_iteration_{key[1]}_bestCost_{key[2]}.png')
        plt.close('all')
        print('Saving', ii)
        ii += 1

    
def get_progress(V, filename):
    def process(equality):
        equality = equality.split('=')[1]
        if equality.endswith('\n'):
            equality = equality[:-1]
        try:
            equality = int(equality)
        except ValueError:
            equality = float(equality)
        return equality
    
        
    filename = filename.split('/')[1]
    print(filename)
    v = -1
    result = {}
    l = []
    try:
        with open(f'solution/{filename}/output.txt', 'r') as file:
            for line in file:
                if line.strip() == '' or line.strip() == '\n':
                    continue
                if v == -1:
                    key = tuple([process(equality) for equality in line.split(' ')])
                    v += 1
                else:
                    if '-' in line:
                        v = -1
                        result[key] = l
                        l = []
                    else:
                        v += 1
                        ll = []
                        for c in line.split(' '):
                            if c == '\n':
                                continue
                            ll.append(int(c))
                        l.append(ll)
    except FileNotFoundError:
        print('Please run the c++ code first.')
        exit()

    print('Progress created!')
    return result
            
def main(filename):
    customers, V, c = load(filename)
    print('Loaded!')
    show_progress(customers, get_progress(V, filename), filename)
    # show_customers(customers, filename)

            
if __name__ == '__main__':
    if len(sys.argv) < 2:
        print(f'Usage: {sys.argv[0]} input_file [-s]')
        sys.exit()
    s = False
    if len(sys.argv) > 2:
        s = sys.argv[2] == '-s'
    main(sys.argv[1])
