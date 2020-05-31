#!/usr/bin/env python3

import sys


for data in sys.stdin:

    r = bytearray.fromhex(data)

    first_random    = r[0]
    second_random   = r[1]

    decoded = []

    print("First Random:", first_random)
    print("Second Random:", second_random)

    for i in range(0, len(r) - 2):

        decoded.append(first_random ^ r[i+2])

        v21 = first_random + second_random
        first_random = (v21 + ((2155905153 * v21) >> 39)) & 0xff

    start = 0

    if chr(decoded[0]) == "<":

        indicator = chr(decoded[0]) + chr(decoded[1])
        start += 1

    else:
        indicator = chr(decoded[0])

    secret      = decoded[start+1:start+9]
    time        = int.from_bytes(decoded[start+9:start+17], byteorder="little")
    position_x  = int.from_bytes(decoded[start+17:start+21], byteorder="little")
    position_y  = int.from_bytes(decoded[start+21:start+25], byteorder="little")
    position_z  = int.from_bytes(decoded[start+25:start+29], byteorder="little")
    euler_x     = int.from_bytes(decoded[start+29:start+33], byteorder="little")
    euler_y     = int.from_bytes(decoded[start+33:start+37], byteorder="little")
    euler_z     = int.from_bytes(decoded[start+37:start+41], byteorder="little")

    print("Bytearray:", decoded)
    print("Indicator:", indicator)
    print("Time:", time)
    print("Secret:", secret)
    print("Position X:", int(position_x / 10000))
    print("Position Y:", int(position_y / 10000))
    print("Position Z:", int(position_z / 10000))
    print("Euler X:", int(euler_x / 10000))
    print("Euler Y:", int(euler_y / 10000))
    print("Euler Z:", int(euler_z / 10000))
    print("-"*20)
