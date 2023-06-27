all: main.out
	./main.out
main.out:
	$(CC) main.c -O3 -Wall -Wextra -Werror --std=c11 -o main.out
clean:
	rm main.out
