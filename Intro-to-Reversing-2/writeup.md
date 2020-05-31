# Intro to Reversing 2

## Solution

I took a quite different approach to the challenge. When running `ltrace ./rev2` I noticed this when entering `abc` as a password:
```
...
strcmp("\352\353\354", "\374\375\352\300\272\354\350\375\373\275\367\276\357\271\373\366\275\300\272\271\367\350\362\375\350\362\374") = -18
puts("Thats not the password!"Thats not the password!
)                                                                                                   = 24
```
This means `a` is `\352`, b is `\353` and c is `\353`. I guess we can do this with every character and then just replace `\374\375\352\300\272\354\350\375\373\275\367\276\357\271\373\366\275\300\272\271\367\350\362\375\350\362\374`
with the according values, which then should be our password:

```python
#!/usr/bin/env python3

s = "\\374\\375\\352\\300\\272\\354\\350\\375\\373\\275\\367\\276\\357\\271\\373\\366\\275\\300\\272\\271\\367\\350\\362\\375\\350\\362\\374"

s = s.replace("\\352", "a")
s = s.replace("\\353", "b")
s = s.replace("\\354", "c")
s = s.replace("\\355", "d")
s = s.replace("\\356", "e")
s = s.replace("\\357", "f")
s = s.replace("\\360", "g")
s = s.replace("\\361", "h")
s = s.replace("\\362", "i")
s = s.replace("\\363", "j")
s = s.replace("\\364", "k")
s = s.replace("\\365", "l")
s = s.replace("\\366", "m")
s = s.replace("\\367", "n")
s = s.replace("\\370", "o")
s = s.replace("\\371", "p")
s = s.replace("\\372", "q")
s = s.replace("\\373", "r")
s = s.replace("\\374", "s")
s = s.replace("\\375", "t")
s = s.replace("\\376", "u")
s = s.replace("\\377", "v")
s = s.replace("\\001", "x")
s = s.replace("\\002", "y")
s = s.replace("\\003", "z")
s = s.replace("\\350", "_")
s = s.replace("\\271", "0")
s = s.replace("\\272", "1")
s = s.replace("\\273", "2")
s = s.replace("\\274", "3")
s = s.replace("\\275", "4")
s = s.replace("\\276", "5")
s = s.replace("\\277", "6")
s = s.replace("\\300", "7")

print(s)
```

I'm pretty sure, I could've just reversed the algorithm, but that worked for me too and we get the password: `sta71c_tr4n5f0rm4710n_it_is`.

Flag: `CSCG{1s_th4t_wh4t_they_c4ll_on3way_transf0rmati0n?}`


## Mitigation

Similar to the previous challenge, the verification of a password on the client-side is probably always bypassable and should therefore rather be done server-side.
