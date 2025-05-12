import sys

e = float(sys.argv[4]) if (len(sys.argv) >= 5) else 1e-3
M = int(sys.argv[3]) if (len(sys.argv) >= 4) else 5
N = int(sys.argv[2]) if (len(sys.argv) >= 3) else 5

if len(sys.argv) >= 2:
    name = sys.argv[1]
else:
    name = os.path.basename(__file__)

err = 0

with open(name, 'r', encoding='utf8') as file:
    for line in file:
        if line.strip() == 'GOTCHA':
            err += 1

print("="*25)
print(f'Filter element count: {N}')
print(f'Patently false search queries: {M}')
print(f'Desired error: {e}')

print(f'Error (false positive) count: {err}')
print(f'Absolute error: {err/M}')
print("="*25)