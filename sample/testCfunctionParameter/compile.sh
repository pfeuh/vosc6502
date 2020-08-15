#!/bin/sh
echo $SHELL $0 "launched by" $USER $(date)

#~ cl65 -O -t atari credits.c printTool.c rainbow.s text.s -o CREDITS.COM
cl65 -O -t atari main.c -o PROGRAM.XEX

errnum=$?
if test $errnum -eq 0;then
echo COMPILATION SUCCESSFUL!
else
echo COMPILATION FAILED error $errnum
exit 1
fi
