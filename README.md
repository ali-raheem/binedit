# binedit

Simple utility to let you patch files with arbitary data.

## Building

`gcc -O2 -o bin/binedit src/binedit.c`

## Usage

binedit can take the bytes to patch in either as a command line argument (convient unless you need to patch in nullbytes) or from a file.

Printable characters are easiest to use:

`binedit inFile 10 "Quotes are needed if you have spaces!"`

Non-printable characters are not so bad either:

`binedit inFile 10 $(printf 'A\x01B')`

But null byte (\x00) will need to be passed in via a patch file:

```bash
printf 'A\x00B' > patch_data_file
binedit inFile 10 -f patch_data_file
```

