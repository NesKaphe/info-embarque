DEBUG = no
PATHHEADERS = include/
CC = gcc

ifeq ($(DEBUG), yes)
	CFLAGS = -g -W -Wall -I$(PATHHEADERS)
else
	CFLAGS = -W -Wall -I$(PATHHEADERS)
endif

OBJ = bin/main.o
EXEC = main
TEST1 = rectangle
OBJTEST1 = bin/rectangle.o
TEST2 = carre
OBJTEST2 = bin/carre.o
TESTS = $(TEST1) $(TEST2)
LIB = lib/libcolimacon.so

all: $(LIB) $(EXEC) $(TESTS)

lib: $(LIB)

tests: $(TESTS)

rectangle: $(OBJTEST1)
	$(CC) -o $@ $^ $(CFLAGS) -Llib -lcolimacon

carre: $(OBJTEST2)
	$(CC) -o $@ $^ $(CFLAGST) -Llib -lcolimacon

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) -Llib -lcolimacon

lib/libcolimacon.so: bin/libcolimacon.o
	$(CC) -shared -Wl,-soname,libcolimacon.so -o $@ $< $(CFLAGS)

bin/libcolimacon.o: src/colimacon.c
	$(CC) -fPIC -o $@ -c $< $(CFLAGS)

bin/main.o: main.c
	$(CC) -o $@ -c $< $(CFLAGS)

bin/%.o: src/%.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf bin/*.o lib/libcolimacon.so

mrproper: clean
	rm -rf $(EXEC) $(TESTS)
