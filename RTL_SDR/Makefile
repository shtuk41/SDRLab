CC = gcc
CFLAGS = 
INCLUDES = -I/usr/include/librtlsdr -I/usr/include/libusb-1.0
LIBPATH = -L/usr/lib/x86_64-linux-gnu
LDLIBS = -lrtlsdr -lusb-1.0

RELEASE_FLAGS = -O2 -DNDEBUG -Wall
DEBUG_FLAGS = -g -O0 -DDEBUG -Wall -Wextra -Werror

all: release

debug: CFLAGS += $(DEBUG_FLAGS) $(INCLUDES)
debug: LDFLAGS += $(LIBPATH)
debug: comm.c
	$(CC) $(CFLAGS) $< -o comm $(LDFLAGS) $(LDLIBS)

release: CFLAGS += $(RELEASE_FLAGS) $(INCLUDES)
release: LDFLAGS += $(LIBPATH)
release: comm.c
	$(CC) $(CFLAGS) $< -o comm $(LDFLAGS) $(LDLIBS)

clean:
	rm -f comm
