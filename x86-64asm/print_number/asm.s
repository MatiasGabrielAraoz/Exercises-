.global _start
.intel_syntax noprefix

.data
    .lcomm input, 64
    newline: .byte 0xa
	prompt: .asciz "Inserta un numero: "
	prompt_len = . - prompt
.bss
    .lcomm buffer, 21

.text
_start:
	mov rax, 1
	mov rdi, 1
	lea rsi, [prompt]
	mov rdx, prompt_len
	syscall

	mov rax, 0
	mov rdi, 0
	lea rsi, [input]
	mov rdx, 64
	syscall

    mov rax, [input]
    lea rbx, buffer
    add rbx, 20
    mov byte ptr [rbx], 0
    
    mov rcx, 10

.loop_int_to_str:
    xor rdx, rdx
    div rcx
    add dl, '0'
    dec rbx
    mov [rbx], dl
    test rax, rax
    jnz .loop_int_to_str

    # Calcular longitud
    lea rdx, buffer
    add rdx, 20
    sub rdx, rbx               # rdx = longitud

    # Imprimir número
    mov rax, 1
    mov rdi, 1
    mov rsi, rbx
    syscall

    # Imprimir newline
    mov rax, 1
    mov rdi, 1
    lea rsi, newline
    mov rdx, 1
    syscall

    # Salir
    mov rax, 60
    xor rdi, rdi
    syscall
