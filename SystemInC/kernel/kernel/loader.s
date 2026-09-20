BITS 32
global loader
extern kmain

global loader

MAGIC_NUMBER equ 0x1BADB002
FLAGS equ 0x0
CHECKSUM equ -(MAGIC_NUMBER + FLAGS)
STACK_SIZE equ 4096

section .multiboot
align 4
	dd MAGIC_NUMBER
	dd FLAGS
	dd CHECKSUM

section .text
loader: 
	mov esp, stack_top
	call kmain

.hang:
	jmp .hang



section .bss
align 4
stack_bottom:
	resb STACK_SIZE ; 4kb

stack_top: 
