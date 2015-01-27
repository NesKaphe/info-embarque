PATHHEADERS = include/
CC = gcc
CFLAGS = -Wall -Wno-error=unused-but-set-variable -I$(PATHHEADERS)

OBJ = bin/main.o bin/listechaine.o bin/hash.o
EXEC = exe

all: $(EXEC)

exe: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

bin/main.o: main.c
	$(CC) -o $@ -c $< $(CFLAGS)

bin/%.o: src/%.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	@rm -rf bin/*.o bin/main.o

mrproper:
	@rm -rf $(EXEC)
