#pragma once

//BUILTINS
typedef __builtin_va_list va_list;
#define va_start(v, l) __builtin_va_start(v, l)
#define va_arg(v, l)   __builtin_va_arg(v, l)
#define va_end(v)      __builtin_va_end(v)

#define size_t unsigned long long
#define NULL ((void*)0)

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define O_RDONLY 0
#define O_WRONLY 1 
#define O_RDRW 2

extern void asm_exit();
extern void asm_print(const char* text, size_t len, int fd);
extern int asm_fopen(const char* filename, int flags);
extern void asm_fclose(int fd);
extern void asm_fread(int fd, void* buff, int count);

void print(const char* format, ...);
