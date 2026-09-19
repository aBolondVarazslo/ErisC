CC = gcc
CFLAGS = -std=c11 -Wall -Wextra

erisc: src/lexer.c src/main.c
	mkdir build/
	$(CC) $(CFLAGS) -o build/erisc src/lexer.c src/main.c

run: erisc
	build/erisc ErisC/file.eris

clean:
	rm -rf build/