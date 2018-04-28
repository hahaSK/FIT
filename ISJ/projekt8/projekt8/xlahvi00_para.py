#!/usr/bin/env python3

import multiprocessing

def count(n):
    while n > 0:
        n -= 1

p = multiprocessing.Process(target=count, args=(10**8,))
p.start()
k = multiprocessing.Process(target=count, args=(10**8,))
k.start()
p.join()
k.join()
