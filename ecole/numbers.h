#ifndef NUMBERS_H_INCLUDED
#define NUMBERS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "mystring.h"

#define READ_SUCCESS 1
#define READ_FAILURE 0

int readNumber(void*, char*, char*, FILE*, int);
int* readInt(char*, FILE*, int);
int* readNotSignedInt(FILE*, int);
int* readSignedInt(FILE*, int);

double* readDouble(FILE*, int);

int countDigits(int, unsigned int);

#endif // NUMBERS_H_INCLUDED
