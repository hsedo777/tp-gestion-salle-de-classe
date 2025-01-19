#ifndef NOTE_H_INCLUDED
#define NOTE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "mystring.h"
#include "course.h"
#include "student.h"

#define NOTE_MAX 20.


struct note{
	student stud;
	course crs;
	double first;
	double second;
	double avg;
};
typedef struct note* note;

double readNoteValue(int, double, const char*);
note scanNote(student, course);
void alterNote(note, int);
void freeNote(note);

#endif // NOTE_H_INCLUDED
