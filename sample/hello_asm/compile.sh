#!/bin/sh
echo $SHELL $0 "launched by" $USER $(date)
cd ./

cl65 -O -t atari hello.asm -o HELLO_ASM.BIN

errnum=$?
if test $errnum -eq 0;then
#~ ./vosc6502.exe
echo COMPILATION SUCCESSFUL!
fi
