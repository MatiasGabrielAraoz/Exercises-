CC = clang
CC_FLAGS = -Wall -Wextra -fsanitize=address
LIBS = -lSDL3
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
