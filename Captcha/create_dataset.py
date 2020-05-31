#!/usr/bin/env python3

import sys
import os


print("==== CREATING DATASET FILE ====\n")
print("SAVING IN:", "captcha-" + sys.argv[1] + ".txt")

PATH = "/".join(os.path.realpath(__file__).split("/")[:-1])

f = open("captcha-" + sys.argv[1] + ".txt", "a")
length = []

for file in os.listdir(sys.argv[1] + "-captchas"):

    solution = file.split(".")[0]
    length.append(len(solution))

    f.write(PATH + "/" + sys.argv[1] + "-captchas/" + file + " " + solution + "\n")

print("MAX SOLUTION LENGTH:", max(length))
print("\n========== FINISHED! ==========")
f.close()

