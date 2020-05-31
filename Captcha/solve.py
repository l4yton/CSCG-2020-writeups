#!/usr/bin/env python2

import base64
import requests
import re
import os
import subprocess
import time

# turn off tensorflow warnings
os.environ["TF_CPP_MIN_LOG_LEVEL"] = "3"


def solveCaptchas(captchas):

    f = open("/tmp/names.txt", "w")
    f.write("\n".join(captchas))
    f.close()

    p = subprocess.Popen("cat /tmp/names.txt | aocr predict --max-width 355 --max-height 30 --max-prediction 15", shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    p.wait()
    out, err = p.communicate()

    solutions = []

    for solution in re.findall("(?<= )[A-Z0-9]{6,15}", err):
        solutions.append(solution)

    return solutions


def stage1(session):

    r = session.get("http://hax1.allesctf.net:9200/captcha/0")

    re_img = re.search("iV[\w\=\+\/]+", r.text)
    img = base64.b64decode(re_img.group(0))

    f = open("captcha.png", "wb")
    f.write(img)
    f.close()

    solution = solveCaptchas(["captcha.png"])[0]

    print("Stage 0:", solution)

    data = {}
    data["0"] = solution

    r = session.post("http://hax1.allesctf.net:9200/captcha/0", data=data)

    return r


def stageN(session, page, stage_number):

    re_img = re.findall("iV[\w\=\+\/]+", page.text)

    data = {}
    captchas = []

    for n, img in enumerate(re_img):

        img = base64.b64decode(img)
        name = "captcha" + str(n) + ".png"

        f = open(name, "wb")
        f.write(img)
        f.close()

        captchas.append(name)

    start = time.time()

    solutions = solveCaptchas(captchas)

    for n, solution in enumerate(solutions):

        print("Stage " + str(stage_number) + "[" + str(n) + "]:", solution)

        data[str(n)] = solution

    end = time.time()

    print("Time:", end-start)

    r = session.post("http://hax1.allesctf.net:9200/captcha/" + str(stage_number), data=data)

    return r


def main():

    print("=" * 18 + " STAGE 0 " + "=" * 18)
    session = requests.Session()

    next_page = stage1(session)

    if "fail" in next_page.url:
        print(next_page.url)
        print("=" * 18 + " FAILED! " + "=" * 18)
        quit()


    print("=" * 18 + " STAGE 1 " + "=" * 18)

    next_page = stageN(session, next_page, 1)

    if "fail" in next_page.url:
        print("=" * 18 + " FAILED! " + "=" * 18)
        quit()

    print("=" * 18 + " STAGE 2 " + "=" * 18)

    next_page = stageN(session, next_page, 2)

    if "fail" in next_page.url:
        print("=" * 18 + " FAILED! " + "=" * 18)
        quit()

    print("=" * 18 + " STAGE 3 " + "=" * 18)

    next_page = stageN(session, next_page, 3)

    if "fail" in next_page.url:
        print("=" * 18 + " FAILED! " + "=" * 18)
        quit()

    print("=" * 19 + " FLAG! " + "=" * 19)

    re_img = re.search("iV[\w\=\+\/]+", next_page.text)
    img = base64.b64decode(re_img.group(0))

    f = open("flag.png", "wb")
    f.write(img)
    f.close()

    print("SAVED FLAG IN: flag.png")

if __name__ == "__main__":
    main()
