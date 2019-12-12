import numpy as np
import sys

def load(filename):
    with open(filename, 'r') as file:
        [N, V, c] = map(int, file.readline().split())
        print(f'{N} customers, {V} vehicles with capacity {c}')
        customers = [list(map(float, line.split())) for line in file if line.strip()]
        return np.array(customers), V, c

def main(filename):
    customers, V, c = load(filename)

            
if __name__ == '__main__':
    if len(sys.argv) != 2:
        print(f'Usage: {sys.argv[0]} input_file')
        sys.exit()
    main(sys.argv[1])
