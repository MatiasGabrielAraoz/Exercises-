.section .data
	msg: 
		.ascii "Hola"
	msg_end:
		.set msg_len, msg_end - msg
	.set counter, 0
	
.section .text
	.global _start

_start: 
loop: 
	movq counter, %rax
	cmp %rax, msg_len
	je end_loop

end_loop:
	mov $60, %rax
	mov $0, %rdi
	syscall
