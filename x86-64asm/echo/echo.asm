.intel_syntax noprefix
.data
	prompt:
	.ascii "Inserta el texto acá: "
	.byte 0xa

	prompt_len = . - prompt

.bss
	.lcomm input_buffer, 256


.text
	.globl _start
	_start:
	// write prompt
	mov rax, 1
	mov rdi, 1
	lea rsi, [rip + prompt]
	mov rdx, 23
	syscall

	// read input
	mov rax, 0
	mov rdi, 0	
	lea rsi, [rip + input_buffer]
	mov rdx, 256
	syscall

	mov rax, 1
	mov rdi, 1
	lea rsi, [rip + input_buffer]
	mov rdx, 256
	syscall

	// exit
	mov rax, 60
	mov rdi, rdi
	syscall
