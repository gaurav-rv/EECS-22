#Makefile
 
all: PhotoLab PhotoLabTest
 
clean:
	rm -f *.o
	rm -f PhotoLab
	rm -f PhotoLabTest
 
PhotoLabTest: PhotoLab.c libFileIO.a libFilter.a
	gcc -g -DDEBUG PhotoLab.c -lFileIO -lFilter -L. -o PhotoLabTest
 
PhotoLab: PhotoLab.c libFileIO.a libFilter.a
	gcc -g PhotoLab.c -lFileIO -lFilter -L. -o PhotoLab
 
libFileIO.a: Image.o FileIO.o
	ar rc libFileIO.a Image.o FileIO.o
	ranlib libFileIO.a
 
libFilter.a: DIPs.o Advanced.o
	ar rc libFilter.a DIPs.o Advanced.o
	ranlib libFilter.a
 
Image.o: Image.c Image.h
	gcc -c -Wall -ansi Image.c -o Image.o
 
FileIO.o: FileIO.c FileIO.h
	gcc -c -Wall -ansi FileIO.c -o FileIO.o
 
DIPs.o: DIPs.c DIPs.h
	gcc -c -Wall -ansi DIPs.c -o DIPs.o
 
Advanced.o: Advanced.c Advanced.h
	gcc -c -Wall -ansi Advanced.c -o Advanced.o
 
#EOF
