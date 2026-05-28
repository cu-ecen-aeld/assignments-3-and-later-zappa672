all: clean writer
default: writer

writer:
	$(CC) -g -Wall -c -o writer.o writer.c
	$(CC) -g -Wall writer.o -o writer

clean:
	rm -f *.o aesdsocket *.elf *.map
