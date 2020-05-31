# win_eXPerience 1

## Solution

Searching for a memory analysis tool, one quickly finds [volatility](https://github.com/volatilityfoundation/volatility).

The first thing I thought of was doing a filescan and grep for interesting filenames:
```
$ volatility -f memory.dmp --profile=WinXPSP2x86 filescan | grep "flag"
Volatility Foundation Volatility Framework 2.6.1
0x00000000017c90e8      1      0 R--rwd \Device\HarddiskVolume1\Documents and Settings\CSCG\Desktop\CSCG\cscg.flag.PNG
0x0000000001a3c7e8      1      0 R--rwd \Device\TrueCryptVolumeE\flag.zip
```

The first file turns out to be a relict from an older challenge, so we extract the `flag.zip` with:<br/>
```
$ volatility -f memory.dmp --profile=WinXPSP2x86 dumpfiles -Q 0x0000000001a3c7e8 -D .
$ mv file.None.0x81732ef8.dat flag.zip
```

Trying to unzip the file prompts us for a password. Going through the options of volatility, we can try to see if there's anything interesting in the clipboard:
```
$ volatility -f memory.dmp --profile=WinXPSP2x86 clipboard
Volatility Foundation Volatility Framework 2.6.1
Session    WindowStation Format                 Handle Object     Data                                              
---------- ------------- ------------------ ---------- ---------- --------------------------------------------------
         0 WinSta0       CF_UNICODETEXT        0x500b5 0xe1d523d8 BorlandDelphiIsReallyCool                         
         0 WinSta0       CF_LOCALE            0x1401b7 0xe10cb418                                                   
         0 WinSta0       CF_TEXT                   0x1 ----------                                                   
         0 WinSta0       CF_OEMTEXT                0x1 ----------                                                   
```

Trying to extract the contents of `flag.zip` with `BorlandDelphiIsReallyCool` as a password:
```
$ 7z x flag.zip
$ cat flag.txt
CSCG{c4ch3d_p455w0rd_fr0m_0p3n_tru3_cryp1_c0nt41n3r5}
```

## Mitigation

Don't make a memory dump with confidential information and post it online for everyone to analyze.

