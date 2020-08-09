ataload sample/testInterrupt/TEST.BIN
; sb 209d
; wpokerom fffc 206f ; run vector
; wpokerom fffe 3412 ; irq vector
; wpokerom fffa 7856 ; nmi vector


