# binedit

Simple utility to let you patch files with arbitary data.

## Building

`gcc -O2 -o bin/binedit src/binedit.c`

## Running

`binedit inputfile 10 patch_data`

Will replace bytes at offset 10 of the file inputfile.txt with the contents of patch_data.txt and output to STDOUT.

A patch file makes using patch data with a null byte easier for example:

`printf '\x00' > patch_data`
