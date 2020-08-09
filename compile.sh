#!/bin/sh
echo $SHELL $0 "launched by" $USER $(date)
cd ./src

gcc -Wall main.c console.c interpreter.c fake6502.c memory.c commands.c dump.c screen.c keyboard.c random.c desass6502.c emulator.c finder.c timers.c -o ../vosc6502.exe
#~ gcc -Wall utest_inputNumber.c console.c -o utest_inputNumber.exe

errnum=$?
if test $errnum -eq 0;then
#~ ./vosc6502.exe
echo COMPILATION SUCCESSFUL!
fi
