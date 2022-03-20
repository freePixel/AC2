#SYSCALLS
.equ IN_KEY		, 1
.equ GET_CHAR		, 2
.equ PUT_CHAR		, 3
.equ READ_INT		, 4
.equ READ_INT10		, 5
.equ PRINT_INT		, 6
.equ PRINT_INT10	, 7
.equ PRINT_STR		, 8
.equ READ_STR		, 9
.equ EXIT		, 10
.equ READ_CORE_TIMER	, 11
.equ RESET_CORE_TIMER  	, 12


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


.data

.text

.globl main


#$s1 , v

main:
	
	addiu $sp , $sp , -8
	sw $ra , 0($sp)
	sw $s0 , 4($sp)

	li $s0 , 0 							#int v = 0;

	lui $t0 , SFR_BASE_HI
	lw $t1  , TRISE($t0)
	andi $t1 , $t1 , 0xfffe
	sw $t1 , TRISE($t0)					#TRISE0 = 0

while:									#while(1){

	lui $t0 , SFR_BASE_HI
	lw $t1 , LATE($t0)
	andi $t1 , $t1 , 0xfffe			

	move $t2 , $s0
	andi $t2 , $t2 , 0x0001				#(OPCIONAL, IMPEDE A ESCRITA EM LATE EM POSIÇÕES DIFERENTES DE 0)

	or $t1 , $t1 , $t2					#merge

	sw $t1 , LATE($t0)					#LATE0 = v;

	li $a0 , 500
	jal delay 							#delay(500);

	xori $s0 , $s0 , 0x0001 			# v ^= 1;

	j while 							#}

	lw $ra , 0($sp)
	lw $s0 , 4($sp)

	jr $ra   							#}

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
                

