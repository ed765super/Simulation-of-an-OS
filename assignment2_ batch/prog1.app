var memory 10
addi $t1 $t0 10
la $t2 memory
take_input: 
in $a0 
sw $a0 0x0($t2)
addi $t2 $t2 8 
addi $t1 $t1 -1
bgt $t1 $t0 take_input
addi $t1 $t0 9 
la $t2 memory 
addi $a0 $t2 8
sort: lw $a1 0x0($t2)
lw $a2 0x0($a0)
bgt $a2 $a1 y_greater
sw $a1 0x0($a0)
sw $a2 0x0($t2)
y_greater: addi $t2 $t2 8 
addi $a0 $a0 8
addi $t1 $t1 -1
beq $t1 $t0 done
beq $t0 $t0 sort
done: nand $v0 $zero $zero
halt