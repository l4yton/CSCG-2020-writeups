#!/usr/bin/env python3

from Crypto.PublicKey import RSA

m = int.from_bytes(b"Quack! Quack!", "big")
c = int.from_bytes(b"Hello! Can you give me the flag, please? I would really appreciate it!", "big")

N = c - m
d = 1
e = 3

for i in range(1,3000):
    if N % i == 0:
        p = i

q = N // p


private_key = RSA.construct((N, e, d, p, q), consistency_check=False)

#print(private_key)
