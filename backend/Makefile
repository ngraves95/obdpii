
CC=gcc
CFLAGS=-I$(IDIR) -Wall -Werror

ODIR=obj

SRCDIR = src
SRCS = $(wildcard $(SRCDIR)/*.c)

IDIR = inc
DEPS = $(wildcard $(IDIR)/*.h)

_OBJ = $(SRCS)
OBJ = $(patsubst $(SRCDIR)/%.c, $(ODIR)/%.o, $(SRCS))

MAIN = main

$(ODIR)/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

$(MAIN): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean echo-src echo-obj run

run : $(MAIN)
	./$(MAIN)

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~

echo-src:
	@echo $(SRCS)
echo-obj:
	@echo $(OBJ)
