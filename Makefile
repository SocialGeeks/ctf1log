BIN=ctflog
OBJ=$(patsubst %.c, %.o, $(wildcard *.c))
PREFIX=/sandbox

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
	install -o root -g root -m "4555" $< $(PREFIX)/bin/$(BIN)
	install -o root -g ctf  -m "0640" bash_profile $(PREFIX)/home/ctf/.bash_profile
