#ifndef COURSE_H_INCLUDED
#define COURSE_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mystring.h"

static int CD_MAX_LENGTH;
static int LA_MAX_LENGTH;
static int TE_MAX_LENGTH;

struct course{
	char* code;
	char* label;
	char* teacher;
};
typedef struct course* course;

course scanCourse(course);
void printCourse(course);
void presentCourse(course);
void freeCourse(course);
course findCourseByCode(course[], char*, int);
void updateLength2(char*, int*);


#endif // COURSE_H_INCLUDED
