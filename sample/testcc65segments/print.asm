            .export _main
            
            CHAR_RETURN = $0a
            
            ; screen output hardware register
            VOSC_IO_PUTSCR = $bf00

            ; * = $600
_main:      
            ldx #<splash1
            ldy #>splash1
            jsr println
            ldx #<splash2
            ldy #>splash2
            jsr println
            brk
            
println:
            jsr print
            lda #CHAR_RETURN
            sta VOSC_IO_PUTSCR
            rts
            
print:
            op1 = 0
            stx op1
            sty op1+1
            ldy #0

print_l1:
            lda (op1),y
            cmp #0
            beq print_out
            sta VOSC_IO_PUTSCR
            iny
            bne print_l1
print_out:
            rts
            
splash1:
            .asciiz "VOSC6502 (Virtual Old School Computer with a 6502 processor)"
splash2:
            .asciiz "version 0.99 -------------------------- MMXX - Pierre Faller"




