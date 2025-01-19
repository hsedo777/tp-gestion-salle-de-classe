#include "student.h"

static int FN_MAX_LENGTH = 0;
static int LN_MAX_LENGTH = 0;
static int AG_MAX_LENGTH = 0;

void updateLength(char* text, int* address){
	int len = strlen(text);
	if (len > *address){
		*address = len;
	}
}


void freeIfDef(void * p){
	if (p != NULL){
		free(p);
	}
}

/**
* Lecture d'un étudiant.
* @param old
			si défini, alors il s'agit d'une
*			mise à jour des informations d'un
*			étudiant
* @return	en cas de création, un pointeur
*			sur l'étudiant nouvellement créé,
*			sinon le pointeur sur l'étudiant
*			modifié
*/
student scanStudent(student old){
	char sex, *text = NULL, *toFree = NULL;
	int *age = NULL, *id = NULL, show = 0, tmp = 0;
	student st = NULL;
	if (old != NULL){//old->
		//Process update
		printf("\nMise à jour des informations de l'étudiant de matricule %d\n", old->id);
		show = 1;
		st = old;
	} else {
		//New student
		st = (student) malloc(sizeof(struct student));
		if (st == NULL){
			printf("\nEchec d'allocation de memoire\n");
			return st;
		}
	}
	do {
		printf("Quel est le nom");
		if (show){
			printf("(ancien=%s)", st->lastname);
			toFree = st->lastname;
		}
		printf(" : ");
		text = readString(0, stdin, 0);
	} while (text == NULL || text[0] == '\0');
	st->lastname = text;
	updateLength(text, &LN_MAX_LENGTH);
	freeIfDef(toFree);
	text = NULL;
	do {
		printf("Quel est le prenom");
		if (show){
			printf("(ancien=%s)", st->firstname);
			toFree = st->firstname;
		}
		printf(" : ");
		text = readString(0, stdin, 0);
	} while (text == NULL || text[0] == '\0');
	st->firstname = text;
	updateLength(text, &FN_MAX_LENGTH);
	freeIfDef(toFree);
	text = NULL;
	do {
		printf("Quel est le sexe(saisir M ou F)");
		if (show){
			printf("(ancien=%c)", st->sex);
		}
		printf(" : ");
		//Here, we read all characters to ensure buffer cleaning
		text = readStringAsLineFromStd(1);
		if (text != NULL){
			sex = text[0];
			free(text);
		} else {
			sex = '\0';
		}
	} while (sex != 'M' && sex != 'F');
	st->sex = sex;
	do {
		printf("Quel est l'age");
		if (show){
			printf("(ancien=%d)", st->age);
		}
		printf(" : ");
		age = readNotSignedInt(stdin, 1);
	} while (age == NULL || *age <= 0);
	st->age = *age;
	tmp = countDigits(*age, 10);
	AG_MAX_LENGTH = (tmp < AG_MAX_LENGTH) ? AG_MAX_LENGTH : tmp;
	free(age);
	do {
		printf("Quel est le matricule, un entier naturel non null et <= %d", MAX_ID);
		if (show){
			printf("(ancien=%d)", st->id);
		}
		printf(" : ");
		id = readNotSignedInt(stdin, 1);
	} while (id == NULL || *id <= 0 || *id > MAX_ID);
	st->id = *id;
	free(id);
	return st;
}

void printStudent(student st){
	if (st == NULL){
		return;
	}
	printf("{id=%d, %s, %s, %d, %c}", st->id, st->lastname,
		st->firstname, st->age, st->sex);
	return;
}

void presentStudent(student st){
	if (st == NULL){
		return;
	}
	printf("\nMatricule : %d", st->id);
	printf("\nNom : %s", st->lastname);
	printf("\nPrenom : %s", st->firstname);
	printf("\nSex : %c", st->sex);
	printf("\nAge : %d\n", st->age);
	return;
}

void freeStudent(student st){
	if (st != NULL){
		free(st->firstname);
		free(st->lastname);
		free(st);
	}
	return;
}
