CC = gcc
CFLAGS = -std=c11 -Wall -Wextra

erisc: src/lexer.c src/main.c
	$(CC) $(CFLAGS) -o erisc src/lexer.c src/main.c

clean:
	rm -f erisc