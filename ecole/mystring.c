#include "mystring.h"

/**
* Lire une chaîne de caractères du flux `source`.
* @param maxLetters
*				si supérieur strictement à 0, traité
*				le nombre maximal de caractères à
*				lire. Si la valeur est inférieure ou
*				égale à 0, alors tout le texte est lu
*				jusqu'au retour à la ligne le plus
*				proche.
* @param source
*				le fichier duquel est lu le texte.
* @param cleanBuffer
*				exploité comme un booléen permettant
*				de demander la vidange du buffer(ou
*				ligne en cours de lecture) après
*				lecture de la chaîne de caractères.
* @return		un pointeur sur la chaîne lue.
*/
char* readString(int maxLetters, FILE* source, int cleanBuffer){
	char* str = NULL;
	if (source == NULL){
		printf("\nLa source su texte est indefinie!\n");
		return NULL;
	}
	if (maxLetters > 0){
		str = (char *) malloc(maxLetters * sizeof(char));
		if (str == NULL){
			printf("\nImpossible d'allouer la memoire necessaire !\n");
			return NULL;
		}
		fgets(str, maxLetters, source);
	} else {
		char buffer[BUFFER_SIZE];
		int size = 0, rsize, capacity = 0;
		while (fgets(buffer, BUFFER_SIZE, source) != NULL){
			rsize = strlen(buffer);
			if (rsize + size + 1 > capacity){
				capacity = (rsize + size + 1) * 2;
				char *new_value = realloc(str, capacity);
				if (new_value == NULL){
					printf("\nEchec d'allocation de la memoire!\n");
					free(str);
					return NULL;
				}
				str = new_value;
			}
			strcpy(str + size, buffer);
			size += rsize;
			//Ensure there is at least one character remaining
			if (buffer[rsize - 1] == '\n'){
				break;
			}
		}
	}
	if (str != NULL){
		//Try to remove the line break
		char *p = strpbrk(str, "\r\n");
		if (p != NULL){
			//All characters are readed.
			*p = '\0';
		} else {
			//There is at least one character
			//still in the buffer
			if (cleanBuffer != 0){
				char c;
				while ((c = fgetc(source)) != EOF && c != '\n');
			}
		}
	}
	return (str);
}

char* readStringFromStd(int maxLetters, int cleanBuffer){
	return readString(maxLetters, stdin, cleanBuffer);
}

char* readStringAsLine(FILE* source, int cleanBuffer){
	return readString(-1, source, cleanBuffer);
}

char* readStringAsLineFromStd(int cleanBuffer){
	return readStringAsLine(stdin, cleanBuffer);
}
