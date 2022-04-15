.data

.equ PUT_CHAR  , 3
.equ PRINT_INT , 6
.equ PRINT_INT10 , 7
.equ READ_CORE_TIMER , 11
.equ RESET_CORE_TIMER , 12
.equ IN_KEY , 1
.equ PRINT_STR , 8

STR1:     .asciiz ", "
STR2:     .asciiz " Hz"
STR3:     .asciiz "                 "

.text

.globl main

main:                   #int main(void){

    addiu $sp , $sp , -20
    sw $ra , 0($sp)
    sw $s0 , 4($sp)
    sw $s1 , 8($sp)
    sw $s2 , 12($sp)
    sw $s3 , 16($sp)

    li $s0 , 0          #int counter = 0;

    li $s1 , '\0'       #char key = '\0';

    li $s2 , 2          #int freq = 2;

    li $s3 , 0       #int flag = 0;

while:                  #while(1){

    li $s3 , 0          #flag = 0;

    li $v0 , IN_KEY
    syscall
    move $s1 , $v0      #key = inkey();

    blt $s1 , '0' , eif1
    bgt $s1 , '4' , eif1        #if(key >= '0' && key <= '4'){

    sub  $s2 , $s1 , 48
    addi $s2,  $s2,   1
    mul  $s2 , $s2 ,  2 #freq = 2* (1+(key-48));}

eif1:

    bne $s1 , 10 , eif2     #if(key == \'x0a){

    li $s3 , 1          #flag = 1;}

eif2:

    move $a0 , $s0
    li $a1 , 2
    sll $a1 , $a1 , 16
    ori $a1 , $a1 , 10
    li $v0 , PRINT_INT
    syscall             #printInt(counter , 10 | (2 << 16));

    beq $s3 , 0 , eif3

    li $v0 , PRINT_STR
    la $a0 , STR1
    syscall

    li $v0 , PRINT_INT10
    move $a0 , $s2
    syscall

    li $v0 , PRINT_STR
    la $a0 , STR2
    syscall

eif3:

    li $v0 , PUT_CHAR
    li $a0 , '\r'
    syscall                 #putChar('\r');

    addi $s0 , $s0 , 1
    rem $s0 , $s0 , 100     #counter = (counter + 1) % 100;

    li $v0 , 1000
    div $a0 , $v0 , $s2
    jal delay

    li $v0, PRINT_STR
    la $a0 , STR3
    syscall

    li $v0 , PUT_CHAR
    li $a0 , '\r'
    syscall                 #putChar('\r');

    j while             #}


    lw $ra , 0($sp)
    lw $s0 , 4($sp)
    lw $s1 , 8($sp)
    lw $s2 , 12($sp)
    lw $s3 , 16($sp)
    addiu $sp , $sp , 20


delay:      #void delay(unsigned int ms){

    li $v0 , RESET_CORE_TIMER
    syscall                         #resetCoreTimer();
    mul $t0 , $a0 , 20000

delay_while:
    li $v0 , READ_CORE_TIMER        #while(readCoreTimer() < 20000 * ms);
    syscall
    blt $v0 , $t0 , delay_while     

    jr $ra                         #}
