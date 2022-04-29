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
*  Nom du fichier : transformationT.c                                                   *
*                                                                             *
******************************************************************************/

#include <stdio.h>
#include <ctype.h>
#include <locale.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Interface.h"
#include "transformationT.h"

void VerifierConvertir() {
	int estalphanum;
	char* ligne;
	ligne = (char*) malloc (strlen(pOptionsCrypto.texte)+1);
	strcpy(ligne, pOptionsCrypto.texte);
	const char* nonaccent = "AAAAAAECEEEEIIIIDNOOOOOx0UUUUYPsaaaaaaeceeeeiiiiOnooooo/0uuuuypy";
	if (setlocale(LC_CTYPE, "") == NULL)
	{
		free(ligne);
		free(pOptionsCrypto.texte);
		free(pOptionsCrypto.clef);
		if (pOptionsCrypto.useFile == 1)
			free(pOptionsCrypto.filename);
		affichage('r', "setlocale");
	}
	wchar_t ws[strlen(ligne)+1];
	if (mbstowcs(ws, ligne, strlen(ligne)) == (size_t)-1)
	{
		free(ligne);
		free(pOptionsCrypto.texte);
		free(pOptionsCrypto.clef);
		if (pOptionsCrypto.useFile == 1)
			free(pOptionsCrypto.filename);
		affichage('r', "mbstowcs");
	}
	estalphanum = 1;
	for (unsigned i = 0;ws[i] != L'\0'; i++){
		if (ws[i] <= 1000 && ws[i] >=0) {
			if (!isalnum(ws[i]) && ws[i] != 32 && ws[i] != '\n' && ws[i] != '\0'){
				if ( ws[i] >=192 && ws[i] <=255) {
					ws[i] = nonaccent[ ws[i]-192 ];
				}
			}
			if (!isalnum(ws[i]) && ws[i] != 32 && ws[i] != 46 && ws[i] !=44 && ws[i] != '\n' && ws[i] <=255 && ws[i] >=0){
				estalphanum = 0;
			}
		}
    }
	wcstombs(ligne, ws, strlen(ligne));
	strcpy(pOptionsCrypto.texte, ligne);
	free(ligne);
	pOptionsCrypto.isAlphaNum = estalphanum;
}
