
CFLAGS = -O3 -Wall

all:	csqrt

csqrt:	csqrtmain.o csqrt.o
	gcc $(CFLAGS) csqrtmain.o csqrt.o -o csqrt
	
csqrt.o: csqrt.c
csqrtmain.o: csqrtmain.c

clean:
	rm -f *.o csqrt
	
time:	csqrt
	time -p ./csqrt
