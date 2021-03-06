.data


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


while:
	
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
	

	rem $v0 , $s2 , 10
	bne $v0 , 0 , eif1
	
	addi $s2 , $s2 , 1

eif1:
	rem $v0 , $s1 , 2
	bne $v0 , 0 , eif2
	
	addi $s1 , $s1 , 1	

eif2:
	
	addi $s2 , $s2 , 1

eif12:

	move $a0 , $s3
	jal timeDone



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
