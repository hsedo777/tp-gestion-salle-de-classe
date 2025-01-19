#include "note.h"

note scanNote(student stud, course crs){
	if (stud == NULL || crs == NULL){
		return NULL;
	}
	note nte = (note) malloc(sizeof(struct note));
	nte->stud = stud;
	nte->crs = crs;
	alterNote(nte, 0);
	return nte;
}

double readNoteValue(int showOld, double old, const char* prompt){
	double *value = NULL;
	do {
		printf("%s", prompt);
		if (showOld){
			printf("(ancienne=%lf)", old);
		}
		printf(" : ");
		value = readDouble(stdin, 1);
	} while (value == NULL || *value < 0. || *value > NOTE_MAX);
	return *value;
}

void alterNote(note nte, int showOld){
	if (nte == NULL || nte->stud == NULL || nte->crs == NULL){
		return;
	}
	printf("\nLecture des notes de l'etudiant ");
	printStudent(nte->stud);
	printf(" dans la matiere ");
	printCourse(nte->crs);
	printf(", la note etant comprise entre 0.0 et %.2lf, : \n", NOTE_MAX);
	double first = nte->first, second = nte->second;
	nte->first = readNoteValue(showOld, first, "Premiere note");
	nte->second = readNoteValue(showOld, second, "Deuxieme note");
	nte->avg = (nte->first + nte->second)/2;
	return;
}

void freeNote(note nte){
	if (nte != NULL){
		//Keep student and course alive, i.e. do not delete/free them
		nte->crs = NULL;
		nte->stud = NULL;
		free(nte);
	}
	return;
}