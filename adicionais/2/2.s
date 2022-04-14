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

    lw $t1 , TRISE($t0)
    andi $t1 , $t1 , 0xfff0
    sw $t1 , TRISE($t0)

while:


    li $v0 , 1
	syscall

	lw $t1 , LATE($t0)
	andi $t1 , $t1 , 0xfff0

	bne $v0 , '0' , eif1

	ori $t1 , $t1 , 0x0001
	j end

eif1:

	bne $v0 , '1' , eif2

	ori $t1 , $t1 , 0x0002
	j end
	
eif2:

	bne $v0 , '2' , eif3

	ori $t1 , $t1 , 0x0004
	j end

eif3:

	bne $v0 , '3' , eif4

	ori $t1 , $t1 , 0x0008
	j end

eif4:

    bne $v0 , 0 , eif5

    #andi $t1 , $t1 , 0xfff0
	#sw $t1 , LATE($t0)
	j while


eif5: #default case

	ori $t1 , 0x000f
	sw $t1 , LATE($t0)

	li $v0 , 12
	syscall

while2:
	li $v0 , 11
	syscall

	blt $v0 , 20000000 , while2

	andi $t1 , $t1 , 0xfff0
	sw $t1 , LATE($t0)
	j while
	

end:


	sw $t1 , LATE($t0)

    j while

    jr $ra
