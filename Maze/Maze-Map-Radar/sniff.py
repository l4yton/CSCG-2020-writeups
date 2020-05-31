#!/usr/bin/env python3

# Ports: 1337 - 1357

from scapy.all import sniff
import struct

filter_udp = "udp and ( " + " or ".join(["dst port " + str(1337 +i) for i in range(21)]) + " )"
TIME = 0

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

    global TIME

    r = bytes(pkt["Raw"]).hex()

    if len(r) == 96:
        r = decode(r)
        t = struct.unpack("<q", bytes(r[9:17]))[0] / 10000
        x = struct.unpack("<i", bytes(r[17:21]))[0] / 10000
        y = struct.unpack("<i", bytes(r[21:25]))[0] / 10000
        z = struct.unpack("<i", bytes(r[25:29]))[0] / 10000

        print("T:", int(t), "|", "X:", int(x), "|", "Y:", int(y), "|", "Z", int(z))

try:
    sniff(prn=pkt_callback, filter=filter_udp, store=0)
except KeyboardInterrupt:
    pass

