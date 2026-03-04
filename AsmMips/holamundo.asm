.data
msg: .asciiz "La suma da: "
.text
	.globl main
	main: 
		li $t0, 12
		li $t1, 1

		add $t4, $t0, $t1
		
		li $v0, 4
		la $a0, msg
		syscall

		li $v0, 1
		move $a0, $t4
		syscall


		li $v0, 10
		syscall















