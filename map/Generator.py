#!/usr/bin/python2.7 -u

import sys
import pprint
import random

if len(sys.argv) != 3:
    print(sys.argv[0] + " <X> <Y>")
    exit()
x = int(sys.argv[1])
y = int(sys.argv[2])

i = 0
while i < x:
    j = 0
    while j < y:
        if i == 0 or j == 0 or i == x - 1 or j == y - 1 or (j % 2 == 0 and i % 2 == 0):
            sys.stdout.write('#')
        elif random.randint(0, 10) == 1:
            sys.stdout.write('o')
        else:
            sys.stdout.write(' ')
        j += 1
    sys.stdout.write('\n')
    i += 1
