# Intro to Reversing 1

## Solution

When executing `rev1` we are prompted for a password:
```
$ ./rev1
Give me your password:
```
Running `strings rev1` reveals an interesting string:
```
$ strings rev1
...
y0u_5h3ll_p455
...
```
And indeed, it turns out to be the correct password.
<br/> <br/>

Flag: `CSCG{ez_pz_reversing_squ33zy}`

## Mitigation

Do not write the password in cleartext in the source code. Or even better, do not verify the password client-side, but server-side.
