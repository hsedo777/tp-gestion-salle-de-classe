#ifndef STUDENT_H_INCLUDED
#define STUDENT_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "mystring.h"
#include "numbers.h"

#define MAX_ID 99999999

static int FN_MAX_LENGTH;
static int LN_MAX_LENGTH;
static int AG_MAX_LENGTH;

struct student{
	char* firstname;
	char* lastname;
	int id;//Matricule
	char sex;//'F' ou 'M'
	int age;
};
typedef struct student* student;

void updateLength(char*, int*);
void freeIfDef(void *);

student scanStudent(student);
void printStudent(student);
void presentStudent(student);
void freeStudent(student);

#endif // STUDENT_H_INCLUDED
