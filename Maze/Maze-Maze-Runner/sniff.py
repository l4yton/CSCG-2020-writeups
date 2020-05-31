#!/usr/bin/env python3

# Ports: 1337 - 1357

from scapy.all import sniff
import struct

filter_udp = "udp and ( " + " or ".join(["src port " + str(1337 +i) for i in range(21)]) + " )"

def decode(data):

    r = bytearray.fromhex(data)

    first_random    = r[0]
    second_random   = r[1]
    decoded = []

    for i in range(0, len(r) - 2):

        decoded.append(first_random ^ r[i+2])

        v21 = first_random + second_random
        first_random = (v21 + ((2155905153 * v21) >> 39)) & 0xff

    return decoded


def pkt_callback(pkt): # pkt: "Ethernet", "IP", "UDP", "Raw" 

    r = bytes(pkt["Raw"]).hex()

    r = decode(r)

    if r[0] == 82:
        print("Passed checkpoint:", r[1])
        return

    string = "".join([chr(r) for r in r])

    if "CSCG" in string:
        print(string)

    return

try:
    sniff(prn=pkt_callback, filter=filter_udp, store=0)
except KeyboardInterrupt:
    pass

