.equ SIZE , 20
.equ PRINT_STR , 8
.equ PRINT_INT , 6
.equ PRINT_INT10 , 7
.equ READ_INT10 , 5
.equ IN_KEY , 1
.equ PUT_CHAR , 3
.equ READ_STR , 9

.data

.align 2
str1:   .space SIZE+1
str2:   .space SIZE+1
str3:   .space 2*SIZE+1
str_tex1:   .asciiz "Introduza 2 strings: "
str_tex2:   .asciiz "Resultados:\n"

.text

.globl main

main:

    addiu $sp , $sp , -4
    sw $ra , 0($sp)

    li $v0 , PRINT_STR
    la $a0 , str_tex1
    syscall             #printStr("Introduza 2 strings: ");

    la $a0 , str1
    li $a1 , SIZE
    li $v0 , READ_STR
    syscall             # readStr( str1, SIZE );

    la $a0 , str2
    li $a1 , SIZE
    li $v0 , READ_STR
    syscall             # readStr( str2, SIZE ); 

    la $a0 , str_tex2
    li $v0 , PRINT_STR
    syscall             #printStr("Resultados:\n");

    li $a0 , (SIZE+1)
    li $a1 , 10
    li $v0 , PRINT_INT  
    syscall             #printInt(strlen(str1) , 10);

    li $a0 , (SIZE+1)
    li $a1 , 10
    li $v0 , PRINT_INT
    syscall             #printInt(strlen(str2) , 10);

    la $a0 , str3
    la $a1 , str2
    jal strcpy          #strcpy(str3 , str1);

    la $a0 , str3
    la $a1 , str2
    jal strcat
    move $a0 , $v0
    li $v0 , PRINT_STR
    syscall             #printStr(strcat(str3 , str2));

    la $a0 , str1
    la $a1 , str2
    jal strcmp
    move $a0 , $v0
    li $v0 , PRINT_INT10
    syscall             #printInt10(strcmp(str1 , str2));

    lw $ra , 0($sp)
    addiu $sp , $sp , 4

    li $v0 , 0
    jr $ra                 #return 0;




strlen:

    li $t0 , 0
    strlen_for:
        lb $t1 , 0($a0)
        beq $t1 , 0 , strlen_efor
        addi $t0 , $t0 , 1
        addiu $a0 , $a0 , 1
        j strlen_for
    strlen_efor:
    move $v0 , $t0
    jr $ra


strcpy:
    move $v0 , $a0
    strcpy_for:
    lb $t2 , 0($a0)
    lb $t3 , 0($a1)
    bne $t2 , $t3 , strcpy_efor
    addiu $a0 , $a0 , 1
    addiu $a1 , $a1 , 1
    j strcpy_for
    strcpy_efor:

    jr $ra              #return p;


strcat:

    addiu $sp , $sp , -16
    sw $ra , 0($sp)
    sw $s0 , 4($sp)
    sw $s1 , 8($sp)
    sw $s2 , 12($sp)

    move $s0 , $a0
    move $s1 , $a1
    move $s2 , $s0

    strcat_for:
        lb $v0 , 0($s0)
        beq $v0 , 0 , strcat_efor
        addiu $s1 , $s1 , 1
        j strcat_for
    strcat_efor:

    move $a0 , $s0
    move $a1 , $s1
    jal strcpy

    move $v0 , $s0

    lw $ra , 0($sp)
    lw $s0 , 4($sp)
    lw $s1 , 8($sp)
    lw $s2 , 12($sp)

    addiu $sp , $sp , 16
    jr $ra



strcmp:
    strcmp_for:
        lb $t0 , 0($a0)
        lb $t1 , 0($a1)
        bne $t0 , $t1 , strcmp_efor

        beq $t0 , 0 , strcmp_efor

        addiu $a0 , $a0 , 1
        addiu $a1 , $a1 , 1
        j strcmp_for
    strcmp_efor:

    lb $t0 , 0($a0)
    lb $t1 , 0($a1)
    sub $v0 , $t0 , $t1
    jr $ra
