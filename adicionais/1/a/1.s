.data

#I/O
.equ SFR_BASE_HI , 0xBF88

.equ TRISB , 0x6040
.equ PORTB  , 0x6050
.equ LATB   , 0x6060

.equ TRISC  , 0x6080
.equ PORTC  , 0x6090
.equ LATC   , 0x60a0

.equ TRISD  , 0x60c0
.equ PORTD  , 0x60d0
.equ LATD   , 0x60e0

.equ TRISE  , 0x6100
.equ PORTE  , 0x6110
.equ LATE   , 0x6120



.text

.globl main

main:
    lui $t0 , SFR_BASE_HI

    lw $t1 , TRISB($t0)
    ori $t1 , $t1 , 0x000f
    sw $t1 , TRISB($t0)

    lw $t1 , TRISE($t0)
    andi $t1 , $t1 , 0xfff0
    sw $t1 , TRISE($t0)

while:

    lw $t1 , PORTB($t0)
    andi $t1 , $t1 , 0x000f
    lw $t2 , LATE($t0)
    andi $t2 , $t2 ,0xfff0
    or $t2 , $t2 , $t1
    sw $t2 , LATE($t0)

    j while

    jr $ra
