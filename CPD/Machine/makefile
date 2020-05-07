# Makefile for try projecl

binary:	main.o libtry.a myBigChars.o mySimpleComputer.o myTerm.o myReadkey.o
	gcc -o binary main.o myBigChars.o mySimpleComputer.o myTerm.o myReadkey.o -L -ltry

main.o:	main.c
	gcc -c main.c

libtry.a:	myBigChars.o mySimpleComputer.o myTerm.o myReadkey.o
	ar cr libtry.a myBigChars.o mySimpleComputer.o myTerm.o myReadkey.o

myBigChars.o:	myBigChars.c
	gcc -c myBigChars.c

mySimpleComputer.o:	mySimpleComputer.c
	gcc -c mySimpleComputer.c

myTerm.o:	myTerm.c
	gcc -c myTerm.c

myReadkey.o:	myReadkey.c
	gcc -c myReadkey.c

clean:
	rm -f *.o *.a binary
