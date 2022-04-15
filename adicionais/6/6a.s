


.data

.equ PUT_CHAR , 3
.equ PRINT_INT , 6
.equ READ_CORE_TIMER , 11
.equ RESET_CORE_TIMER , 12

.text

.globl main
main:                               #int main(void)#{
    
    addiu $sp , $sp , -8
    sw $ra , 0($sp)
    sw $s0 , 4($sp)

    li $s0 , 0                  #int counter = 0;

while:                              #while(1){
    
    li $v0 , PRINT_INT
    move $a0 , $s0
    li $a1 , 2
    sll $a1 , $a1 , 16
    ori $a1 , $a1 , 10
    syscall                         #printInt(counter , 10 | (2 << 16));


    li $v0 , PUT_CHAR
    li $a0 , '\r'
    syscall                         #putChar('\r');

    addi $s0 , $s0 , 1              #counter = (counter + 1 ) % 100;
    rem $s0 , $s0 , 100

    li $a0 , 100                    #delay(100);
    jal delay

    j while                         #}

    lw $ra ,0($sp)
    lw $s0 ,4($sp)

    jr $ra                          #return 0;

                                    #}




delay:                              #void delay(unsigned int ms){
    li $v0 , RESET_CORE_TIMER
    syscall                         #resetCoreTimer();

delay_while:
    li $v0 , READ_CORE_TIMER
    mul $t0 , $a0 ,  20000
    syscall
    blt $v0 , $t0 , delay_while     #while(readCoreTimer() < 20000 * ms);


    jr $ra                          #}



