.intel_syntax noprefix
.global asm_print
.global asm_exit
.global asm_fopen
.global asm_fclose
.global asm_fread


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

asm_fopen:
	mov rax, 2
	mov rdi, rdi
	mov rsi, rsi
	mov rdx, 0
	syscall
	ret

asm_fclose:
//rdi = fd
	mov rax, 3
	syscall

	ret

asm_fread:
// necesita rdi = fd, rsi = buf, rdx = count
	mov rax, 0
	syscall
	ret

asm_exit:
	mov rax, 60
	mov rdi, 0
	syscall
	ret
