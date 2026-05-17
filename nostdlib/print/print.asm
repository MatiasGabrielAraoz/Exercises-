.intel_syntax noprefix
.global asm_print
.global asm_exit

asm_print: 
// rdi = texto, rsi = len, rdx = fd
	mov r10, rdi
	mov r9, rsi
	mov r8, rdx

	mov rax, 1 
	mov rdi, r8 
	mov rsi, r10 
	mov rdx, r9 
	syscall
	ret

asm_exit:
	mov rax, 60
	mov rdi, 0
	syscall
	ret



