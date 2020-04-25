#!/usr/bin/env python3.8

print("Hello World")


def example(a: int):
    if(a < 0): return 
    print(a)
    return(example(a-1))
example(10)
