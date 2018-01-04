CC = gcc
CFLAGS= -g -Wall -Wextra
CLIBSS=
TARGET= postalcode

$(TARGET): $(TARGET).c 
	$(CC) $(CFLAGS) $(CLIBS) -o $@ $^

clean:
	rm -f *.o $(TARGET)

