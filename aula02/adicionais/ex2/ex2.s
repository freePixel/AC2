.data


.equ FORMAT , 0x0005000a
.equ READ_CORE_TIMER , 11
.equ RESET_CORE_TIMER , 12
.equ PUT_CHAR , 3
.equ PRINT_INT , 6
.equ IN_KEY , 1
.equ RUN , 0
.equ STOP , 1

.equ K , 20000

.text

.globl main

main:

	addiu $sp , $sp , -24
	sw $ra , 0($sp)
	sw $s0 , 4($sp)
	sw $s1 , 8($sp)
	sw $s2 , 12($sp)
	sw $s3 , 16($sp)
	sw $s4 , 20($sp)
	
	li $s0 , 0
	li $s1 , 0
	li $s2 , 0

	li $s3 , 100

	li $s5 , 0
while:
	
	move $a0 , $s3
	li $a1 , 0
	jal timeDone
	ble $v0 , 0 , eif_last

	add $s5 , $s5 , $s3
	rem $v0 , $s5 , 1000
	bne $v0 , 0 , eif_x

	li $a0 , '\n'
	li $v0 , PUT_CHAR
	syscall

eif_x:

	
	
	li $a0 , 0
	li $a1 , 1
	jal timeDone


	li $v0 , IN_KEY
	syscall

	bne $v0 , 'A' , eif8

	li $s3 , 50

eif8:

	bne $v0 , 'N' , eif9

	li $s3 , 100

eif9:

	bne $v0 , 'S' , eif10

	li $s4, STOP

eif10:
	
	bne $v0 , 'R' , eif11

	li $s4, RUN

eif11:

	bne $s4 , RUN , eif12
	

	addi $s2 , $s2 , 1

	rem $v0 , $s2 , 10
	bne $v0 , 0 , eif1
	
	addi $s0 , $s0 , 1

eif1:
	rem $v0 , $s2 , 2
	bne $v0 , 0 , eif2
	
	addi $s1 , $s1 , 1	

eif2:
	

eif12:

	
	


	li $a0 , '\r'
	li $v0 , PUT_CHAR
	syscall			#putChar('\r');

	move $a0 , $s2
	li $a1 , FORMAT
	li $v0 , PRINT_INT
	syscall			#printInt(cnt10,10|5<<16);
	li $a0 , ' '
	li $v0 , PUT_CHAR
	syscall			#putChar(' ');

	move $a0 , $s1
	li $a1 , FORMAT
	li $v0 , PRINT_INT
	syscall			#printInt(cnt5 , 10|5<<16);
	
	li $a0 , ' '
	li $v0 , PUT_CHAR
	syscall			#putChar(' ');

	move $a0 , $s0
	li $a1 , FORMAT
	li $v0 , PRINT_INT
	syscall			#printInt(cnt1,10|5<<16);

	

eif_last:

	j while

	lw $ra , 0 ($sp)
	lw $s0 , 4($sp)
	lw $s1 , 8($sp)
	lw $s2 , 12($sp)	
	lw $s3 , 16($sp)
	lw $s4 , 20($sp)
	addiu $sp , $sp , 24

	li $v0 , 0
	jr $ra


#$t0 curCount
#$t1 retValue
timeDone:
	li $t1 , 0	#unsigned int retValue = 0;


	ble $a1 , 0 , td_else
	
	li $v0 , RESET_CORE_TIMER
	syscall

	j td_endif
td_else:
	li $v0 , READ_CORE_TIMER
	syscall
	move $t0 , $v0
	
	mul $v0 , $a0 , K
	ble $t0 , $v0 , td_endif1

	div $t1 , $t0 , K

td_endif1:

td_endif:

	move $v0 , $t1

	jr $ra
