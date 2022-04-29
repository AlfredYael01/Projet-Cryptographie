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
*  Nom du fichier : Vigenere.c                                                  *
*                                                                             *
******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Vigenere.h"
#include "Interface.h"

void vigenere_chiff(char texte[]) {
    removeSpace();
    char* clef;
    int cmpt = 0;
    int i;
    char c;
    clef = (char*) malloc ((strlen(pOptionsCrypto.clef)+1) * sizeof(char));
    strcpy(clef, pOptionsCrypto.clef);
    for (i=0; i<=strlen(texte); i++) {
        if ((texte[i] >= 'A' && texte[i]<= 'Z') || (texte[i] >= 'a' && texte[i]<= 'z')) {
			if (texte[i] >= 'a') {
				c = texte[i] - 'a';
				c += (clef[cmpt % strlen(clef)] - 'a');
				c = c % 26;
				texte[i] = c + 'a';
                cmpt++;
			} else {
				c = texte[i] - 'A';
				c += (clef[cmpt % strlen(clef)] - 'a');
				c = c % 26;
				texte[i] = c + 'A';
                cmpt++;
			}
		} else if ((texte[i] >= '0') && (texte[i]<='9')){
			c = texte[i] - '0';
			c += (clef[cmpt % strlen(clef)] - 'a');
			c = c % 10;
			texte[i] = c + '0';
            cmpt++;
		}
    }
    free(clef);
}

void vigenere_dechiffr(char texte[]){
    removeSpace();
    char* clef;
    int cmpt = 0;
    int i;
    char c;
    clef = (char*) malloc ((strlen(pOptionsCrypto.clef)+1) * sizeof(char));
    strcpy(clef, pOptionsCrypto.clef);
    const int lenKey = strlen(clef);
    for (i=0; i<=strlen(texte); i++) {
        if ((texte[i] >= 'A' && texte[i]<= 'Z') || (texte[i] >= 'a' && texte[i]<= 'z')) {
			if (texte[i] >= 'a') {
				c = texte[i] - 'a';
				c -= (clef[cmpt % strlen(clef)] - 'a');
				c = c % 26;
                if (c<0) {
					c += 26;
				}
				texte[i] = c + 'a';
                cmpt++;
			} else {
				c = texte[i] - 'A';
				c -= (clef[cmpt % strlen(clef)] - 'a');
				c = c % 26;
                if (c<0) {
					c += 26;
				}
				texte[i] = c + 'A';
                cmpt++;
			}
		} else if ((texte[i] >= '0') && (texte[i]<='9')){
			c = texte[i] - '0';
			c -= (clef[cmpt % strlen(clef)] - 'a');
			c = c % 10;
            if (c<0) {
                c += 10;
            }
			texte[i] = c + '0';
            cmpt++;
		}
    }
    free(clef);
}

void removeSpace() {
    char* clef;
    clef = (char*) malloc (strlen(pOptionsCrypto.clef)+1);
    
    strcpy(clef, pOptionsCrypto.clef);
    int i;
    int count = 0;
    for (i = 0; clef[i]; i++)
        if (clef[i] != ' ')
            clef[count++] = clef[i];
    clef[count] = '\0';
    pOptionsCrypto.clef = (char*) realloc (pOptionsCrypto.clef, (strlen(clef)+1));
    strcpy(pOptionsCrypto.clef,clef);
    free(clef);
}
