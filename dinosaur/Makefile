libs = $(shell find ../lib -name "*.c")
all: main.out
	./main.out	
main.out:
	$(CC) main.c $(libs) -g -Wall -Wextra -Werror --std=c11 -o main.out
clean:
	rm main.out
