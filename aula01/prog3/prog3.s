#$t0 , c

.equ IN_KEY , 1
.equ PUT_CHAR , 3


.data

.text
.globl main

main:
    do:
        li $v0 , IN_KEY
        syscall
        move $t0 , $v0      #c = inkey();

        beq $t0 , 0 , else
        #if:
            li $v0 , PUT_CHAR
            move $a0 , $t0
            syscall
            j endif         #putChar(c);

        else:
            li $v0 , PUT_CHAR
            li $a0 , '.'
            syscall         #putChar('.');
        endif:

            bne $t0 , 0 , do

        li $v0 , 0
        jr $ra              #return 0;