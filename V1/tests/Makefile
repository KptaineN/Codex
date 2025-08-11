.RECIPEPREFIX := >
CC=cc
CFLAGS=-Wall -Wextra -Werror -I../include -I../include/LIBFT
LDFLAGS=../include/LIBFT/libft.a -lcriterion
SRC=test_custom_split.c ../SRC/parser/costum_split.c

all: test

test: $(SRC)
>$(CC) $(CFLAGS) $(SRC) $(LDFLAGS) -o test

run: test
>./test

clean:
>rm -f test

.PHONY: all run clean test
