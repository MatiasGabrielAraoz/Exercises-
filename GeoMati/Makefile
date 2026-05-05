Compiler = clang
CFLAGS = -fsanitize=address -Wall -Wextra -g
LIBS = -lSDL3 -lm
TARGET = main
SRC = main.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(Compiler) $(CFLAGS) $(SRC) -o $(TARGET) $(LIBS)
	@echo "Compilado correctamente"

clean:
	rm -f $(TARGET)

run: $(TARGET)
	./$(TARGET)


.PHONY: all clean run
