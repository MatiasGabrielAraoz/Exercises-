CC = clang
FLAGS = -Wall -Wextra -Wpedantic 
LIBS = -lSDL3 -lm -lSDL3_gfx
SRC = main.c
OUT = main

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(SRC) $(FLAGS) $(LIBS) -o $(OUT)

run: all
	./$(OUT)

clean:
	rm -rf $(OUT)

.PHONY: all clean run
