ca65 V2.16 - Ubuntu 2.16-2
Main file   : print.asm
Current file: print.asm

000000r 1                           .export _main
000000r 1               
000000r 1                           ; screen output hardware register
000000r 1                           VOSC_IO_PUTSCR = $bf00
000000r 1               
000000r 1                           ; * = $600
000000r 1               _main:
000000r 1  A2 rr                    ldx #<splash
000002r 1  A0 rr                    ldy #>splash
000004r 1  20 rr rr                 jsr print
000007r 1  00                       brk
000008r 1               
000008r 1               print:
000008r 1                           op1 = 0
000008r 1  86 00                    stx op1
00000Ar 1  84 01                    sty op1+1
00000Cr 1  A2 00                    ldx #0
00000Er 1               print_l1:
00000Er 1  B1 00                    lda (op1),y
000010r 1  C9 00                    cmp #0
000012r 1  F0 06                    beq print_out
000014r 1  8D 00 BF                 sta VOSC_IO_PUTSCR
000017r 1  E8                       inx
000018r 1  D0 F4                    bne print_l1
00001Ar 1               print_out:
00001Ar 1  60                       rts
00001Br 1               
00001Br 1               splash:
00001Br 1  56 4F 53 43              .asciiz "VOSC6502 (Virtual Old School Computer with a 6502 processor)\nversion 0.99 -------------------------- MMXX - Pierre Faller\n"
00001Fr 1  36 35 30 32  
000023r 1  20 28 56 69  
000098r 1               
000098r 1               
000098r 1               
000098r 1               
000098r 1               
