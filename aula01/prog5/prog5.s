.equ UP , 1
.equ DOWN , 0

.equ PRINT_STR , 8
.equ PRINT_INT , 6
.equ PRINT_INT10 , 7
.equ READ_INT10 , 5
.equ IN_KEY , 1
.equ PUT_CHAR , 3

#$s0 , state
#$s1 , cnt
#$s2 , c

.data

.text
.globl main

main:

    addiu $sp , $sp, -16
    sw $ra , 0($sp)
    sw $s0 , 4($sp)
    sw $s1 , 8($sp)
    sw $s2 , 12($sp)

    li $s0 , 0      #int state = 0;
    li $s1 , 0      #int cnt = 0;

    do:   
        li $v0 , PUT_CHAR
        li $a0 , '\r'
        syscall

        li $v0 , PRINT_INT
        move $a0 , $s1
        li $a1 , 3
        sll $a1 , $a1 , 16
        ori $a1 , $a1 , 10
        syscall

        li $v0 , PUT_CHAR
        li $a0 , '\t'
        syscall

        li $v0 , PRINT_INT
        move $a0 , $s1
        li $a1 , 8
        sll $a1 , $a1 , 16
        ori $a1 , $a1 , 2
        syscall

        li $a0 , 5
        jal wait

        li $v0 , IN_KEY
        syscall
        move $s2 , $v0


        bne $s2 , '+' , endif1

        li $s0 , UP

        endif1:
        bne $s2 , '-' , endif2

        li $s0 , DOWN

        endif2:

        bne $s0 , UP , else3

        addi $s1 , $s1 , 1
        andi $s1 , $s1 , 0xff
        
        j endif3
        else3:

        addi $s1 , $s1 , -1
        andi $s1 , $s1 , 0xff

        endif3:

        bne $s2 , 'q' , do 


    li $v0 , 0

    lw $ra , 0($sp)
    lw $s0 , 4($sp)
    lw $s1 , 8($sp)
    lw $s2 ,12($sp)

   
    jr $ra     

wait:
    li $t0 , 0
    wait_for:
        mul $a1 , $a0 , 5
        bge $t0 , $a1 , wait_efor
        addi $t0 , $t0 , 1
        j wait_for
    wait_efor:
        jr $ra