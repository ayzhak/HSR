CC = gcc
SRCS = bmp.c julia.c
HDRS = $(SRCS:.c=.h)
OBJS = $(SRCS:.c=.o)
TGTS = fork
CFLAGS = -g3

.PHONY: clean

all: $(TGTS)

%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<

fork: fork.c $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ -lm

clean:
	rm -f $(OBJS)
	rm -f *.bmp
	rm -f $(TGTS)
