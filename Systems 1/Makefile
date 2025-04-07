CC = gcc
CFLAGS = -Wall -Wextra -g

# Target for the executable
mallocTest: duMalloc.o mallocTest.o
	$(CC) $(CFLAGS) -o mallocTest duMalloc.o mallocTest.o

# Target for duMalloc.o
duMalloc.o: duMalloc.c duMalloc.h
	$(CC) $(CFLAGS) -c duMalloc.c

# Target for mallocTest.o
mallocTest.o: mallocTest.c duMalloc.h
	$(CC) $(CFLAGS) -c mallocTest.c

# Target to clean up the directory
clean:
	rm -f mallocTest duMalloc.o mallocTest.o