#$t0 -> c

.equ GET_CHAR , 2
.equ PUT_CHAR , 3

.data

.text
.globl main

main:  

    do:                     #do{
        li $v0 , GET_CHAR
        syscall
        move $t0 , $v0      #c = getChar();

        li $v0 , PUT_CHAR
        add $a0 , $t0 , 1
        syscall             #putChar(c+1);

        bne $t0 , 0 , do #} while(c != '\n');

    li $v0 , 0
    jr $ra                  #return 0;
