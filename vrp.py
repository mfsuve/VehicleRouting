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

            
def main(filename):
    customers, V, c = load(filename)
    show_customers(customers, filename)

            
if __name__ == '__main__':
    if len(sys.argv) != 2:
        print(f'Usage: {sys.argv[0]} input_file')
        sys.exit()
    main(sys.argv[1])
