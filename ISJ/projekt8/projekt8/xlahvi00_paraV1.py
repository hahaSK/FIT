#!/usr/bin/env python3

import multiprocessing

def count(n):
    while n > 0:
        n -= 1

p = multiprocessing.Pool(2)
p.map(count,[(10**8),(10**8)])

