# Intro to Reversing 3

## Solution

I used Ghidra to decompile the binary. We can pretty quickly find the `main` function and this is also where all the magic happens:
```c
  puts("Give me your password: ");
  sVar2 = read(0,local_38,0x1f);
  local_38[(int)sVar2 + -1] = 0;
  local_40 = 0;
  while (local_40 < (int)sVar2 + -1) {
    local_38[local_40] = local_38[local_40] ^ (char)local_40 + 10U;
    local_38[local_40] = local_38[local_40] - 2;
    local_40 = local_40 + 1;
  }
  iVar1 = strcmp((char *)local_38,"lp`7a<qLw\x1ekHopt(f-f*,o}V\x0f\x15J");
```
We can see that it loops through every characater of our input, XORs it with the index of that character + 10 and afterwards subtracts 2.
That result is then compared with the string ```ilp`7a<qLw\x1ekHopt(f-f*,o}V\x0f\x15J```.
<br/> <br/>
So we just have to do that backwards with the string ```ilp`7a<qLw\x1ekHopt(f-f*,o}V\x0f\x15J``` to get the password. Iterate over every character add 2 and then XOR it with its index + 10:
```python
#!/usr/bin/env python3

print("".join([chr((i+2)^s+10) for s,i in enumerate(b"lp`7a<qLw\x1ekHopt(f-f*,o}V\x0f\x15J")]))
```
The password is: `dyn4m1c_k3y_gen3r4t10n_y34h`
<br/> <br/>
Flag: `CSCG{pass_1_g3ts_a_x0r_p4ss_2_g3ts_a_x0r_EVERYBODY_GETS_A_X0R}`


## Mitigation

Still the same as in the previous challenges, don't verify passwords client-side, do it server-side, so that the user doesn't have access to the code that verifies the password.
