C = gcc
CFLAGS = -Wall -g

TARGETS = master slave

all: $(TARGETS)

master: master.o
	$(C) $(CFLAGS) -o $@ master.o

slave: slave.o
	$(C) $(CFLAGS) -o $@ slave.o

clean:
	rm -rf *.o $(TARGETS)
