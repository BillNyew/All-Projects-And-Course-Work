CC = gcc
CFLAGS = -Wall -Wextra -g

# Target for the executable
mallocTest: duMalloc.o mallocTestVersion4.o
	$(CC) $(CFLAGS) -o mallocTest duMalloc.o mallocTestVersion4.o

# Target for duMalloc.o
duMalloc.o: duMalloc.c duMalloc.h
	$(CC) $(CFLAGS) -c duMalloc.c -o duMalloc.o

# Target for mallocTestVersion4.o
mallocTestVersion4.o: mallocTestVersion4.c duMalloc.h
	$(CC) $(CFLAGS) -c mallocTestVersion4.c -o mallocTestVersion4.o

# Target to clean up the directory
clean:
	rm -f mallocTest duMalloc.o mallocTestVersion4.ox