#!/usr/bin/python
# -*- coding: utf-8 -*-

import sys

def writeln(text):
    sys.stdout.write("%s\n"%text)


def getTable(fname_in, fname_out):
    fp = open(fname_in, "r")
    lines = [line.strip() for line in fp.readlines()]
    for index, line in enumerate(lines):
        words = [word.strip().lower() for word in line.split()]
        lines[index] = words
    print lines
    
if __name__ == "__main__":
    
    getTable("../sample/testInterrupt/symbols.txt", None)
