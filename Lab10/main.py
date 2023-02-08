import time
import timeit


def zad1():
    start = time.time()
    start2 = time.perf_counter()

    f = open("test.txt", "r")
    print(f.read())

    print(f'Time: {time.time() - start}')
    print(f'Time_CPU: {time.perf_counter() - start2}')

zad1()