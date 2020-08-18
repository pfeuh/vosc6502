
    ; --------------------------------------- ;
    ;  this program is supposed to uses all   ;
    ;       the official 6502 opcodes         ;
    ; --------------------------------------- ;

    ;* = $200 ; (un)comment if neccessary
    _main: ; (un)comment if neccessary
    .export _main

LABEL_01:
    BRK          ; opcode $00
    ORA ($A7,X)  ; opcode $01
                 ; opcode $02 (illegal)
                 ; opcode $03 (illegal)
                 ; opcode $04 (illegal)
    ORA $6C      ; opcode $05
    ASL $C1      ; opcode $06
                 ; opcode $07 (illegal)
    PHP          ; opcode $08
    ORA #$F5     ; opcode $09
    ASL A        ; opcode $0a
                 ; opcode $0b (illegal)
                 ; opcode $0c (illegal)
    ORA $87A6    ; opcode $0d
    ASL $467E    ; opcode $0e
                 ; opcode $0f (illegal)
LABEL_02:
    BPL LABEL_02 ; opcode $10
    ORA ($52),Y  ; opcode $11
                 ; opcode $12 (illegal)
                 ; opcode $13 (illegal)
                 ; opcode $14 (illegal)
    ORA $07,X    ; opcode $15
    ASL $4D,X    ; opcode $16
                 ; opcode $17 (illegal)
    CLC          ; opcode $18
    ORA $E97E,Y  ; opcode $19
                 ; opcode $1a (illegal)
                 ; opcode $1b (illegal)
                 ; opcode $1c (illegal)
    ORA $50F5,X  ; opcode $1d
    ASL $241E,X  ; opcode $1e
                 ; opcode $1f (illegal)
LABEL_03:
    JSR $B1DA    ; opcode $20
    AND ($96,X)  ; opcode $21
                 ; opcode $22 (illegal)
                 ; opcode $23 (illegal)
    BIT $D0      ; opcode $24
    AND $D1      ; opcode $25
    ROL $D8      ; opcode $26
                 ; opcode $27 (illegal)
    PLP          ; opcode $28
    AND #$79     ; opcode $29
    ROL A        ; opcode $2a
                 ; opcode $2b (illegal)
    BIT $BC10    ; opcode $2c
    AND $97CD    ; opcode $2d
    ROL $1678    ; opcode $2e
                 ; opcode $2f (illegal)
LABEL_04:
    BMI LABEL_04 ; opcode $30
    AND ($66),Y  ; opcode $31
                 ; opcode $32 (illegal)
                 ; opcode $33 (illegal)
                 ; opcode $34 (illegal)
    AND $72,X    ; opcode $35
    ROL $FB,X    ; opcode $36
                 ; opcode $37 (illegal)
    SEC          ; opcode $38
    AND $9FBA,Y  ; opcode $39
                 ; opcode $3a (illegal)
                 ; opcode $3b (illegal)
                 ; opcode $3c (illegal)
    ORA $64AB,X  ; opcode $3d
    ASL $5D20,X  ; opcode $3e
                 ; opcode $3f (illegal)
LABEL_05:
    RTI          ; opcode $40
    EOR ($28,X)  ; opcode $41
                 ; opcode $42 (illegal)
                 ; opcode $43 (illegal)
                 ; opcode $44 (illegal)
    EOR $D7      ; opcode $45
    LSR $15      ; opcode $46
                 ; opcode $47 (illegal)
    PHA          ; opcode $48
    EOR #$A5     ; opcode $49
    LSR A        ; opcode $4a
                 ; opcode $4b (illegal)
    JMP $F3FE    ; opcode $4c
    EOR $6571    ; opcode $4d
    LSR $286C    ; opcode $4e
                 ; opcode $4f (illegal)
LABEL_06:
    BVC LABEL_06 ; opcode $50
    EOR ($B2),Y  ; opcode $51
                 ; opcode $52 (illegal)
                 ; opcode $53 (illegal)
                 ; opcode $54 (illegal)
    EOR $0C,X    ; opcode $55
    LSR $A4,X    ; opcode $56
                 ; opcode $57 (illegal)
    CLI          ; opcode $58
    EOR $2BB7,Y  ; opcode $59
                 ; opcode $5a (illegal)
                 ; opcode $5b (illegal)
                 ; opcode $5c (illegal)
    EOR $CD9D,X  ; opcode $5d
    LSR $40B3,X  ; opcode $5e
                 ; opcode $5f (illegal)
LABEL_07:
    RTS          ; opcode $60
    ADC ($5E,X)  ; opcode $61
                 ; opcode $62 (illegal)
                 ; opcode $63 (illegal)
                 ; opcode $64 (illegal)
    ADC $59      ; opcode $65
    ROR $A2      ; opcode $66
                 ; opcode $67 (illegal)
    PLA          ; opcode $68
    ADC #$48     ; opcode $69
    ROR A        ; opcode $6a
                 ; opcode $6b (illegal)
    JMP($E120)   ; opcode $6c
    ADC $5334    ; opcode $6d
    ROR $3D76    ; opcode $6e
                 ; opcode $6f (illegal)
LABEL_08:
    BCS LABEL_08 ; opcode $70
    ADC ($DD),Y  ; opcode $71
                 ; opcode $72 (illegal)
                 ; opcode $73 (illegal)
                 ; opcode $74 (illegal)
    ADC $73,X    ; opcode $75
    ROR $A3,X    ; opcode $76
                 ; opcode $77 (illegal)
    SEI          ; opcode $78
    ADC $4001,Y  ; opcode $79
                 ; opcode $7a (illegal)
                 ; opcode $7b (illegal)
                 ; opcode $7c (illegal)
    ADC $6168,X  ; opcode $7d
    ROR $50E3,X  ; opcode $7e
                 ; opcode $7f (illegal)
LABEL_09:
                 ; opcode $80 (illegal)
    STA ($07,X)  ; opcode $81
                 ; opcode $82 (illegal)
                 ; opcode $83 (illegal)
    STY $C1      ; opcode $84
    STA $3C      ; opcode $85
    STX $82      ; opcode $86
                 ; opcode $87 (illegal)
    DEY          ; opcode $88
                 ; opcode $89 (illegal)
    TXA          ; opcode $8a
                 ; opcode $8b (illegal)
    STY $D1A1    ; opcode $8c
    STA $7DD2    ; opcode $8d
    STX $51E3    ; opcode $8e
                 ; opcode $8f (illegal)
LABEL_10:
    BCC LABEL_10 ; opcode $90
    STA ($3B),Y  ; opcode $91
                 ; opcode $92 (illegal)
                 ; opcode $93 (illegal)
    STY $03,X    ; opcode $94
    STA $21,X    ; opcode $95
    STX $0E,Y    ; opcode $96
                 ; opcode $97 (illegal)
    TYA          ; opcode $98
    STA $A2FF,Y  ; opcode $99
    TXS          ; opcode $9a
                 ; opcode $9b (illegal)
                 ; opcode $9c (illegal)
    STA $0AFB,X  ; opcode $9d
                 ; opcode $9e (illegal)
                 ; opcode $9f (illegal)
LABEL_11:
    LDY #$06     ; opcode $a0
    LDA ($0A,X)  ; opcode $a1
    LDX #$C6     ; opcode $a2
                 ; opcode $a3 (illegal)
    LDY $C8      ; opcode $a4
    LDA $90      ; opcode $a5
    LDX $CE      ; opcode $a6
                 ; opcode $a7 (illegal)
    TAY          ; opcode $a8
    LDA #$33     ; opcode $a9
    TAX          ; opcode $aa
                 ; opcode $ab (illegal)
    LDY $DD3D    ; opcode $ac
    LDA $CD98    ; opcode $ad
    LDX $E51D    ; opcode $ae
                 ; opcode $af (illegal)
LABEL_12:
    BCS LABEL_12 ; opcode $b0
    LDA ($F3),Y  ; opcode $b1
                 ; opcode $b2 (illegal)
                 ; opcode $b3 (illegal)
    LDY $E0,X    ; opcode $b4
    LDA $F7,X    ; opcode $b5
    LDX $F1,Y    ; opcode $b6
                 ; opcode $b7 (illegal)
    CLV          ; opcode $b8
    LDA $CEAA,Y  ; opcode $b9
    TSX          ; opcode $ba
                 ; opcode $bb (illegal)
    LDY $6EE1,X  ; opcode $bc
    LDA $095C,X  ; opcode $bd
    LDX $98EB,Y  ; opcode $be
                 ; opcode $bf (illegal)
LABEL_13:
    CPY #$DE     ; opcode $c0
    CMP ($45,X)  ; opcode $c1
                 ; opcode $c2 (illegal)
                 ; opcode $c3 (illegal)
    CPY $71      ; opcode $c4
    CMP $E3      ; opcode $c5
    DEC $B5      ; opcode $c6
                 ; opcode $c7 (illegal)
    INY          ; opcode $c8
    CMP #$74     ; opcode $c9
    DEX          ; opcode $ca
                 ; opcode $cb (illegal)
    CPY $0E77    ; opcode $cc
    CMP $C1FF    ; opcode $cd
    DEC $12DD    ; opcode $ce
                 ; opcode $cf (illegal)
LABEL_14:
    BNE LABEL_14 ; opcode $d0
    CMP ($CA),Y  ; opcode $d1
                 ; opcode $d2 (illegal)
                 ; opcode $d3 (illegal)
                 ; opcode $d4 (illegal)
    CMP $41,X    ; opcode $d5
    DEC $81,X    ; opcode $d6
                 ; opcode $d7 (illegal)
    CLD          ; opcode $d8
    CMP $7063,Y  ; opcode $d9
                 ; opcode $da (illegal)
                 ; opcode $db (illegal)
                 ; opcode $dc (illegal)
    CMP $999A,X  ; opcode $dd
    DEC $55D2,X  ; opcode $de
                 ; opcode $df (illegal)
LABEL_15:
    CPX #$E5     ; opcode $e0
    SBC ($FD,X)  ; opcode $e1
                 ; opcode $e2 (illegal)
                 ; opcode $e3 (illegal)
    CPX $C9      ; opcode $e4
    SBC $70      ; opcode $e5
    INC $83      ; opcode $e6
                 ; opcode $e7 (illegal)
    INX          ; opcode $e8
    SBC #$C8     ; opcode $e9
    NOP          ; opcode $ea
                 ; opcode $eb (illegal)
    CPX $2EF5    ; opcode $ec
    SBC $56CE    ; opcode $ed
    INC $CF16    ; opcode $ee
                 ; opcode $ef (illegal)
LABEL_16:
    BEQ LABEL_16 ; opcode $f0
    SBC ($6E),Y  ; opcode $f1
                 ; opcode $f2 (illegal)
                 ; opcode $f3 (illegal)
                 ; opcode $f4 (illegal)
    SBC $DD,X    ; opcode $f5
    INC $B7,X    ; opcode $f6
                 ; opcode $f7 (illegal)
    SED          ; opcode $f8
    SBC $8429,Y  ; opcode $f9
                 ; opcode $fa (illegal)
                 ; opcode $fb (illegal)
                 ; opcode $fc (illegal)
    SBC $2BE1,X  ; opcode $fd
    INC $B023,X  ; opcode $fe
                 ; opcode $ff (illegal)
