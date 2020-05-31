# Intro to Stegano 1

## Solution

We are given an image file. The first thing I usually do, is running [`exiftool`](https://exiftool.org/):
```
$ exiftool chall.jpg
fTool Version Number         : 11.85
File Name                       : chall.jpg
Directory                       : .
File Size                       : 172 kB
File Modification Date/Time     : 2020:04:06 17:35:32+02:00
File Access Date/Time           : 2020:04:06 17:35:32+02:00
File Inode Change Date/Time     : 2020:04:06 17:50:00+02:00
File Permissions                : rw-r--r--
File Type                       : JPEG
File Type Extension             : jpg
MIME Type                       : image/jpeg
JFIF Version                    : 1.01
Resolution Unit                 : inches
X Resolution                    : 72
Y Resolution                    : 72
Comment                         : alm1ghty_st3g4n0_pls_g1v_fl4g
Image Width                     : 1024
Image Height                    : 1128
Encoding Process                : Baseline DCT, Huffman coding
Bits Per Sample                 : 8
Color Components                : 3
Y Cb Cr Sub Sampling            : YCbCr4:4:4 (1 1)
Image Size                      : 1024x1128
Megapixels                      : 1.2
```

We find an interesting exif comment, guess we have to keep that in mind for later.
<br/>
Next, I used a tool called [`steghide`](http://steghide.sourceforge.net/) that can detect and extract hidden files in images:
```
$ steghide extract -sf chall.jgp
Enter passphrase:
```
Oh, looks like the file is protected with passphrase. What about the exif comment earlier?
```
$ steghide extract -sf chall.jpg
Enter passphrase: alm1ghty_st3g4n0_pls_g1v_fl4g
wrote extracted data to "flag.txt".
```

```
$ cat flag.text
CSCG{Sup3r_s3cr3t_d4t4}
```

## Mitigation

Don't put the password for the hidden file in an exif comment.
