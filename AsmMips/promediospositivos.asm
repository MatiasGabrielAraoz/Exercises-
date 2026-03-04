.data
arr: .word 0,10
arr_end:
arr_len: .space 4

.text
	.globl main
	main: 
		
		la $a0, arr
		la $a1, arr_end
		jal calcArrSize
		sw $v0, arr_len 
		
		
		la $a0, arr
		lw $a1, arr_len
		jal Promedio
		move $t0, $v0
		
		li $v0, 1
		move $a0, $t0
		syscall
		
		
		
		
		li $v0, 10
		syscall

	calcArrSize:

		sub $t2, $a1, $a0
		srl $t2, $t2, 2
		move $v0, $t2
		jr $ra

	Promedio:
		
		addi $sp, $sp, -4
		sw $ra, 0($sp)
		
		move $t0, $a0 # array
		move $t1, $a1 # array_len
		li $t2, 0 # total
		li $t3, 0 # i
		
		j PromedioLoop
		
		
		j EndPromedio
		
	PromedioLoop:
		bge $t3, $t1, EndPromedio
		# $t0 = array
		# $t1 = array_len
		# $t2 = total
		# $t3 = i
		# $t4 = offset
		# $t5 = dirección
		# $t6 = valor arr
		
		
		sll $t4, $t3, 2
		add $t5, $t0, $t4
		
		lw $t6, 0($t5)
		
		add $t2, $t2, $t6
		
		addi $t3, $t3, 1
		
		j PromedioLoop

	EndPromedio:
	
		div $t2, $t1
		mflo $v0
	
		lw $ra, 0($sp)
		addiu $sp, $sp, 4
		
		jr $ra

