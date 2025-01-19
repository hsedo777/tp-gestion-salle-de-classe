#include "numbers.h"

/**
* Lire un nombre d'un type quelconque.
* @param value
*			l'adresse où écrire le nombre. Doit être déjà allouée.
* @param digits
*			liste, sous-forme de chaîne de caractères, des chiffres
*			de la base de lecture du nombre. Exemples :
*				- "0123456789+" pour les entiers positif
*				- "0123456789.+-" pour le `double` ou le `float`
*				- "0123456789aAbBcCdDeEfF" pour l'hexadéximal
* @param format
*			le format de nombre à lire. Exemples :
*				- "%d" ou "%ld" pour les entiers
*				- "%f" ou "%lf" pour les flottants
*				- "%x" ou "%lx" pour l'hexadécimal
* @param source
*			le fichier à partir duquel extraire la donnée.
* @param cleanBuffer
*			utilisé comme un booléen pour spécifier la vidange ou
*			non du buffer après lecture du nombre
* @return `READ_SUCCESS` si la lecture a réussi, `READ_FAILURE` sinon.
*/
int readNumber(void* value, char * digits, char *format, FILE *source, int cleanBuffer){
	if (value == NULL){
		printf("The pointer on which to store the value to read is unusable.");
		return READ_FAILURE;
	}
	char* text = readString(-1, source, cleanBuffer);
	int state = READ_FAILURE;
	if (text != NULL){
		char *start = strpbrk(text, digits);
		if (start != NULL){
			int r = sscanf(start, format, value);
			if (r == 1){
				//Success reading of one value
				state = READ_SUCCESS;
			}
			/*if(r == EOF){
				printf("\nEOF\n");
			} else {
				printf("\nr=%d\n", r);
			}*/
		}
		free(text);
	}
	return state;
}

/**
* Reads `int` value.
* @param digits			might be `"0123456789"` or `"-0123456789"`. The value
*						is matched again function `strpbrk` to determine the
*						first occurence of the first digits
* @param source			the input stream from wich to read/extract data.
* @param cleanBuffer	specify buffer cleaning or not.
*/
int* readInt(char* digits, FILE* source, int cleanBuffer){
	int *value = (int*) calloc(1, sizeof(int));
	int r = readNumber(value, digits, "%d", source, cleanBuffer);
	if (r == READ_FAILURE){
		free(value);
		value = NULL;
	}
	return value;
}

int* readNotSignedInt(FILE* source, int cleanBuffer){
	return readInt("+0123456789", source, cleanBuffer);
}

int* readSignedInt(FILE* source, int cleanBuffer){
	return readInt("-+0123456789", source, cleanBuffer);
}

double* readDouble(FILE* source, int cleanBuffer){
	double *value = (double*) calloc(1, sizeof(double));
	int r = readNumber(value, "0123456789.+-", "%lf", source, cleanBuffer);
	if (r == READ_FAILURE){
		free(value);
		value = NULL;
	}
	return value;
}

int countDigits(int value, unsigned int base){
	int occur = 0;
	if (base >= 2){
		do {
			value /= base;
			occur++;
		} while (value != 0);
	}
	return occur;
}
