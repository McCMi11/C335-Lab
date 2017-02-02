CC = gcc
CFLAGS = -g

poly: dump.o poly.o
	$(CC) $(CFLAGS) -o poly dump.o poly.o

dump.o: dump.c
	$(CC) $(CFLAGS) -c dump.c

poly.o: poly.c
	$(CC) $(CFLAGS) -c poly.c
