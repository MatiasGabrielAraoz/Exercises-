.data 
	prompt1: .asciiz "Inserta el primer numero: "
	prompt2: .asciiz "Inserta el segundo numero: "
.text
	.globl main
	multiply:
		mul $v0, $a0, $a1
		jr $ra 
	main:
	
	li $v0, 4
	la $a0, prompt1
	syscall

	li $v0, 5
	syscall
	move $t0, $v0

	li $v0, 4
	la $a0, prompt2
	syscall

	li $v0, 5
	syscall
	move $t1, $v0

	move $a0, $t0
	move $a1, $t1
	jal multiply
	move $t3, $v0

	li $v0, 1
	move $a0, $t3
	syscall

	li $v0, 10
	syscall
