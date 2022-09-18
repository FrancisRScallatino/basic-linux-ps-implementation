GC = gcc
WFLAGS = -Wall -Werror

all: MYps

MYps.o: src/MYps.c
	$(GC) $(WFLAGS) -c src/MYps.c

OptProc.o: src/OptProc.c hedr/OptProc.h
	$(GC) $(WFLAGS) -c src/OptProc.c

MYps: src/MYps.o src/OptProc.o
	$(GC) $(WFLAGS) src/MYps.o src/OptProc.o -o MYps
	
clean:
	rm -rf *.o ./*/*.o MYps MYpsDB

#debugging
db: MYps.o OptProc.o
	$(GC) -g src/MYps.o src/OptProc.o -o MYpsDB