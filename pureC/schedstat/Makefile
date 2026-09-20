CC = clang
FLAGS = -Wall -Wextra -Wpedantic 
SRC = src/*
OUT = main

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CC_FLAGS) $(SRC) -o $(OUT)

clear: 
	rm -rf $(OUT)

run: 
	./$(OUT)

.PHONY: all run clear
