GCD recursive

in $a0
in $a1
check: bgt $a0 $a1 xbigger
bgt $a1 $a0 ybigger
out $a0
halt
xbigger sw $ra 0x0($sp)
addi $sp $sp -4
sw $a1 0x4 ($sp)
sw $a0 0x8 ($sp)
addi $sp $sp 8
la $t0 gcd_one
jalr $t0 $ra
addi $sp $sp 4
lw $a0 0x8($sp)
lw $a1 0x4($sp)
beq $ra $ra check
ybigger sw $ra 0x0($sp)
addi $sp $sp -4
sw $a1 0x4 ($sp)
sw $a0 0x8 ($sp)
addi $sp $sp 8
la $t0 gcd_two
jalr $t0 $ra
addi $sp $sp 4
lw $a0 0x8($sp)
lw $a1 0x4($sp)
beq $ra $ra check
gcd_one nand $a1 $a1 $a1
addi $a1 $a1 1
add $a0 $a0 $a1
jalr $ra $t0
gcd_two nand $a0 $a0 $a0
addi $a0 $a0 1
add $a1 $a1 $a0
jalr $ra $t0