all: c
	./main.out
c:
	$(CC) main.c -Wall -Wextra -Werror --std=c11 -o main.out
