# Intro to Crypto 3

For this challenge we are given three different public keys (german_government.pem, russian_government.pem, us_government.pem) and a file containing three encrypted messages (intercepted-messages.txt).

## Solution

Going through a [list of RSA attacks made for CTFs](https://github.com/ValarDragon/CTF-Crypto/blob/master/README.md), I found that the [Chinese remainder theorem](https://en.wikipedia.org/wiki/Chinese_remainder_theorem)
seems to be fitting for this challenge. <br/>

Being lazy, I took the script kiddie approach and searched for a tool running that attack: https://github.com/JulesDT/RSA-Hastad.
I seperated the messages in `intercepted-messages.txt` to `german.txt`, `russian.txt` and `us.txt` and ran the tool:
```
$ python2 RSA-Hastad/rsaHastad.py german_government.pem russian_government.pem us_government.pem german.txt russian.txt us.txt --decimal


        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
                RSA Hastad Attack         
                 JulesDT -- 2016          
                 License GNU/GPL          
        ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
Decoded Hex :
414141414141414141414141414141414141414141414141414141414141414141414141414141414141414141414141414141414141414141414141414141414141414141414141414141435343477b6368316e6573335f67307665726e6d336e745f6834735f6e305f707230626c656d5f773174685f6330726f6e347d
---------------------------
As Ascii :
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAACSCG{ch1nes3_g0vernm3nt_h4s_n0_pr0blem_w1th_c0ron4}
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
```

Flag: `CSCG{ch1nes3_g0vernm3nt_h4s_n0_pr0blem_w1th_c0ron4}`

## Mitigation

Do not encrypt the same message multiple times with different RSA public keys (that also have the same exponent).
