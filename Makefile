GC = gcc
WFLAGS = -Wall -Werror

MYps: src/OptProc.o src/GetProcList.o
	$(GC) $(WFLAGS) src/OptProc.o src/GetProcList.o -o MYps src/MYps.c

OptProc.o: src/OptProc.c hedr/OptProc.h
	$(GC) $(WFLAGS) -c src/OptProc.c

GetProcList.o: src/GetProcList.c hedr/GetProcList.h
	$(GC) $(WFLAGS) -c src/GetProcList.c	

clean:
	rm -rf *.o ./*/*.o MYps MYpsDB

#debugging
db: MYps.o OptProc.o
	$(GC) -g src/MYps.o src/OptProc.o -o MYpsDB