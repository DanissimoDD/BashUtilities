C=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11

all: s21_grep

test: s21_grep
	sh grep_test.sh  

s21_grep: struct func grep
	$(C) grep.o func.o parser_struct.o -g3 -o s21_grep

grep: grep.c
	$(C) $(CFLAGS) grep.c -c

func: func.c
	$(C) $(CFLAGS) func.c ../common/parser_struct.c ../common/parser_struct.h -c

struct: 
	$(C) $(CFLAGS) ../common/parser_struct.c -c

clean:
	rm -rf *.o s21_grep