Repetative dirty instructions

F la $V0 4
A sw $V0 0x0($V0)
T addi $zero 0

C la $V0 4
A sw $V0 0x0($V0)
T beq $V0 $V0 F