VPATH = src hedr
GC = gcc
WFLAGS = -Wall -Werror

MYps: src/OptProc.o src/GetProcList.o src/MYps.o
	$(GC) $(WFLAGS) src/OptProc.o src/GetProcList.o src/MYps.o -o MYps

MYps.o: MYps.c
	$(GC) $(WFLAGS) -c MYps.c

OptProc.o: OptProc.c OptProc.h
	$(GC) $(WFLAGS) -c OptProc.c

GetProcList.o: GetProcList.c GetProcList.h
	$(GC) $(WFLAGS) -c GetProcList.c	

clean:
	rm -rf *.o ./*/*.o MYps MYpsDB

#debugging
db: MYps.o OptProc.o GetProcList.o
	$(GC) -g src/OptProc.o src/GetProcList.o -o MYpsDB src/MYps.c
