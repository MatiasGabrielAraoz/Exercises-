CC = clang
FLAGS = -nostdlib -fno-builtin -fno-stack-protector
SRC = main.s print.c main.c  
OUT = main

main: $(SRC)
	$(CC) $(FLAGS) $(SRC) -o $(OUT)

run: main
	./$(OUT)

.PHONY: all clear run
