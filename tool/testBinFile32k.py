#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys

write = sys.stdout.write

def writeln(text):
    sys.stdout.write("%s\n"%text)

FNAME = "./../sample/testcc65segments/TEST.BIN"

fp = open(FNAME, 'rb')

for x in range(32768):
    if not (x & 15):
        write("%04x "%x)
        
    write("%02x "%ord(fp.read(1)))

    if (x & 15) == 15:
        write("\n")
    