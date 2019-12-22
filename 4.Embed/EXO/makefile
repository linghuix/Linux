exoskeleton:main.o epos.o
	arm-linux-gcc main.o epos.o -o exoskeleton -lm
epos.o:epos.c epos.h
	arm-linux-gcc -c epos.c -o epos.o
main.o:main.c epos.h
	arm-linux-gcc -c main.c -o main.o 
clean:
	rm -rf *.o exoskeleton
