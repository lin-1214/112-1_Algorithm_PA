# CC and CFLAGS are varilables
CC = g++
CFLAGS = -c
AR = ar
ARFLAGS = rcv

OPTFLAGS = -O2

all	: bin/mps
	ulimit -s 68157440
	@echo -n ""

bin/mps	: main_opt.o lib
			$(CC) $(OPTFLAGS) main_opt.o tm_usage.o -o bin/mps
main_opt.o 	   	: src/main.cpp src/tm_usage.h
			$(CC) $(CFLAGS) $< -Ilib -o $@

lib: ./libtm_usage.a

./libtm_usage.a: tm_usage.o
	$(AR) $(ARFLAGS) $@ $<
tm_usage.o: src/tm_usage.cpp src/tm_usage.h
	$(CC) $(CFLAGS) $<

clean:
	rm ./*.o ./libtm_usage.a ./bin/mps