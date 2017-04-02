

#Makefile: PhotoLab 

all: PhotoLab

PhotoLab: FileIO.o DIPs.o PhotoLab.o Advanced.o
	gcc -g -Wall -ansi -lm FileIO.o DIPs.o PhotoLab.o Advanced.o -o PhotoLab

PhotoLabTest: FileIO.o DIPs.o PhotoLab.o Advanced.o
	gcc -g -DDEBUG -Wall -ansi -lm FileIO.o DIPs.o Photolab.o Advanced.o -o PhotoLabTest

FileIO.o: FileIO.c FileIO.h Constants.h
	gcc -Wall -ansi -c FileIO.c -o FileIO.o

DIPs.o: DIPs.c DIPs.h Constants.h
	gcc -Wall -ansi -c DIPs.c -o DIPs.o

PhotoLab.o: PhotoLab.c Constants.h 
	gcc -Wall -ansi -c PhotoLab.c -o PhotoLab.o

Advanced.o: Advanced.c Advanced.h Constants.h
	gcc -Wall -ansi -c Advanced.c -o Advanced.o


clean:
	rm -f *.o
