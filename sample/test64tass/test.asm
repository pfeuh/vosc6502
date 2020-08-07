            
            VOSC_IO_PUTSCR = $bf00
            RUN_VECTOR = $fff0

            * = $200
main:      
			lda #$48
			sta VOSC_IO_PUTSCR
			lda #$65
			sta VOSC_IO_PUTSCR
			lda #$6c
			sta VOSC_IO_PUTSCR
			lda #$6c
			sta VOSC_IO_PUTSCR
			lda #$6f
			sta VOSC_IO_PUTSCR
			lda #$2c
			sta VOSC_IO_PUTSCR
			lda #$20
			sta VOSC_IO_PUTSCR
			lda #$57
			sta VOSC_IO_PUTSCR
			lda #$6f
			sta VOSC_IO_PUTSCR
			lda #$72
			sta VOSC_IO_PUTSCR
			lda #$6c
			sta VOSC_IO_PUTSCR
			lda #$64
			sta VOSC_IO_PUTSCR
			lda #$21
			sta VOSC_IO_PUTSCR
			lda #$0a
			sta VOSC_IO_PUTSCR
            brk

RUN_VECTOR:
            * = RUN_VECTOR
            .word main