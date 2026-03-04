.data
prompt: .asciiz "\n Inserta Un numero: "
newline: .asciiz "\n"
buffer: .space 10          # Buffer para leer números como strings

.text
.globl _start
_start:
    # Mostrar prompt (sys_write)
    li $v0, 4004           # syscall number for write
    li $a0, 1              # file descriptor: stdout
    la $a1, prompt
    li $a2, 19             # longitud del prompt (ajústalo si es necesario)
    syscall

    # Leer número (sys_read)
    li $v0, 4003           # syscall number for read
    li $a0, 0              # file descriptor: stdin
    la $a1, buffer
    li $a2, 10             # leer hasta 9 dígitos
    syscall

    # Convertir string a entero (simple, sin validar)
    la $t0, buffer
    li $t1, 0              # resultado
    li $t2, 10             # multiplicador

convert_loop:
    lb $t3, 0($t0)         # leer un carácter
    beq $t3, 10, convert_done  # si es newline, terminar
    beq $t3, 0, convert_done   # si es null, terminar
    sub $t3, $t3, '0'      # convertir a dígito (ASCII a número)
    mul $t1, $t1, $t2      # resultado = resultado * 10
    add $t1, $t1, $t3      # resultado = resultado + dígito
    add $t0, $t0, 1        # siguiente carácter
    j convert_loop

convert_done:
    move $a0, $t1          # pasar argumento a factorial
    jal factorial
    move $t4, $v0          # guardar resultado

    # Convertir resultado a string (para mostrarlo)
    la $a1, buffer + 9     # empezar desde el final del buffer
    li $t5, 10
    li $t6, 0
    sb $zero, 0($a1)       # null terminator

convert_result:
    div $t4, $t5
    mflo $t4               # cociente
    mfhi $t7               # resto
    add $t7, $t7, '0'
    add $a1, $a1, -1
    sb $t7, 0($a1)
    add $t6, $t6, 1
    bnez $t4, convert_result

    # Mostrar resultado (sys_write)
    li $v0, 4004
    li $a0, 1
    move $a2, $t6          # longitud del número
    syscall

    # Mostrar newline
    li $v0, 4004
    li $a0, 1
    la $a1, newline
    li $a2, 1
    syscall

    # Salir (loop infinito, pero con exit)
    # j _start   # para loop infinito (comentado)
    li $v0, 4001           # syscall number for exit
    li $a0, 0
    syscall

factorial:
    bgt $a0, 1, loop_factorial
    li $v0, 1
    jr $ra

loop_factorial:
    addiu $sp, $sp, -8
    sw $a0, 0($sp)
    sw $ra, 4($sp)

    add $a0, $a0, -1
    jal factorial

    lw $a0, 0($sp)
    lw $ra, 4($sp)
    addiu $sp, $sp, 8

    mul $v0, $a0, $v0
    jr $ra
