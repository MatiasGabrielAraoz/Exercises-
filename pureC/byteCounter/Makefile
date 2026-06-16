CC = clang
CC_FLAGS = -Wall -Wextra
SRC = main.c
OUT = main

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CC_FLAGS) $(SRC) -o $(OUT)

clear: 
	rm -rf $(OUT)

run: 
	./$(OUT)

.PHONY: all run clear
