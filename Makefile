# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
all: wcat wgrep wzip wunzip reverse
CFLAGS  = -Wall -Werror -g

wcat: wcat.c
	$(CC) $(CFLAGS) -o wcat wcat.c

wgrep: wgrep.c
	$(CC) $(CFLAGS) -o wgrep wgrep.c

wzip: wzip.c
	$(CC) $(CFLAGS) -o wzip wzip.c

wunzip: wunzip.c
	$(CC) $(CFLAGS) -o wunzip wunzip.c

byte_int: byte_int.c
	$(CC) $(CFLAGS) -o byte_int byte_int.c

reverse: reverse.c
	$(CC) $(CFLAGS) -o reverse reverse.c

clean:
	$(RM) wcat wgrep wzip reverse wunzip *.z

test_compression:
	./test_compression.sh

test_reverse:
	./test_reverse.sh
