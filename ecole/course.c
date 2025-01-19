#include "course.h"

static int CD_MAX_LENGTH = 0;
static int LA_MAX_LENGTH = 0;
static int TE_MAX_LENGTH = 0;

void updateLength2(char* text, int* address){
	int len = strlen(text);
	if (len > *address){
		*address = len;
	}
}

/**
* Lecture d'une matière.
* @param old	si défini, alors il s'agit d'une
*		mise à jour des informations d'une
*		matière
* @return	en cas de création, un pointeur
*			sur la matière nouvellement créée,
*			sinon le pointeur sur la matière
*			modifiée
*/
course scanCourse(course old){
	char *text = NULL;
	int show = 0;
	course crs = NULL;
	if (old != NULL){//old->
		//Process update
		printf("\nMise à jour des informations de la matiere ayant pour code : %s\n", old->code);
		show = 1;
		crs = old;
	} else {
		//New course
		crs = (course) malloc(sizeof(struct course));
		if (crs == NULL){
			printf("\nEchec d'allocation de memoire\n");
			return crs;
		}
	}
	do {
		printf("Donner le code de la matiere");
		if (show){
			printf("(ancien=%s)", crs->code);
		}
		printf(" : ");
		text = readString(0, stdin, 0);
	} while (text == NULL || text[0] == '\0');
	crs->code = text;
	updateLength2(text, &CD_MAX_LENGTH);
	text = NULL;
	do {
		printf("Donner le libelle de la matiere");
		if (show){
			printf("(ancien=%s)", crs->label);
		}
		printf(" : ");
		text = readString(0, stdin, 0);
	} while (text == NULL || text[0] == '\0');
	crs->label = text;
	updateLength2(text, &LA_MAX_LENGTH);
	text = NULL;
	do {
		printf("Veuiller renseigner le nom complet du responsable de la matiere");
		if (show){
			printf("(ancien=%s)", crs->teacher);
		}
		printf(" : ");
		//Here, we read all characters to ensure buffer cleaning
		text = readString(0, stdin, 0);
	} while (text == NULL || text[0] == '\0');
	crs->teacher = text;
	updateLength2(text, &TE_MAX_LENGTH);
	return crs;
}

void printCourse(course crs){
	if (crs == NULL){
		return;
	}
	printf("{code=%s, %s, %s}", crs->code, crs->label, crs->teacher);
	return;
}

void presentCourse(course crs){
	if (crs == NULL){
		return;
	}
	printf("\nCode : %s", crs->code);
	printf("\nLibelle : %s", crs->label);
	printf("\nEnseignant : %s\n", crs->teacher);
	return;
}

void freeCourse(course crs){
	if (crs != NULL){
		free(crs->code);
		free(crs->label);
		free(crs->teacher);
		free(crs);
	}
	return;
}

course findCourseByCode(course courses[], char* code, int size){
	if (code == NULL || size <= 0){
		return NULL;
	}
	int i = 0, found = 0;
	while (i < size && found == 0){
		found = strcmp(code, courses[i]->code) == 0;
		i++;
	}
	return ((found == 0) ? NULL : courses[i - 1]);
}
