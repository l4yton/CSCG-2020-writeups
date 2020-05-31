#!/usr/bin/env python3

import argparse
import base64
import cv2
import requests
import re
import time
import os


parser = argparse.ArgumentParser()
parser.add_argument("-n", "--number", type=int, default=100, help="how many captchas to get")
parser.add_argument("-d", "--delay", type=float, default=0.4, help="delay between requests")
args = parser.parse_args()

url = "http://hax1.allesctf.net:9200/captcha/0"


def getCaptcha(session):

    r = session.get(url)

    re_img = re.search("iV[\w\=\+\/]+", r.text)
    img = base64.b64decode(re_img.group(0))

    f = open("captcha.png", "wb")
    f.write(img)
    f.close()

    return


def getSolution(session):

    data = {}
    data["0"] = ""

    r = session.post(url, data=data, allow_redirects=False)

    solution = re.search("(?<=solution\=)[\w]+", r.text)

    return solution.group(0)


def main():

    print("===== COLLECTING CAPTCHAS =====\n")

    for n in range(1, args.number):

        print(f"[i] COUNT: {n}...", end="\r")

        session = requests.Session()

        getCaptcha(session)

        solution = getSolution(session)

        os.replace("captcha.png", f"training-captchas/{solution}.png")

        time.sleep(args.delay)

    print(f"[i] COUNT: {args.number}...\n")

    print("=========== FINISHED! =========")

if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        print("[i] Quitting...")
        quit()

