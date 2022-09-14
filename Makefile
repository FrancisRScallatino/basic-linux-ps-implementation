WFLAGS = -Wall -Werror

output: src/MYps.c
	gcc $(WFLAGS) src/MYps.c -o MYps
clean:
	rm -rf *.o MYps MYpsDB

#debugging
db: src/MYps.c
	gcc -g src/MYps.c -o MYpsDB
