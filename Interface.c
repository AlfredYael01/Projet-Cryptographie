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
*  Nom du fichier : Interface.c                                                   *
*                                                                             *
******************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Interface.h"
#include <ctype.h>
#include <math.h>
optionsCrypto pOptionsCrypto;

void affichage(char option, char* message){

       if (option == 'c'){
       printf("\n===========================\n");
       printf("> Votre message chiffré est: %s  \n",message);
       printf("===========================\n");
	   	free(pOptionsCrypto.texte);
		free(pOptionsCrypto.clef);
       exit(1);
       }
       if (option == 'd'){
       printf("\n===========================\n");
       printf("> Votre message déchiffré est: %s  \n",message);
       printf("===========================\n");
	   	free(pOptionsCrypto.texte);
		free(pOptionsCrypto.clef);
       exit(1);
       }
       if (option == 'r'){
		  printf("Erreur:\n\t %s  \n",message);
		  exit(EXIT_FAILURE);
       }
       if (option == 'h') {
			printf("Displaying help :\n"
					"Syntaxe\n"
					"\t./crypto [option] [input] [clef]\n"
					"\t./crypto [option] [fileIn/Out] [clef]\n"
					"\nOptions\n"
					"\t Crypt Choice :\n"
					"\t\t-c : Utiliser le chiffrement Cesar (defaut)\n"
					"\t\t-v : Utiliser le chiffrement Vigenere\n"
					"\t Input/Output mode Choice :\n"
					"\t\t-s : Utiliser le terminal comme entrée et sortie (defaut)\n"
					"\t\t-f : Utiliser le fichier spécifier comme entrée et sortie\n"
					"\t Mode Choice :\n"
					"\t\t-e : Encrypter (defaut)\n"
					"\t\t-d : Decrypter\n"
					"\nCesar\n"
					"\tLa clef du chiffrement cesar est un décalage donné en chiffre.\n"
					"\tSi aucune clef n'est donnée, la clef sera par defaut 1.\n"
					"\nVigenere\n"
					"\tLa clef du chiffrement vigenere une chaine de caractère obligatoire.\n"
					"\nCaractère spéciaux\n"
					"\tLe texte ne peut etre composé que de lettres, de chiffres, de virgules et de points.\n"
					"\tLes accents les plus utilisé (entre 192 et 255 en ascii) seront convertis.\n"
					"\tTout autre caractères provoqueront une erreur du programme.\n"
					"\nChaine de caractère\n"
					"\tSi des chaines de caractères sont entrées pour le texte ou la clef de vigenaire, elles doivent etre entourée de \"\"");
			exit(1);
       }
		if (option == 'f'){
			printf("\n===========================\n");
			printf("> Fichier %s est chiffre  \n",pOptionsCrypto.filename);
			printf("===========================\n");
			free(pOptionsCrypto.filename);
			exit(1);
		}
		if (option == 'y'){
			printf("\n===========================\n");
			printf("> Fichier %s est dechiffre  \n",pOptionsCrypto.filename);
			printf("===========================\n");
			free(pOptionsCrypto.filename);
			exit(1);
		}
}

void EcrireFic(char* texte) {
    FILE* fic = fopen(pOptionsCrypto.filename, "w");
    if (fic == NULL) {
    	affichage('r',"Erreur a l'ouverture du fichier texte \n");
   	}
	fwrite(texte,1,strlen(texte), fic);
	fclose(fic);
}

void LireFic(char* nomFic){
	char* TabLigne;
	char* Ligne;
	FILE* fic;
	int count = 0;
	fic = fopen(nomFic, "r");
	if (fic == NULL){
		affichage('r',"Erreur a l'ouverture du fichier texte \n");
	}
	while(fgetc(fic) != EOF)
    	count ++; /* incrémentation du compteur */
	fclose(fic);
	fic = fopen(nomFic, "r");
	TabLigne = (char *) malloc (count+1);
	Ligne = (char *) malloc (count+1);
	strcpy(TabLigne,"");
	while (fgets(Ligne, count, fic) != NULL) {
		strcat(TabLigne,Ligne);
	}

	fclose(fic);
	pOptionsCrypto.texte = (char*) malloc (strlen(TabLigne)+1);
	strcpy(pOptionsCrypto.texte, TabLigne);
	free(TabLigne);
	free(Ligne);
}

void getOption(char* argv[],int argc) {
	int useFile; //Default Value 0 = using stream input
	int useCrypt; //0 Default value = Cesar Code
	char* clef;
	char* texte;
	int chiffrer = 0;
	char* filename;

	char* option;
	char* tempKey;
	int i,cmptOpt;
	char* endCI;
	option = (char *) malloc (5);
	cmptOpt = 0;
	strcpy(option,"");
	for (i=0; i<argc;i++) {
		if (argv[i][0] == '-') {
			cmptOpt++;
			strcat(option,argv[i]);
		}
	}
	//help
	if (strstr(option,"h")){
		affichage('h',"");
	}
	//Output input
	if (strchr(option,'f') && strchr(option,'s')) {
		free(option);
		affichage('r',"Option f et s utilisé en meme temps");
	}
	if (strchr(option,'f')) {
		useFile=1;
	} else {
		useFile=0;
	}
	//Crypto Option
	if (strchr(option,'c') && strchr(option,'v')) {
		free(option);
		affichage('r', "Option c et v utilisé en meme temps");
	}
	if (strchr(option,'v')) {
			useCrypt=1;
	}else {
			useCrypt=0;
	}
	//Chiffrer Option
		if (strchr(option,'e') && strchr(option,'d')) {
			free(option);
			affichage('r', "Option e et d utilisé en meme temps");
		}
		if (strchr(option,'d')) {
			chiffrer=0;
		}else {
			chiffrer=1;
		}
	//Key option
	if (argc < 2){
		free(option);
		affichage('r', "Pas assez d'arguments, utilisez -h pour avoir l'aide");
	}

	if (argc <= 3 && useCrypt==1){
		free(option);
		affichage('r', "Le chiffrement vigenere necessite une clef");
	} 
	if (argc == cmptOpt+3){
		if (useCrypt==0) {

			tempKey = (char *) malloc (strlen(argv[cmptOpt+2])+1);
			strcpy(tempKey, argv[cmptOpt+2]);
			if (((strtol(tempKey, &endCI, 10)%26) >= 0) && ((strtol(tempKey, &endCI, 10)%26) <= 27)) {
				if (*endCI == '\0') {
					tempKey = realloc (tempKey, (int)(ceil(log10(strtol(tempKey, &endCI, 10)%26)))+1);
					sprintf(tempKey, "%d", strtol(tempKey, &endCI, 10)%26);
					clef = (char *) malloc (strlen(tempKey)+1);
					strcpy(clef,tempKey);
				} else {
					free(option);
					free(tempKey);
					affichage('r', "La clef du chiffrement cesar est un chiffre");
				}
			} else {
				free(option);
				free(tempKey);
				affichage('r', "La clef du chiffrement cesar est un chiffre");
			}
		} else if (useCrypt==1) {
			tempKey = (char *) malloc (strlen(argv[cmptOpt+2])+1);
			strcpy(tempKey, argv[cmptOpt+2]);
			for (int i = 0; tempKey[i] != '\0'; i++) {
				if (!isalpha(tempKey[i]) && tempKey[i] != '\n' && tempKey[i] != 32) {
					free(option);
					free(tempKey);
					affichage('r',"La clef de chiffrement necessite d etre en lettres");
				}
			}
		}
		if (useCrypt == 1) {
			clef = (char *) malloc (strlen(argv[cmptOpt+2])+1);
			strcpy(clef,argv[cmptOpt+2]);
		}
	} else {
		clef = (char *) malloc (2 * sizeof(char));
		strcpy(clef,"1");
	}
	if (useCrypt == 1) {
		for (int i = 0; clef[i] != '\0'; i++)
			clef[i] = tolower(clef[i]);
	}
	if (useFile == 0) {
		texte = (char *) malloc (strlen(argv[cmptOpt+1])+1);
		strcpy(texte,argv[cmptOpt+1]);
		pOptionsCrypto.texte = (char*) malloc (strlen(texte)+1);
		strcpy(pOptionsCrypto.texte,texte);
	} else {
		filename = (char *) malloc (strlen(argv[cmptOpt+1])+1);
		strcpy(filename, argv[cmptOpt+1]);
		LireFic(argv[cmptOpt+1]);
	}
	pOptionsCrypto.clef = (char*) malloc (strlen(clef)+1);
	strcpy(pOptionsCrypto.clef, clef);
	pOptionsCrypto.useFile = useFile;
	pOptionsCrypto.useCrypt = useCrypt;
	pOptionsCrypto.chiffrer = chiffrer;
	if (useFile == 1) {
		pOptionsCrypto.filename = (char*) malloc (strlen(filename)+1);
		strcpy(pOptionsCrypto.filename,filename);
		free(filename);
	} else {
		free(texte);
	}
	free(option);
	free(tempKey);
	free(clef);
	
}


