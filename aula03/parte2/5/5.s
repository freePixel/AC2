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
#$s0 -> contador
main:
    
    li $t0 , SFR_BASE_HI
    lw $t1 , TRISE($t0)
    andi $t1 , $t1 , 0xfff0
    sw $t1 , TRISE($t0)         #RE[0..4] OUTPUTS

    lw $t1 , TRISB($t0)
    ori $t1 , $t1 , 0x000f
    sw $t1 , TRISB($t0)        #RB[0..4] INPUTS

while:                          #{

    
    li $t0 , SFR_BASE_HI
    lw $t1 , LATE($t0)
    andi $t1 , $t1 , 0xfff0
    andi $s0 , $s0 , 0x000f     #evita a escrita em RB4+ e impede o contador de ultrapassar 0xf
    or $t1 , $t1 , $s0
    sw $t1 , LATE($t0)          #write counter



    sll $s0 , $s0 , 1


    srl $v0 , $s0 , 3
    andi $v0 , $v0 , 0x0001
    xori $v0 , $v0 , 0x0001     #negar bit
    or $s0 , $s0 , $v0          #merge



    li $v0 , 667
    jal delay                   #delay(667) ~1.5hZ;

    j while                     #}


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
                

