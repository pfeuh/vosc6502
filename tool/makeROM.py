#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys
write = sys.stdout.write

data = "\
a9 48 8d 00 bf a9 65 8d 00 bf a9 6c 8d 00 bf a9 \
6c 8d 00 bf a9 6f 8d 00 bf a9 2c 8d 00 bf a9 20 \
8d 00 bf a9 57 8d 00 bf a9 6f 8d 00 bf a9 72 8d \
00 bf a9 6c 8d 00 bf a9 64 8d 00 bf a9 21 8d 00 \
bf a9 0a 8d 00 bf 00 ad 16 21 ae 17 21 20 dd 20 \
ad 18 21 ae 19 21 20 dd 20 a0 04 4c 6f 20 a0 00 \
f0 07 a9 16 a2 21 4c 1a 21 60 a9 00 a2 00 48 a5 \
82 38 e9 02 85 82 b0 02 c6 83 a0 01 8a 91 82 68 \
88 91 82 60 a9 3f 85 8a a9 21 85 8b a9 00 a8 a2 \
00 f0 0a 91 8a c8 d0 fb e6 8b ca d0 f6 c0 05 f0 \
05 91 8a c8 d0 f7 60 00 00 00 00 8d 28 21 8e 29 \
21 8d 2f 21 8e 30 21 88 b9 ff ff 8d 39 21 88 b9 \
ff ff 8d 38 21 8c 3b 21 20 ff ff a0 ff d0 e8 60 \
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 \
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 \
00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 "

def writeln(text):
    sys.stdout.write("%s\n"%text)

FNAME = "./../sample/testcc65segments/DUMMYROM"

ROM_SIZE = 0x1000
ROM_ADDR = 0x10000 - ROM_SIZE
 
# putting program in ROM
bytes = [int(word, 16)for word in data.split()]
# stuffing with ff
for x in range(4096 - len(bytes)):
    bytes.append(255)
# adding RUN VECTOR
bytes[ROM_SIZE - 4 ] = ROM_ADDR & 0xff
bytes[ROM_SIZE - 3 ] = ROM_ADDR / 0x100

# Saving ROM
fp = open(FNAME, 'wb')
for x in range(ROM_SIZE):
    fp.write(chr(bytes[x]))
fp.close()
