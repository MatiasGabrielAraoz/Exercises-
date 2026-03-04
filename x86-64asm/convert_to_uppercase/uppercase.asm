.intel_syntax noprefix
.data
	prompt: .ascii "Inserta texto: "
	.byte 0xa
	prompt_len = . - prompt
.bss
	.lcomm input_buffer, 256
	.lcomm input_uppercase, 256
.text
	.globl _start
	_start: 
		mov rax, 1
		mov rdi, 1
		lea rsi, [rip + prompt]
		mov rdx, prompt_len
		syscall
		
		mov rax, 0
		mov rdi, 0
		lea rsi, [rip + input_buffer]
		mov rdx, 256
		syscall
		lea rsi, [rip + input_buffer]
		mov byte ptr [rsi + rax], 0



		//TODO: call function to convert to uppercase every character
		lea rdi, [rip + input_buffer]
		call convert_to_upper
		mov [input_uppercase], rax

		mov rax, 1
		mov rdi, 1
		lea rsi, [input_buffer]
		mov rdx, 256
		syscall

		//exit
		call exit
	convert_to_upper:
		// Guardar el stack pointer en el base pointer
		push rbp
		mov rbp, rsp
		xor rcx, rcx
		jmp convert_to_upper_loop
	convert_to_upper_loop:
		mov al, [rdi]
		cmp al, 0
		je exit_loop
		
		//TODO: Logic to convert to uppercase
		cmp al, 'a'
		jl loop_continue

		cmp al, 'z'
		jg loop_continue

		xor al, 0b00100000
		mov [rdi], al

	loop_continue:
		inc rdi
		jmp convert_to_upper_loop

	exit_loop:
		mov rsp, rbp
		pop rbp
		ret


	exit:
		mov rax, 60
		xor rdi, rdi
		syscall
