CC = as
LD = ld
FLAGS =
OUT = main
SRC = main.s

all: $(OUT)

$(OUT): $(SRC)
	$(CC) $(SRC) -o $(OUT).o
	$(LD) $(OUT).o -o $(OUT)

.PHONY: all
