OPT = -O0 -g3
LIB_SOURCES1 = main.c

LIB_SOURCES = $(addprefix src/, $(LIB_SOURCES1))
CC = gcc
TARGET = run
LIB_OBJECTS =$(LIB_SOURCES:.c=.o)
LDFLAGS= -L. $(OPT)
LIBS= -lpthread -ldl libiron.a -lm -lglfw -lX11 -lGL
ALL= $(TARGET)
CFLAGS = -Isrc/ -I. -Iinclude/ -std=gnu11 -c $(OPT) -Werror=implicit-function-declaration -Wformat=0 -D_GNU_SOURCE -fdiagnostics-color  -Wwrite-strings -msse4.2 -Werror=maybe-uninitialized -DUSE_VALGRIND -DDEBUG -Wall

all: libiron.a 
all: $(TARGET)

$(TARGET): $(LIB_OBJECTS) 
	$(CC) $(LDFLAGS)   $(LIB_OBJECTS) $(LIBS)  -o $(TARGET)

.PHONY: iron/libiron.a

iron/libiron.a:
	make -C iron

libiron.a: iron/libiron.a
	cp iron/libiron.a libiron.a

libiron.bc:
	make -C iron wasm
	cp iron/libiron.bc .
.c.o: $(HEADERS) $(LEVEL_CS)
	$(CC) $(CFLAGS) $< -o $@ -MMD -MF $@.depends

release: OPT = -O4 -g0
release: all

depend: h-depend
clean:
	rm -f $(LIB_OBJECTS) $(ALL) src/*.o.depends src/*.o
	rm libcrypto.bc libiron.bc
	rm libcrypto.a libiron.a
	make -C iron clean
.PHONY: test
test: $(TARGET)
	make -f makefile.test test

-include $(LIB_OBJECTS:.o=.o.depends)


