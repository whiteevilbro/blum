from random import seed, randint, sample
from time import time
import sys
import os

BIG = 2147483567

e = float(sys.argv[4]) if (len(sys.argv) >= 5) else 1e-3
M = int(sys.argv[3]) if (len(sys.argv) >= 4) else 5
N = int(sys.argv[2]) if (len(sys.argv) >= 3) else 5

if len(sys.argv) >= 2:
    name = sys.argv[1]
else:
    name = os.path.basename(__file__)

seed(time())

l = sample(range(0, BIG), N+M)
n = l[:N]
m = l[N:]

with open(name, 'w', encoding='utf8') as file:
    file.write(f"{N} {e}\n")

    for i in n:
        file.write(f"{i}\n")
    file.write(f"\n{M}\n\n")
    for j in m:
        file.write(f"{j}\n")
