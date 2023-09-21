
TARGET=test

all: build exec


build:
	nasm -f elf -o test.o test.s
	gcc -no-pie -m32 test.o -o test

exec:
	./$(TARGET)

clean:
	rm *.o
