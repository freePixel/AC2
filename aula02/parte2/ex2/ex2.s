.data

.equ FORMAT , 0x0005000a
.equ READ_CORE_TIMER , 11
.equ RESET_CORE_TIMER , 12
.equ PUT_CHAR , 3
.equ PRINT_INT , 6

.text

.globl main
#$s0 -> cnt1
#$s1 -> cnt5
#$s2 -> cnt10

main:

	addiu $sp , $sp , -16
	sw $ra , 0($sp)
	sw $s0 , 4($sp)
	sw $s1 , 8($sp)
	sw $s2 , 12($sp)
	
	li $s0 , 0
	li $s1 , 0
	li $s2 , 0
while:

	addi $s2 , $s2 , 1

	


	rem $v0 , $s2 , 10
	bne $v0 , 0 , eif1
	
	addi $s0 , $s0 , 1

eif1:
	rem $v0 , $s2 , 2
	bne $v0 , 0 , eif2
	
	addi $s1 , $s1 , 1	

eif2:
	


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


	
	
	li $a0 , 100
	jal delay


	j while

	lw $ra , 0 ($sp)
	lw $s0 , 4($sp)
	lw $s1 , 8($sp)
	lw $s2 , 12($sp)	




delay:
    li $v0 , RESET_CORE_TIMER
    syscall
    delay_while:
    li $v0 , READ_CORE_TIMER
    syscall
    mul $v1 , $a0 , 20000
    bge $v0 , $v1 , delay_ewhile
    j delay_while
    delay_ewhile:
    jr $ra
                
