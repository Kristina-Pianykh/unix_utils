# the compiler: gcc for C program, define as g++ for C++
CC = gcc

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS  = -Wall -Werror

# the build target executable:
# TARGET = myprog

all: wcat wgrep wzip

wcat: wcat.c
	$(CC) $(CFLAGS) -o wcat wcat.c

wgrep: wgrep.c
	$(CC) $(CFLAGS) -o wgrep wgrep.c

wzip: wzip.c
	$(CC) $(CFLAGS) -o wzip wzip.c

wunzip: wunzip.c
	$(CC) $(CFLAGS) -o wunzip wunzip.c

clean:
	$(RM) wcat wgrep wzip wunzip *.z

test_compression:
	./test_compression.sh
