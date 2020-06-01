# binedit

Simple utility to let you patch files with arbitary data.

## Building

`gcc -O2 -o bin/binedit src/binedit.c`

## Usage

binedit can take the bytes to patch in either as a command line argument or from a file.

You can parse in arbitary data as a hex string like so:

`binedit inFile 10 'aAbB\x20\x00\x41c'`

Note you must format the bytes as \xHH where HH are the hexidecimal characters.

Sometimes the command line will argue with you if you have anything but simple printable characters as an argument, if that's the case use a patch data file like so:

```bash
printf 'A\x00B' > patch_data_file
binedit inFile 10 -f patch_data_file
```

The offset can be provided in hexdecimal format, but this should be prefixed by "0x" otherwise it'll be interpretted as decimal.
