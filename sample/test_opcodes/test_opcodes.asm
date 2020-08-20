
    ; -------------------------------------- ;
    ;  this program is supposed to use all   ;
    ;       the official 6502 opcodes        ;
    ; -------------------------------------- ;

    ;* = $200 ; (un)comment if neccessary
    ;_main: ; (un)comment if neccessary
    ;.export _main ; (un)comment if neccessary

LABEL_01:
    BRK ???      ; opcode $00
    ORA ???      ; opcode $01
                 ; opcode $02 (illegal)
                 ; opcode $03 (illegal)
                 ; opcode $04 (illegal)
    ORA ???      ; opcode $05
    ASL ???      ; opcode $06
                 ; opcode $07 (illegal)
    PHP ???      ; opcode $08
    ORA ???      ; opcode $09
    ASL ???      ; opcode $0a
                 ; opcode $0b (illegal)
                 ; opcode $0c (illegal)
    ORA ???      ; opcode $0d
    ASL ???      ; opcode $0e
                 ; opcode $0f (illegal)
LABEL_02:
    BPL ???      ; opcode $10
    ORA ???      ; opcode $11
                 ; opcode $12 (illegal)
                 ; opcode $13 (illegal)
                 ; opcode $14 (illegal)
    ORA ???      ; opcode $15
    ASL ???      ; opcode $16
                 ; opcode $17 (illegal)
    CLC ???      ; opcode $18
    ORA ???      ; opcode $19
                 ; opcode $1a (illegal)
                 ; opcode $1b (illegal)
                 ; opcode $1c (illegal)
    ORA ???      ; opcode $1d
    ASL ???      ; opcode $1e
                 ; opcode $1f (illegal)
LABEL_03:
    JSR ???      ; opcode $20
    AND ???      ; opcode $21
                 ; opcode $22 (illegal)
                 ; opcode $23 (illegal)
    BIT ???      ; opcode $24
    AND ???      ; opcode $25
    ROL ???      ; opcode $26
                 ; opcode $27 (illegal)
    PLP ???      ; opcode $28
    AND ???      ; opcode $29
    ROL ???      ; opcode $2a
                 ; opcode $2b (illegal)
    BIT ???      ; opcode $2c
    AND ???      ; opcode $2d
    ROL ???      ; opcode $2e
                 ; opcode $2f (illegal)
LABEL_04:
    BMI ???      ; opcode $30
    AND ???      ; opcode $31
                 ; opcode $32 (illegal)
                 ; opcode $33 (illegal)
                 ; opcode $34 (illegal)
    AND ???      ; opcode $35
    ROL ???      ; opcode $36
                 ; opcode $37 (illegal)
    SEC ???      ; opcode $38
    AND ???      ; opcode $39
                 ; opcode $3a (illegal)
                 ; opcode $3b (illegal)
                 ; opcode $3c (illegal)
    ORA ???      ; opcode $3d
    ASL ???      ; opcode $3e
                 ; opcode $3f (illegal)
LABEL_05:
    RTI ???      ; opcode $40
    EOR ???      ; opcode $41
                 ; opcode $42 (illegal)
                 ; opcode $43 (illegal)
                 ; opcode $44 (illegal)
    EOR ???      ; opcode $45
    LSR ???      ; opcode $46
                 ; opcode $47 (illegal)
    PHA ???      ; opcode $48
    EOR ???      ; opcode $49
    LSR ???      ; opcode $4a
                 ; opcode $4b (illegal)
    JMP ???      ; opcode $4c
    EOR ???      ; opcode $4d
    LSR ???      ; opcode $4e
                 ; opcode $4f (illegal)
LABEL_06:
    BVC ???      ; opcode $50
    EOR ???      ; opcode $51
                 ; opcode $52 (illegal)
                 ; opcode $53 (illegal)
                 ; opcode $54 (illegal)
    EOR ???      ; opcode $55
    LSR ???      ; opcode $56
                 ; opcode $57 (illegal)
    CLI ???      ; opcode $58
    EOR ???      ; opcode $59
                 ; opcode $5a (illegal)
                 ; opcode $5b (illegal)
                 ; opcode $5c (illegal)
    EOR ???      ; opcode $5d
    LSR ???      ; opcode $5e
                 ; opcode $5f (illegal)
LABEL_07:
    RTS ???      ; opcode $60
    ADC ???      ; opcode $61
                 ; opcode $62 (illegal)
                 ; opcode $63 (illegal)
                 ; opcode $64 (illegal)
    ADC ???      ; opcode $65
    ROR ???      ; opcode $66
                 ; opcode $67 (illegal)
    PLA ???      ; opcode $68
    ADC ???      ; opcode $69
    ROR ???      ; opcode $6a
                 ; opcode $6b (illegal)
    JMP ???      ; opcode $6c
    ADC ???      ; opcode $6d
    ROR ???      ; opcode $6e
                 ; opcode $6f (illegal)
LABEL_08:
    BCS ???      ; opcode $70
    ADC ???      ; opcode $71
                 ; opcode $72 (illegal)
                 ; opcode $73 (illegal)
                 ; opcode $74 (illegal)
    ADC ???      ; opcode $75
    ROR ???      ; opcode $76
                 ; opcode $77 (illegal)
    SEI ???      ; opcode $78
    ADC ???      ; opcode $79
                 ; opcode $7a (illegal)
                 ; opcode $7b (illegal)
                 ; opcode $7c (illegal)
    ADC ???      ; opcode $7d
    ROR ???      ; opcode $7e
                 ; opcode $7f (illegal)
LABEL_09:
                 ; opcode $80 (illegal)
    STA ???      ; opcode $81
                 ; opcode $82 (illegal)
                 ; opcode $83 (illegal)
    STY ???      ; opcode $84
    STA ???      ; opcode $85
    STX ???      ; opcode $86
                 ; opcode $87 (illegal)
    DEY ???      ; opcode $88
                 ; opcode $89 (illegal)
    TXA ???      ; opcode $8a
                 ; opcode $8b (illegal)
    STY ???      ; opcode $8c
    STA ???      ; opcode $8d
    STX ???      ; opcode $8e
                 ; opcode $8f (illegal)
LABEL_10:
    BCC ???      ; opcode $90
    STA ???      ; opcode $91
                 ; opcode $92 (illegal)
                 ; opcode $93 (illegal)
    STY ???      ; opcode $94
    STA ???      ; opcode $95
    STX ???      ; opcode $96
                 ; opcode $97 (illegal)
    TYA ???      ; opcode $98
    STA ???      ; opcode $99
    TXS ???      ; opcode $9a
                 ; opcode $9b (illegal)
                 ; opcode $9c (illegal)
    STA ???      ; opcode $9d
                 ; opcode $9e (illegal)
                 ; opcode $9f (illegal)
LABEL_11:
    LDY ???      ; opcode $a0
    LDA ???      ; opcode $a1
    LDX ???      ; opcode $a2
                 ; opcode $a3 (illegal)
    LDY ???      ; opcode $a4
    LDA ???      ; opcode $a5
    LDX ???      ; opcode $a6
                 ; opcode $a7 (illegal)
    TAY ???      ; opcode $a8
    LDA ???      ; opcode $a9
    TAX ???      ; opcode $aa
                 ; opcode $ab (illegal)
    LDY ???      ; opcode $ac
    LDA ???      ; opcode $ad
    LDX ???      ; opcode $ae
                 ; opcode $af (illegal)
LABEL_12:
    BCS ???      ; opcode $b0
    LDA ???      ; opcode $b1
                 ; opcode $b2 (illegal)
                 ; opcode $b3 (illegal)
    LDY ???      ; opcode $b4
    LDA ???      ; opcode $b5
    LDX ???      ; opcode $b6
                 ; opcode $b7 (illegal)
    CLV ???      ; opcode $b8
    LDA ???      ; opcode $b9
    TSX ???      ; opcode $ba
                 ; opcode $bb (illegal)
    LDY ???      ; opcode $bc
    LDA ???      ; opcode $bd
    LDX ???      ; opcode $be
                 ; opcode $bf (illegal)
LABEL_13:
    CPY ???      ; opcode $c0
    CMP ???      ; opcode $c1
                 ; opcode $c2 (illegal)
                 ; opcode $c3 (illegal)
    CPY ???      ; opcode $c4
    CMP ???      ; opcode $c5
    DEC ???      ; opcode $c6
                 ; opcode $c7 (illegal)
    INY ???      ; opcode $c8
    CMP ???      ; opcode $c9
    DEX ???      ; opcode $ca
                 ; opcode $cb (illegal)
    CPY ???      ; opcode $cc
    CMP ???      ; opcode $cd
    DEC ???      ; opcode $ce
                 ; opcode $cf (illegal)
LABEL_14:
    BNE ???      ; opcode $d0
    CMP ???      ; opcode $d1
                 ; opcode $d2 (illegal)
                 ; opcode $d3 (illegal)
                 ; opcode $d4 (illegal)
    CMP ???      ; opcode $d5
    DEC ???      ; opcode $d6
                 ; opcode $d7 (illegal)
    CLD ???      ; opcode $d8
    CMP ???      ; opcode $d9
                 ; opcode $da (illegal)
                 ; opcode $db (illegal)
                 ; opcode $dc (illegal)
    CMP ???      ; opcode $dd
    DEC ???      ; opcode $de
                 ; opcode $df (illegal)
LABEL_15:
    CPX ???      ; opcode $e0
    SBC ???      ; opcode $e1
                 ; opcode $e2 (illegal)
                 ; opcode $e3 (illegal)
    CPX ???      ; opcode $e4
    SBC ???      ; opcode $e5
    INC ???      ; opcode $e6
                 ; opcode $e7 (illegal)
    INX ???      ; opcode $e8
    SBC ???      ; opcode $e9
    NOP ???      ; opcode $ea
                 ; opcode $eb (illegal)
    CPX ???      ; opcode $ec
    SBC ???      ; opcode $ed
    INC ???      ; opcode $ee
                 ; opcode $ef (illegal)
LABEL_16:
    BEQ ???      ; opcode $f0
    SBC ???      ; opcode $f1
                 ; opcode $f2 (illegal)
                 ; opcode $f3 (illegal)
                 ; opcode $f4 (illegal)
    SBC ???      ; opcode $f5
    INC ???      ; opcode $f6
                 ; opcode $f7 (illegal)
    SED ???      ; opcode $f8
    SBC ???      ; opcode $f9
                 ; opcode $fa (illegal)
                 ; opcode $fb (illegal)
                 ; opcode $fc (illegal)
    SBC ???      ; opcode $fd
    INC ???      ; opcode $fe
                 ; opcode $ff (illegal)
