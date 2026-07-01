CC = clang
CC_FLAGS = -Wall -Wextra
SRC = main.c
OUTPUT = main

all: $(OUTPUT)

$(OUTPUT): $(SRC)
	$(CC) $(CC_FLAGS) $(SRC) -o $(OUTPUT)
	@echo "Compilado correctamente"

run: all
	./$(OUTPUT)

clear: 
	rm -rf $(OUTPUT)


.PHONY: all run clear
