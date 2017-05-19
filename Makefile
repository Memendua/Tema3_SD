# don't modify this file.
# if you want your warn/errors to be less verbose,
# remove -Wextra (and maybe -Wall) but note that we'll
# compile with all CFLAGS listed here.

CC=g++
DEBUG=-g
CFLAGS=-Wall -Wextra -std=c++11
EXEC=imdb
OUTPUT=output

build:
	$(CC) $(CFLAGS) *.cpp -o $(EXEC)

run:
	./$(EXEC)

clean:
	rm $(EXEC) $(OUTPUT)

.PHONY: build run clean
