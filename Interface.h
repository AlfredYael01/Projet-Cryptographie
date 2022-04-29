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
*  Nom du fichier : Interface.h                                                   *
*                                                                             *
******************************************************************************/


struct optionsCrypto_t {
	int useFile;
	int useCrypt;
	int chiffrer;
	char* filename;
	char* texte;
	char* clef;
	int isAlphaNum;

};
typedef struct optionsCrypto_t optionsCrypto;
extern optionsCrypto pOptionsCrypto;

void affichage(char option, char* message);
void EcrireFic(char* texte);
void LireFic(char* nomFic);
void getOption(char* argv[],int argc);
