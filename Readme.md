# Crypto
***

Dans le cadre d’un projet fait à l’iut, nous devions développer un projet en C.

Dans le but de développer une application de protection de textes 
confidentiels, nous concevons un outil permettant le chiffrement de messages.
Le schéma ci-dessous montre l’enchaînement des traitements initiaux à appliquer afin
de chiffrer un message et afficher le résultat. Le schéma montre
également la procédure inverse : déchiffrer un message.


# Créateurs
Ce projet a été réalisé par AL RIYAMI Ismail, ALFRED Yaël, BOUNOUA Yahya et COMBET Florent.

# Sommaire


- [Usage](#usage)
  - [Makefile](#makefile)
  - [Syntaxe](#syntaxe)
  - [Exemple d'utilisation](#exemple-d'utilisation)
- [Documentation](#documentation)
  - [Variable globale](#variable-globale)
    - [pOptionsCrypto](#poptionscrypto)
  - [TransformationT.c](#transformationtc)
    - [VerifierConvertir()](#verifierconvertir)
  - [cesar.c](#cesarc)
    - [CésarCrypt()](#césarcrypt)
    - [CésarDecrypt()](#césardecrypt)
  - [Vigenere.c](#vigenerec)
    - [vigenere_chiff()](#vigenere_chiff)
    - [vigenere_dechiffr()](#vigenere_dechiffr)
    - [removeSpace()](#removespace)
  - [Interface.c](#interfacec)
    - [Affichage()](#affichage)
    - [EcrireFic()](#ecrirefic)
    - [LireFic()](#lirefic)
    - [getOption()](#getoption)

# Usage
## Makefile
Hors problème particulier, nous conseillons de lancer le Makefile fourni, avec la règle "all" avant la première utilisation.

## Syntaxe
```Shell
./crypto [Options] [Texte] [Clé]
./crypto [Options] [Fichier.txt] [Clé]
```
L'ordre des options n'a pas d'importance.
Les différentes options sont : 
* -h affiche l'aide
* -e pour crypter
* -d pour décrypter
* -c pour utiliser cesar
* -v pour utiliser vigenere
* -f pour crypter un fichier
* -s pour crypter du texte entré en argument

## Exemple d'utilisation
```Shell
Cryptage cesar, clé de 3
./crypto "texte à coder" 3

Cryptage Vigénere, clé abc
./crypto -v "texte à coder" abc

Decryptage fichier texte.txt avec vigénere, clé abc
./crypto -dvf texte.txt abc
./crypto -d -v -f texte.txt abc 
```

# Documentation
## Variable globale
### pOptionsCrypto
Collection globale initialisée par getOption() comportant les paramètres entrés par l'utilisateur. C'est une collection de type pOptionsCrypto_t défini par :
```C
struct optionsCrypto_t {
	int useFile; // à 1 si on utilise un fichier, 0 sinon
	int useCrypt; // à 1 si on utilise vigenere, sinon 0 pour cesar
	int chiffrer; // à 1 si on veut chiffrer, 0 sinon pour dechiffrer
	char* filename; // String contenant le nom du fichier à encrypter/decrypter
	char* texte; // String contenant le texte à encrypter/decrypterr
	char* clef; // String contenant la clef
	int isAlphaNum; // à 1 si le texte contient bien uniquement des valeurs acceptées ou des caractères alphanumériques
};
```
***
## TransformationT.c
### VerifierConvertir()
La fonction vérifie la validitée du texte entré. Convertit les accents si ils sont présent et termine le programme si un caractère non alphanumérique autre que le point, la virgule ou l'espace est présent.
La fonction récupère son texte de la variable globale et la modifiera (ou non) avant de l'y remettre.

```C
void VerifierConvertir();
```

Entrée : pOptionsCrypto.texte
Sortie : pOptionsCrypto.texte, pOptionsCrypto.isAlphaNum

La fonction fait afficher une erreur si le texte contient des valeurs autres que celles acceptées.
***
## cesar.c
### CésarCrypt()
Le chiffrement cesar est un chiffrement par substitution, ou chaque lettre est remplacée par la nième suivante ou n est la clef comprise entre 0 et 26. Si la lettre dépasse 'z', elle continue son décalage depuis 'a'.

```C
void CesarCrypt(char str[], int decalage);
```

Entrée : char str[], int decalage
sortie : char str[]

### CésarDecrypt()
Dechiffrement par cesar suivant le meme principe que le chiffrement. Chaque lettre est remplacée par la nième précédente ou n est la clef comprise entre 0 et 26. Si lors de son décalage la lettre doit dépasser 'a', elle continue à 'z' 

```C
void CesarDecrypt(char str[], int decalage);
```

Entrée : char str[], int decalage
sortie : char str[]
***
## Vigenere.c
### vigenere_chiff()
La fonction chiffre le message en utilisant le principe de Vigenere. Le chiffrement consiste à additioner la clef au texte clair lettre par lettre. Le resultat est donné modulo 26 (ou modulo 10 si on chiffre des nombres). Pour faire correspondre la longueur du texte à la clé, celle-ci est répétée à l'infini.

```C
void vigenere_chiff(char texte[]);
```

Entrée : char texte[], pOptionsCrypto.clef
sortie : char texte[]

### vigenere_dechiffr()
La fonction déchiffre le message en utilisant le principe de Vigenere. Le déchiffrement consiste à soustraire la clef au texte chiffré lettre par lettre. Le resultat est donné modulo 26 (ou modulo 10 si on déchiffre des nombres). Pour faire correspondre la longueur du texte à la clé, celle-ci est répétée à l'infini.

```C
void vigenere_dechiffr(char texte[]);
```

Entrée : char texte[], pOptionsCrypto.clef
sortie : char texte[]

### removeSpace()
La fonction enleve tout les espaces de la clef entrée. Cela est utile si l'algorithme de chiffrement utilisé est vigenere et que la clef est une phrase.

```C
void removeSpace();
```

Entrée : pOptionsCrypto.clef
Sortie : pOptionsCrypto.clef
***
## Interface.c
### Affichage()
La fonction est la seule qui affiche du texte à l'utilisateur. Elle possède 6 cas d'utilisation qui s'affichent en fonction de l'option donnée au programme: 
* 'c' Message chiffré
* 'd' Message déchiffré
* 'f' Fichier chiffré
* 'y' Fichier déchiffré
* 'r' Erreur
* 'h' Aide

```C
void affichage(char option, char* message);
```

Entrée : char Option, char* message, char* pOptionsCrypto.filename

### EcrireFic()
Permet d'écraser le fichier d'entrée avec le texte encodé ou décodé

```C
void EcrireFic(char* texte);
```

Entrée: char* texte, pOptionsCrypto.filename

### LireFic()
Permet de lire le fichier spécifié et de stocker son texte dans la variable pOptionsCrypto.texte

```C
void LireFic(char* nomFic);
```

Entrée: char* nomFic
Sortie: pOptionsCrypto.texte

### getOption()
Lecture et traitement des arguments entrés par l'utilisateur.
Le sous-programme renvoie une erreur si :
* Deux arguments incompatibles sont entrés
* Il n'y a pas assez d'arguments
* Si la clef rentrée pour le chiffrement cesar n'est pas en chiffre
* Si la clef rentrée pour le chiffrement vigénere n'est pas en lettre
* Si il n'y a pas de clef pour le chiffrement vigénere

Par défaut, si aucune option n'est rentrée le programme va chiffrer le texte rentré avec cesar.
La clef pour cesar par defaut est 1.

```C
void getOption(char* argv[],int argc);
```

Entrée : char* argv[], int argc
Sortie : pOptionsCrypto.useFile, pOptionsCrypto.useCrypt, pOptionsCrypto.chiffrer, pOptionsCrypto.clef, pOptionsCrypto.texte, pOptionsCrypto.filename



