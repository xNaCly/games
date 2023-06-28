libs = $(shell find ../lib -name "*.c")
flags = -fdiagnostics-color=always  \
	 -Wall \
	 -Wpedantic \
	 -std=c11 \
	 -Wextra \
	 -Werror \
	 -Wshadow \
	 -Wundef \
	 -g \
	 -fno-common

all: main.out
	./main.out	
main.out: clean
	$(CC) main.c $(libs) $(flags) -o main.out
clean:
	rm -fr main.out
