CC = gcc
CFLAGS= -O0 -g -Wunused-parameter -Wall -Wextra 
CLIBSS=
TARGET= postalcode

$(TARGET): postalcode.o list_post.o
	$(CC) $(CFLAGS) $(CLIBS) -o $@ $^

postalcode.o: postalcode.c postalcode.h
	$(CC) -c $(CFLAGS) $(CLIBS) $<

list_post.o: list_post.c list_post.h
	$(CC) -c $(CFLAGS) $(CLIBS) $<

clean:
	rm -f *.o $(TARGET)

