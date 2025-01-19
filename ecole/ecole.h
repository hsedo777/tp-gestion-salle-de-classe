#ifndef ECOLE_H_INCLUDED
#define ECOLE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include "course.h"
#include "student.h"
#include "note.h"

#define COURSE_NUMBER 2

typedef struct studentnode * node;
struct studentnode {
	student stud;
	note notes[COURSE_NUMBER];
	double avg;
	node next;
};

struct classroom {
	node shead;
	course courses[COURSE_NUMBER];
	int coursesDefined : 1;
	int notesDefined : 1;
	int totalStdNumber;
};
typedef struct classroom * classroom;

classroom initClassroom(int);
student addNewStudent(classroom);
node findByStudentId(classroom, int);
void findStudentInfo(classroom);
void scanStudents(classroom, int);
void printStudents(classroom);
void exchange(classroom, node, node, node, node);
void sortStudents(classroom);
void scanCourses(classroom);
void printCourses(classroom);
int scanStudentNotes(node, course[], int);
int scanNotes(classroom);
void printNotes(classroom);
void freeClassroom(classroom);

int menu(char*);
char* applyChoice(int, classroom);

void repeatText(char*, int);

#endif // ECOLE_H_INCLUDED
