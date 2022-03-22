# t = k * ms
# if k * ms = 20000000 -> delay = 1000ms => k * ms = 20000 -> delay de 1ms
# k = 20000 / 1 = 20000
# max = 2 ^ 32 ticks -> (2^32 / 20 000 000) segundos = (2^32 / 20 000 000) * (1000) ms

.equ READ_CORE_TIMER , 11
.equ RESET_CORE_TIMER , 12 
.equ PUT_CHAR , 3
.equ PRINT_INT , 6

.data


.text
.globl main
main:
	li $t0 , 0
while:
	li $v0 , RESET_CORE_TIMER
	syscall

    li $a0 , 1000
    jal delay

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
