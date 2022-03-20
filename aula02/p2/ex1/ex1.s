.equ PUT_CHAR , 3
.equ PRINT_INT , 6
.equ READ_CORE_TIMER , 11
.equ RESET_CORE_TIMER , 12
.equ IN_KEY , 1



.data



.text
.globl main
#$s0 cnt1
#$s1 cnt5
#$s2 cnt10
#$s3 delay_time

main:
	addiu $sp , $sp , -20
	sw $ra , 0($sp)
	sw $s0 , 4($sp)
	sw $s1 , 8($sp)
	sw $s2 ,12($sp)
	sw $s3 ,16($sp)

	li $s0 , 0
	li $s1 , 0
	li $s2 , 0
	li $s3 , 100

while:

	li $v0 , IN_KEY
	syscall
	
	bne $v0 , 'A' , endif1
	
	li $s3 , 200
	
endif1:
	bne $v0 , 'N' , endif2
	
	li $s3 , 100
		

endif2:
	rem $a0 , $s2 , 10
	bne $a0 , 0 , endif3

	add $s0 , $s0 , 1

endif3:
	rem $a0 , $s2 , 2
	bne $a0 , 0 , endif4

	add $s1 , $s1 , 1

endif4:

	add $s2 , $s2 , 1

	li $a0 , '\r'
	li $v0 , PUT_CHAR
	syscall

	move $a0 , $s2
	li $a1 , 5
	sll $a1 , $a1 , 16
	ori $a1 , $a1 , 10
	li $v0 , PRINT_INT
	syscall

	li $a0 , ' '
	li $v0 , PUT_CHAR
	syscall

	move $a0 , $s1
	li $a1 , 5
	sll $a1 , $a1 , 16
	ori $a1 , $a1 , 10
	li $v0 , PRINT_INT
	syscall

	li $a0 , ' '
	li $v0 , PUT_CHAR
	syscall

	move $a0 , $s0
	li $a1 , 5
	sll $a1 , $a1 , 16
	ori $a1 , $a1 , 10
	li $v0 , PRINT_INT
	syscall

	li $a0 , 100
	jal delay
	
	j while

	
	li $v0 , 0

	lw $ra , 0($sp)
	lw $s0 , 4($sp)
	lw $s1 , 8($sp)
	lw $s2 ,12($sp)

	jr $ra	



delay:
	li $v0 , RESET_CORE_TIMER
	syscall

delay_while:
	li $v0 , READ_CORE_TIMER
	syscall
	li $v1 , 20000
	mul $v1 , $v1 , $a0
	bge $v0 , $v1 , delay_ewhile	

	j delay_while
delay_ewhile:
	jr $ra
