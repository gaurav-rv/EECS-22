
#Makefile

all: MovieLab

clean:
	rm -f *.o
	rm -f MovieLab
	rm -f *.a

MovieLab: MovieLab.c libFileIO.a libFilter.a
	gcc MovieLab.c -lFileIO -lFilter -L. -o MovieLab  


libFileIO.a: Image.o ImageList.o Movie.o MovieLab.o 
	ar rc libFileIO.a Image.o ImageList.o Movie.o
	ranlib libFileIO.a

libFilter.a: DIPs.o MovieLab.o
	ar rc libFilter.a DIPs.o
	ranlib libFilter.a

Image.o: Image.c Image.h 
	gcc -c -Wall -ansi Image.c -o Image.o

ImageList.o: ImageList.c ImageList.h Image.h
	gcc -c -Wall -ansi ImageList.c -o ImageList.o

DIPs.o: DIPs.c DIPs.h
	gcc -c -Wall -ansi DIPs.c -o DIPs.o

Movie.o: Movie.c Movie.h Image.h ImageList.h
	gcc -c -Wall -ansi Movie.c -o Movie.o
