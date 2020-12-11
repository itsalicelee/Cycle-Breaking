# CC and CFLAGS are varilables
CC = g++ -std=c++11
CFLAGS = -c
AR = ar
ARFLAGS = rcv
# -c option ask g++ to compile the source files, but do not link.
# -g option is for debugging version
# -O2 option is for optimized version
DBGFLAGS = -g -D_DEBUG_ON_
OPTFLAGS = -O3

all	: bin/cb
	@echo -n ""

bin/cb   : cycleBreaking_opt.o main_opt.o 
			$(CC) $(OPTFLAGS)  cycleBreaking_opt.o main_opt.o  -o bin/cb

main_opt.o 	   	: src/main.cpp
			$(CC) $(CFLAGS) $<  -o $@
cycleBreaking_opt.o	: src/cycleBreaking.cpp src/cycleBreaking.h
			$(CC) $(CFLAGS) $(OPTFLAGS) $< -o $@

# clean all the .o and executable files
clean:
		rm -rf *.o lib/*.a bin/*