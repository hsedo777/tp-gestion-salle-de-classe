#ifndef MYSTRING_H_INCLUDED
#define MYSTRING_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 10

char* readString(int, FILE*, int);
char* readStringAsLine(FILE*, int);
char* readStringFromStd(int, int);
char* readStringAsLineFromStd(int);

#endif // MYSTRING_H_INCLUDED
