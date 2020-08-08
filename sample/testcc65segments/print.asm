            .export _main
            
            VOSC_IO_PUTSCR = $bf00

            ; * = $600
_main:      
            ldx #<splash
            ldy #>splash
            jsr print
            brk
            
print:
            op1 = 0
            stx op1
            sty op1+1
            ldx #0
print_l1:
            lda (op1),y
            cmp #0
            beq print_out
            sta VOSC_IO_PUTSCR
            inx
            bne print_l1
print_out:
            rts
            
splash:
            .asciiz "VOSC6502 (Virtual Old School Computer with a 6502 processor)\nversion 0.99 -------------------------- MMXX - Pierre Faller\n"




