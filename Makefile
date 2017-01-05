all: clean
	########################################################################
	## BIBLIOTECA LHTHREAD	
	gcc -O -g -c -Wall -Werror -fPIC -lpthread lhthread.c lhthread.h || exit
	gcc -shared -o liblhthread.so lhthread.o || exit
	install -m0755 liblhthread.so /usr/lib/liblhthread.so || exit 

	
clean:
	########################################################################
	## BIBLIOTECA LHTHREAD CLEAN
	rm -f *.o
	rm -f *.so
	rm -f *.gch
	rm -f /usr/lib/liblhthread.so
