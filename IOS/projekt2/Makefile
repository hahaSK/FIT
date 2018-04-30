CC = gcc
EXECUTABLE = proj2

SOURCE_FILES = proj2.c BusSolution.c
HEADER_FILES = proj2.h BusSolution.h

RM = rm -f

CFLAGS = -std=gnu99 -Wall -Wextra -Werror -pedantic
LFLAGS = -lpthread

OBJFILES = $(SOURCE_FILES:.c=.o)

.PHONY: all

all : $(EXECUTABLE)

%.o : %.c
	$(CC) $(CLFAGS) -c $< -o $@

$(EXECUTABLE) : $(OBJFILES)
	$(CC) $(CFLAGS) -o $@ $(OBJFILES) $(LFLAGS)

clean:
	$(RM) *.o core *.out

cleanEXEC:
	$(RM) $(EXECUTABLE)

pack: $(SOURCE_FILES) $(HEADER_FILES)
	zip $(EXECUTABLE) $^ Makefile
