.data
prompt: .asciiz "\n Inserta Un numero: "

.text
	.globl __start
	__start: 
		
		li $v0, 4
		la $a0, prompt
		syscall
		

		li $v0, 5
		syscall
		move $t0, $v0

		move $a0, $t0
		jal factorial
		move $t0, $v0

		li $v0, 1
		move $a0, $t0
		syscall
		
		j __start
		li $v0, 10
		syscall



	factorial:
		bgt $a0, 1, loop_factorial
		li $v0, 1
		jr $ra
		nop

	loop_factorial:
		addiu $sp, $sp, -8
		sw $a0, 0($sp)
		sw $ra, 4($sp)

		add $a0, $a0, -1
		jal factorial
		nop

		lw $a0, 0($sp)
		lw $ra, 4($sp)
		addiu $sp, $sp, 8
		

		mul $v0, $a0, $v0
		jr $ra
		nop
