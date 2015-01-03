.PHONY: clean

CC = g++
CCFLAGS = -Wall -std=gnu++0x
CCDFLAGS = -g -Wall -std=gnu++0x

all: paging

debug: simulator.cc async_io_ops.cc lru.cc
	$(CC) $(CCDFLAGS) -pthread -o paging simulator.cc async_io_ops.cc lru.cc

paging: simulator.cc async_io_ops.cc lru.cc
	$(CC) $(CCFLAGS) -pthread -o paging simulator.cc async_io_ops.cc lru.cc

clean:
	rm -f paging

