all:
	gcc -o crypto Chiffrement.c Vigenere.c Interface.c cesar.c transformationT.c -lm

Chiffrement: Chiffrement.o Vigenere.o Interface.o cesar.o transformationT.o
	gcc -o crypto Chiffrement.o Vigenere.o Interface.o cesar.o transformationT.o -lm

Vigenere: Vigenere.c Vigenere.h Interface.h
	gcc -c Vigenere.c

cesar: cesar.c cesar.h
	gcc -c cesar.c

Interface: Interface.c Interface.h
	gcc -c Interface.c -lm

transformationT: transformationT.c transformationT.h Interface.h
	gcc -c transformationT.c

clean:
	rm -f Chiffrement.o Vigenere.o Interface.o cesar.o transformationT.o crypto
