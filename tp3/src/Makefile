PATHHEADERS = Include/
CC = gcc
CFLAGS = -Wall -W -I$(PATHHEADERS) -lrt -pthread

OBJ = bin/main.o bin/display.o bin/thread.o bin/fork.o bin/delta.o
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

mrproper: clean
	@rm -rf $(EXEC)
