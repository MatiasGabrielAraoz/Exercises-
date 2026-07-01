CC = clang
CC_FLAGS = -Wall -Wextra -Wpedantic
LIBS = -lm
SRC = main.c
OUT = main

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(CC_FLAGS) $(LIBS) $(SRC) -o $(OUT)

clear: 
	rm -rf $(OUT)

run: 
	./$(OUT)

.PHONY: all run clear
