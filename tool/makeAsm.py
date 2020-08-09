#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys

def writeln(text):
    sys.stdout.write("%s\n"%text)

for car in "Hello, World!\n":
    writeln("lda #$%02x"%ord(car))
    writeln("sta VOSC_IO_PUTSCR")