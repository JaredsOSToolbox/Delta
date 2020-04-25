#!/usr/bin/env python3.8
from itertools import zip_longest

with open("../inputs/left.txt") as l:
    l_contents = l.readlines()
with open("../inputs/right.txt") as r:
    r_contents = r.readlines()

l_contents = [element.strip("\n") for element in l_contents]
r_contents = [element.strip("\n") for element in r_contents]
l_contents_size_ = len(l_contents)
r_contents_size_ = len(r_contents)
longest_ = l_contents_size_ if(l_contents_size_ > r_contents_size_) else r_contents_size_

# Assuming fruit is file_context.readlines()
# fruits = fruit.split("\n")
# vegs = veg.split("\n")
# for l1,l2 in zip_longest(fruits, vegs, fillvalue=""):
    # print("{}\t{}".format(l1, l2))   

for i in range(min(len(l_contents),len(r_contents))):
    print("{0:8>}\t\t\t\t{}".format(r_contents[i], l_contents[i]))
