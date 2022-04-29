/******************************************************************************
*  ASR => 4R2.04                                                              *
*******************************************************************************
*                                                                             *
*  N� de Sujet : 3                                                            *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Intitul� : Chiffrement de messages                                         *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Nom-pr�nom1 : Al Riyami Ismail                                             *
*                                                                             *
*  Nom-pr�nom2 : Alfred Yael                                                  *
*                                                                             *
*  Nom-pr�nom3 : Bounoua Yahya                                                *
*                                                                             *
*  Nom-pr�nom4 : Combet Florent                                               *
*                                                                             *
*******************************************************************************
*                                                                             *
*  Nom du fichier : Chiffrement.c                                                   *
*                                                                             *
******************************************************************************/



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Vigenere.h"
#include "Interface.h"
#include "cesar.h"
#include "transformationT.h"



int main(int argc, char *argv[]) {

	int useFile; //Default Value 0 = using stream input
	int useCrypt; //0 Default value = Cesar Code
	char* clef;
	char* texte;
	int chiffrer = 0;
	char* filename;
	int isAlphaNum;
	getOption(argv,argc);
	useFile = pOptionsCrypto.useFile;
	useCrypt = pOptionsCrypto.useCrypt;
	chiffrer = pOptionsCrypto.chiffrer;
	texte = (char *) malloc (strlen(pOptionsCrypto.texte)+1);
	strcpy (texte, pOptionsCrypto.texte);
	clef = (char *) malloc (strlen(pOptionsCrypto.clef)+1);
	strcpy (clef, pOptionsCrypto.clef);
	if (useFile == 1) {
		filename = (char *) malloc (strlen(pOptionsCrypto.filename)+1);
		strcpy (filename, pOptionsCrypto.filename);
	}

	VerifierConvertir();
	strcpy(texte, pOptionsCrypto.texte);
	isAlphaNum = pOptionsCrypto.isAlphaNum;
	if (isAlphaNum == 0) {
		free(texte);
		free(clef);
		free(pOptionsCrypto.texte);
		free(pOptionsCrypto.clef);	
		if (useFile == 1) {
			free(filename);
			free(pOptionsCrypto.filename);
		}
		affichage('r', "le texte contient des valeurs non acceptee");
	}
	switch(useCrypt) {
		case 0:
			if (chiffrer==1) {
				CesarCrypt(texte, atoi(clef));
			} else {
				CesarDecrypt(texte, atoi(clef));
			}
			break;
		case 1:
			if (chiffrer==1) {
				vigenere_chiff(texte);
			} else {
				vigenere_dechiffr(texte);
			}
			break;
	}
	strcpy(pOptionsCrypto.texte, texte);

	if (useFile==1) {
		EcrireFic(texte);
		free(texte);
		free(clef);
		free(pOptionsCrypto.texte);
		free(pOptionsCrypto.clef);
		free(filename);
			
		if (chiffrer==1) {
			affichage('f', NULL);
		} else {
			affichage('y', NULL);
		}
	} else {
		free(texte);
		free(clef);	
		if (chiffrer==1) {
			affichage('c', pOptionsCrypto.texte);
		} else {
			affichage('d', pOptionsCrypto.texte);
		}
	}
    return 1;
}


