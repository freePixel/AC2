#1.a) freq = 100Hz


#$t0 -> counter

.equ READ_CORE_TIMER , 11
.equ RESET_CORE_TIMER , 12 
.equ PUT_CHAR , 3
.equ PRINT_INT , 6


	 #200000		#100hz
		#2000000 	#10hz
.equ TICKS ,		4000000	#5hz
		#20000000	#1hz


.text

.globl main

main:
	li $t0 , 0
while:
	li $v0 , RESET_CORE_TIMER
	syscall

while1:
	li $v0 , READ_CORE_TIMER
	syscall




	bge $v0 , TICKS , ewhile1
	j while1
ewhile1:
	move $a0 , $t0
	li $a1 , 4
	sll $a1 , $a1 , 16
	ori $a1 , $a1 , 10
	li $v0 , PRINT_INT
	syscall
	addi $t0 , $t0 , 1

	li $a0 , '\r'
	li $v0 , PUT_CHAR
	syscall

	j while
	
	li $v0 , 0
	jr $ra
