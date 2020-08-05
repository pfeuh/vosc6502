#!/bin/sh
echo $SHELL $0 "launched by" $USER $(date)
cd ./

#~ cc65 -V -t atarixl hello.asm -o hello.obj
#~ cl65 -O -t atari hello.asm -o HELLO.COM
cl65 -O -t atari hello2.asm -o HELLO2.COM

errnum=$?
if test $errnum -eq 0;then
#~ ./vosc6502.exe
echo COMPILATION SUCCESSFUL!
fi
