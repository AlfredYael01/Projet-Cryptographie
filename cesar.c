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
*  Nom du fichier : cesar.c                                                   *
*                                                                             *
******************************************************************************/


#include <stdio.h>
#include "cesar.h"

void CesarCrypt(char str[], int decalage) {
  	int i = 0;
	char c;
  	while (str[i] != '\0') {
		if ((str[i] >= 'A' && str[i]<= 'Z') || (str[i] >= 'a' && str[i]<= 'z')) {
			if (str[i] >= 'a') {
				c = str[i] - 'a';
				c += decalage;
				c = c % 26;
				str[i] = c + 'a';
			} else {
				c = str[i] - 'A';
				c += decalage;
				c = c % 26;
				str[i] = c + 'A';
			}
		} else if ((str[i] >= '0') && (str[i]<='9')){
			c = str[i] - '0';
			c += decalage;
			c = c % 10;
			str[i] = c + '0';
		}
		i++;
	}

}

void CesarDecrypt(char str[], int decalage) {
  	int i = 0;
	char c ;
	while (str[i] != '\0') {
		if ((str[i] >= 'A' && str[i]<= 'Z') || (str[i] >= 'a' && str[i]<= 'z')) {
			if (str[i] >= 'a') {
				c = str[i] - 'a';
				c -= decalage;
				c = c % 26;
				if (c<0) {
					c += 26;
				}
				str[i] = c + 'a';
			} else {
				c = str[i] - 'A';
				c -= decalage;
				c = c % 26;
				if (c<0) {
					c += 26;
				}
				str[i] = c + 'A';
			}
		} else if ((str[i] >= '0') && (str[i]<='9')){
			c = str[i] - '0';
			c -= decalage;
			c = c % 10;
			if (c<0) {
				c += 10;
			}
			str[i] = c + '0';
		}
		i++;
	}

}
