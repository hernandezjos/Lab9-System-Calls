CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES= info.c pinfo.c pmod.c finfo.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE= lab9
all: $(EXECUTABLE)
# Pull in dependency info for existing .o files
-include $(OBJECTS:.o=.d)
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
.c.o:
	$(CC) $(CFLAGS) $< -o $@
	$(CC) -MM $< > $*.d
clean:
	rm -f $(OBJECTS) $(EXECUTABLE) *.d
.PHONY: all clean