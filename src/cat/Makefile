C=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11

all: s21_cat

test: s21_cat
	sh ./cat_test.sh 3
	
s21_cat: struct func cat
	$(C) cat.o cat_func.o parser_struct.o -g3 -o s21_cat

cat: cat.c
	$(C) $(CFLAGS) cat.c -c

func: cat_func.c
	$(C) $(CFLAGS) cat_func.c ../common/parser_struct.c ../common/parser_struct.h -c

struct:
	$(C) $(CFLAGS) ../common/parser_struct.c -c

clean:
	rm -rf *.o s21_cat