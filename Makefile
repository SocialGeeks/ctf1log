BIN=ctflog
OBJ=$(patsubst %.c, %.o, $(wildcard *.c))
PREFIX=/sandbox/bin

CFLAGS=-Wall

$(BIN) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY : clean

clean :
	$(RM) $(BIN) $(OBJ)

.PHONY : install

install : $(BIN)
	install -o root -g root -m "4555" $< $(PREFIX)/$(BIN)
