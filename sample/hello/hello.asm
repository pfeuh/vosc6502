            .export _main
            
            VOSC_IO_PUTSCR = $fe00

            ; * = $600
_main:      ldx #0
            lda message,x
            cmp #0
            beq stop
            ; sta $fe00 ;VOSC_IO_PUTSCR
            sta VOSC_IO_PUTSCR
            bne _main
stop:       brk

message:    .asciiz "Hello, World!\n"
            
            ; * = $fffc
            ; .word start