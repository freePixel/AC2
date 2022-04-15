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

.equ PUT_CHAR  , 3
.equ PRINT_INT , 6
.equ PRINT_INT10 , 7
.equ READ_CORE_TIMER , 11
.equ RESET_CORE_TIMER , 12
.equ IN_KEY , 1
.equ PRINT_STR , 8

STR1:   .asciiz "DS4="
STR2:   .asciiz "DS3="
STR3:   .asciiz "DS2="
STR4:   .asciiz "DS1="
STR5:   .asciiz ", "

.text

.globl main

main:
    lui $t0 , SFR_BASE_HI
    lw $t1 , TRISB($t0)
    ori $t1 , $t1 , 0x000f
    sw $t1 , TRISB($t0)     #TRISB |= 0x000f;

while:

    la $a0 , STR1
    li $v0 , PRINT_STR
    syscall              
    lw $a0 , PORTB($t0)
    andi $a0 , $a0 , 0x0008
    srl $a0 , $a0 , 3
    addi $a0 , $a0 , 48
    li $v0 , PUT_CHAR
    syscall
    la $a0 , STR5
    li $v0 , PRINT_STR
    syscall

    la $a0 , STR1
    li $v0 , PRINT_STR
    syscall              
    lw $a0 , PORTB($t0)
    andi $a0 , $a0 , 0x0004
    srl $a0 , $a0 , 2
    addi $a0 , $a0 , 48
    li $v0 , PUT_CHAR
    syscall
    la $a0 , STR5
    li $v0 , PRINT_STR
    syscall

    la $a0 , STR1
    li $v0 , PRINT_STR
    syscall              
    lw $a0 , PORTB($t0)
    andi $a0 , $a0 , 0x0002
    srl $a0 , $a0 , 1
    addi $a0 , $a0 , 48
    li $v0 , PUT_CHAR
    syscall
    la $a0 , STR5
    li $v0 , PRINT_STR
    syscall

    la $a0 , STR1
    li $v0 , PRINT_STR
    syscall              
    lw $a0 , PORTB($t0)
    andi $a0 , $a0 , 0x0001
    addi $a0 , $a0 , 48
    li $v0 , PUT_CHAR
    syscall
    la $a0 , STR5
    li $v0 , PRINT_STR
    syscall


    li $v0 , PUT_CHAR
    li $a0 , '\n'
    syscall

    li $v0 , RESET_CORE_TIMER
    syscall

while1:
    li $v0 , READ_CORE_TIMER
    syscall
    blt $v0 , 20000000 , while1

    j while

    j $ra
