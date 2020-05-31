#!/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np

x = [ int(x) for x in open("X.txt", "r").read().split("\n") if x != ""]
y = [ int(y) for y in open("Y.txt", "r").read().split("\n") if y != ""]

plt.scatter(x, y, s=5)
plt.show()

