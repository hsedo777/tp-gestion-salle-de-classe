#include "ecole.h"

node findByStudentId(classroom room, int id){
	node nd = NULL;
	if (room != NULL){
		nd = room->shead;
		while (nd != NULL && nd->stud->id != id){
			nd = nd->next;
		}
	}
	return nd;
}

classroom initClassroom(int studentNumber){
	classroom room = NULL;
	room = (classroom) malloc(sizeof(struct classroom));
	if (room == NULL){
		printf("\n\nErreur d'allocation de memoire\n");
		return NULL;
	}
	room->totalStdNumber = 0;
	room->coursesDefined = 0;
	scanStudents(room, studentNumber);
	//scanCourses(room);
	return room;
}

student addNewStudent(classroom room){
	if (room == NULL){
		printf("\nErreur fatale : impossible de trouver la salle de classe!\n");
		return NULL;
	}
	node sn = (node) malloc(sizeof(struct studentnode));
	if (sn == NULL){
		printf("\n\nErreur d'allocation de memoire...\n");
		return NULL;
	}
	student stud = NULL;
	int idDuplicated = 0;
	do {
		stud = scanStudent(stud);
		if (stud != NULL){
			idDuplicated = findByStudentId(room, stud->id) != NULL;
			if (idDuplicated != 0){
				printf("\n\nLe matricule %d est déjà pris, veuillez utiliser un autre.\n\n", stud->id);
			}
		} else {
			free(sn);
			return NULL;
		}
	} while (idDuplicated != 0);
	sn->stud = stud;
	sn->next = room->shead;
	room->shead = sn;
	room->totalStdNumber += 1;
	return stud;
}

void findStudentInfo(classroom room){
	if (room == NULL){
		printf("\nImpossible de trouver la classe.\n");
		return;
	}
	if (room->totalStdNumber <= 0){
		printf("\nLa liste des etudiants est vide.\n");
		return;
	}
	if (room->notesDefined == 0){
		printf("\nVous devez d'abord definir les notes des etudiants.\n");
		return;
	}
	int *id = NULL;
	do {
		printf("Donner le numero matricule de l'etudiant : ");
		id = readNotSignedInt(stdin, 1);
	} while (id == NULL);
	node nde = findByStudentId(room, *id);
	if (nde == NULL){
		printf("\nAucun etudiant n'a pour matricule %d\n", *id);
		return;
	}
	printf("\nLe numero matricule correspond a l'etudiant :");
	presentStudent(nde->stud);
	printf("\nVoici ses notes et moyennes :\n");
	const char *cn = "Matiere", *ntx = "Notes", *avg = "Moyenne",
			*code = "Codification", *label = "Libelle",
			*teacher = "Enseignant", *fnt = "Premiere", *snt = "Deuxieme";
	int cs = strlen(code), as = strlen(avg), fs = strlen(fnt),
			ss = strlen(snt), ls = strlen(label), ts = strlen(teacher),
			cns, ns;
	cs = (cs < CD_MAX_LENGTH) ? CD_MAX_LENGTH : cs;
	ls = (ls < LA_MAX_LENGTH) ? LA_MAX_LENGTH : ls;
	ts = (ts < TE_MAX_LENGTH) ? TE_MAX_LENGTH : ts;
	cns = cs + ls + ts + 2 * 3;
	ns = fs + ss + 1 * 3;

	int rp = 4 + cs + ls + ts + fs + ss + as + 7 * 3;
	repeatText("-", rp);
	printf("\n| No. | %*s | %*s | %*s |\n", -cns, cn, -ns, ntx, -as, avg);
	printf("      ");
	repeatText("-", cns + ns + 2*3 + 1);
	printf("\n|%*s | %*s | %*s | %*s | %*s | %*s | %*s |\n", 4, " ", -cs, code,
			-ls, label, -ts, teacher, -fs, fnt, -ss, snt, -as, " ");
	repeatText("-", rp);
	int i = 0;
	note nte = NULL;
	course crs = NULL;
	for (i = 0; i < COURSE_NUMBER; i++){
		nte = nde->notes[i];
		crs = nte->crs;
		printf("\n|%3d. | %*s | %*s | %*s | %*.2lf | %*.2lf | %*.2lf |\n", i + 1,
			-cs, crs->code, -ls, crs->label, -ts, crs->teacher, fs, nte->first,
			ss, nte->second, as, nte->avg);
		repeatText("-", rp);
	}
	printf("\n\nSa moyenne generale est : %.2lf\n\n", nde->avg);
	return;
}

void scanStudents(classroom room, int number){
	int i;
	for (i = 0; i < number; i++){
		printf("\nLecture des informations de l'etudiant %d\n", i + 1);
		addNewStudent(room);
	}
	return;
}

void repeatText(char* text, int times){
	int i;
	for (i = 0; i < times; i++){
		printf("%s", text);
	}
}

void printStudents(classroom room){
	if (room == NULL){
		return;
	}
	if (room->totalStdNumber <= 0){
		printf("\nLa liste des etudiants est vide.\n");
		return;
	}
	printf("\n\nListe des etudiants de la classe\n");
	char* fn = "Prenom", *ln = "Nom", *ag = "Age", *sex = "Sexe",
			*id = "Matricule";
	int fns = strlen(fn), lns = strlen(ln), ags = strlen(ag),
			ss = strlen(sex), ids = strlen(id);
	fns = (fns < FN_MAX_LENGTH) ? FN_MAX_LENGTH : fns;
	lns = (lns < LN_MAX_LENGTH) ? LN_MAX_LENGTH : lns;
	ags = (lns < AG_MAX_LENGTH) ? AG_MAX_LENGTH : ags;

	int rp = 4 + ids + lns + fns + ags + ss + 3*6;
	repeatText("-", rp);
	printf("\n| No. | %*s | %*s | %*s | %*s | %*s |\n", -ids, id,
			-lns, ln, -fns, fn, -ags, ag, -ss, sex);
	repeatText("-", rp);
	node nde = room->shead;
	int i = 1;
	while (nde != NULL){
		//printStudent(nde->stud);
		printf("\n|%3d. | %*d | %*s | %*s | %*d | %*c |\n", i, -ids,
				nde->stud->id, -lns, nde->stud->lastname, -fns,
				nde->stud->firstname, ags, nde->stud->age, -ss, nde->stud->sex);
		repeatText("-", rp);
		nde = nde->next;
		i++;
	}
	printf("\n");
	return;
}

void exchange(classroom room, node a, node aprev, node b, node bprev){
	node bnext = b->next, anext = a->next;
	if (a == bprev){
		//`a` et `b` sont côte à côte
		b->next = a;
		a->next = bnext;
	} else {
		bprev->next = a;//isolation de `b`
		a->next = bnext;
		b->next = anext;
	}
	if (aprev == NULL){
		//Echange avec la tête de liste
		//`a` est à `room->shead`
		room->shead = b;
	} else {
		//`a` est après la tête de liste
		aprev->next = b;
	}
	return;
}

void sortStudents(classroom room){
	if (room == NULL || room->totalStdNumber <= 1){
		return;
	}
	int cmp;
	node imin = NULL, inode = room->shead, jnode = NULL,
			iprev = NULL, jprev = NULL, imprev = NULL;
	while (inode != NULL && (jnode = inode->next) != NULL){
		imin = inode;
		jprev = inode;
		while (jnode != NULL){
			cmp = strcmp(imin->stud->lastname, jnode->stud->lastname);
			if (cmp == 0){
				cmp = strcmp(imin->stud->firstname, jnode->stud->firstname);
			}
			if (cmp == 0){
				cmp = imin->stud->id - jnode->stud->id;
			}
			if (cmp > 0){
				imprev = jprev;
				imin = jnode;
			}
			jprev = jnode;
			jnode = jnode->next;
		}
		if(imin != inode){
			//exchange
			exchange(room, inode, iprev, imin, imprev);
			//Mise à jour de l'ordre des pointeur dans le parcours
			inode = imin;
		}
		iprev = inode;
		inode = inode->next;
	}
	return;
}

void scanCourses(classroom room){
	if (room == NULL){
		return;
	}
	int i;
	course crs = NULL;
	int idDuplicated = 0;
	for (i = 0; i < COURSE_NUMBER; i++){
		printf("\nLecture des informations de la matiere %d\n", i + 1);
		do {
			crs = scanCourse(crs);
			if (crs != NULL){
				idDuplicated = findCourseByCode(room->courses, crs->code, i) != NULL;
				if (idDuplicated != 0){
					printf("\n\nLe code %s est déjà pris, veuillez utiliser un autre.\n\n", crs->code);
				}
			} else {
				break;
			}
		} while (idDuplicated != 0);
		if (crs == NULL){
			//Retry
			i--;
		} else {
			room->courses[i] = crs;
			crs = NULL;
		}
	}
	room->coursesDefined = 1;
	return;
}

void printCourses(classroom room){
	if (room == NULL){
		return;
	}
	if (room->coursesDefined == 0){
		printf("\nLa liste des matieres n'est pas encore definie. Veuillez d'abord la definir.\n");
		return;
	}
	printf("\n\nVoici la liste des matieres de la classe :\n");
	const char *code = "Codification", *label = "Libelle", *teacher = "Enseignant";
	int cs = strlen(code), ls = strlen(label), ts = strlen(teacher);
	cs = (cs < CD_MAX_LENGTH) ? CD_MAX_LENGTH : cs;
	ls = (ls < LA_MAX_LENGTH) ? LA_MAX_LENGTH : ls;
	ts = (ts < TE_MAX_LENGTH) ? TE_MAX_LENGTH : ts;

	int rp = 4 + cs + ls + ts + 3*4;
	repeatText("-", rp);
	printf("\n| No. | %*s | %*s | %*s |\n", -cs, code, -ls, label, -ts, teacher);
	repeatText("-", rp);
	int i = 0;
	course crs = NULL;
	for (i = 0; i < COURSE_NUMBER; i++){
		crs = room->courses[i];
		printf("\n|%3d. | %*s | %*s | %*s |\n", i + 1, -cs, crs->code,
				-ls, crs->label, -ts, crs->teacher);
		repeatText("-", rp);
	}
	return;
}

int scanStudentNotes(node nde, course courses[], int size){
	if (nde == NULL){
		return READ_FAILURE;
	}
	int i;
	note nt = NULL;
	double avg = 0.;
	for (i = 0; i < size; i++){
		nt = scanNote(nde->stud, courses[i]);
		if (nt != NULL){
			nde->notes[i] = nt;
			avg += nt->avg;
			//nt = NULL;
		} else {
			//Retry
			i--;
		}
	}
	avg /= size;
	nde->avg = avg;
	return READ_SUCCESS;
}

int scanNotes(classroom room){
	if (room == NULL){
		printf("\nImpossible de trouver la classe\n");
		return READ_FAILURE;
	}
	if (room->coursesDefined){
		node nde = room->shead;
		while (nde != NULL){
			scanStudentNotes(nde, room->courses, COURSE_NUMBER);
			nde = nde->next;
		}
		room->notesDefined = 1;
	} else {
		printf("\nVous devez d'abord definir les matieres avant de saisir les notes d'un etudiant\n");
		return READ_FAILURE;
	}
	return READ_SUCCESS;
}

void printNotes(classroom room){
	if (room == NULL){
		return;
	}
	if (room->totalStdNumber <= 0){
		printf("\nLa liste des etudiants est vide.\n");
		return;
	}
	if (room->notesDefined == 0){
		printf("\nLes notes n'ont pas encore ete definies, veuillez les definir d'abord.\n");
		return;
	}
	//Si les notes sont définies alors les matières aussi
	char* fn = "Prenom", *ln = "Nom", *first = "Prem. Note", *second = "Deux. Note",
			*id = "Matricule", *cAvg = "Moyenne";
	int fns = strlen(fn), lns = strlen(ln), firsts = strlen(first),
			seconds = strlen(second), ids = strlen(id), cAvgs = strlen(cAvg);
	fns = (fns < FN_MAX_LENGTH) ? FN_MAX_LENGTH : fns;
	lns = (lns < LN_MAX_LENGTH) ? LN_MAX_LENGTH : lns;

	int rp = 4 + ids + lns + fns + firsts + seconds + cAvgs + 3*7, i, j;

	for (i = 0; i < COURSE_NUMBER; i++){
		printf("\n\nVoici les notes et moyennes des etudiants dans la matiere :");
		presentCourse(room->courses[i]);
		repeatText("-", rp);
		printf("\n| No. | %*s | %*s | %*s | %*s | %*s | %*s |\n", -ids, id,
				-lns, ln, -fns, fn, -firsts, first, -seconds, second, -cAvgs, cAvg);
		repeatText("-", rp);
		node nde = room->shead;
		j = 1;
		while (nde != NULL){
			printf("\n|%3d. | %*d | %*s | %*s | %*.2lf | %*.2lf | %*.2lf |\n", j, -ids,
					nde->stud->id, -lns, nde->stud->lastname, -fns, nde->stud->firstname,
					firsts, nde->notes[i]->first, seconds, nde->notes[i]->second,
					cAvgs, nde->notes[i]->avg);
			repeatText("-", rp);
			nde = nde->next;
			j++;
		}
	}
	rp -= cAvgs + firsts + seconds + 3*2;
	cAvg = "Moy. Gene.";
	cAvgs = strlen(cAvg);
	rp += cAvgs;
	printf("\n\nVoici les moyennes generales :\n");
	repeatText("-", rp);
	printf("\n| No. | %*s | %*s | %*s | %*s |\n", -ids, id,
			-lns, ln, -fns, fn, -cAvgs, cAvg);
	repeatText("-", rp);
	node nde = room->shead;
	j = 1;
	while (nde != NULL){
		printf("\n|%3d. | %*d | %*s | %*s | %*.2lf |\n", j, -ids,
				nde->stud->id, -lns, nde->stud->lastname, -fns,
				nde->stud->firstname, cAvgs, nde->avg);
		repeatText("-", rp);
		nde = nde->next;
		j++;
	}
	return;
}

void freeClassroom(classroom room){
	if (room == NULL){
		return;
	}
	int i;
	//Courses deletion
	course crs;
	for (i = 0; i < COURSE_NUMBER; i++){
		crs = room->courses[i];
		if (crs != NULL){
			freeCourse(crs);
		}
	}
	//Students deletion
	node nde = room->shead, tmp;
	while (nde != NULL){
		tmp = nde->next;
		nde->next = NULL;
		freeStudent(nde->stud);
		free(nde);
		room->totalStdNumber += -1;
		nde = tmp;
	}
	return;
}

int menu(char* message){
	if (message != NULL){
		printf("\n\n");
		printf("%s", message);
	}
	printf("\n\n");
	printf("********************\tBienvenu dans le menu de gestion de la salle\t***********************\n\n");
	printf("Que voulez-vous faire ? Choisissez une option dans le menu suivant :\n");
	printf("\n 1. Ajouter les matieres");
	printf("\n 2. Ajouter un etudiant");
	printf("\n 3. Lister les etudiants");
	printf("\n 4. Saisir les notes des etudiants");
	printf("\n 5. Afficher les moyennes definitives et par matières");
	printf("\n 6. Trouver les infos d'un etudiants");
	printf("\n 7. Produire la liste alphabetique triee de la classe");
	printf("\n 8. Afficher les matieres");
	printf("\n 9. Effacer la console");
	//printf("\n");
	printf("\n 0. Quitter");
	//printf("\n");
	int *n = NULL, value;
	do {
		printf("\n\nVotre choix : ");
		n =  readNotSignedInt(stdin, 1);
	} while (n == NULL || *n < 0 || *n > 9);
	value = *n;
	free(n);
	return (value);
}

char* applyChoice(int choice, classroom room){
	char* message = NULL;
	int out = 0;
	student stud = NULL;
	switch (choice){
		case 0:
			message = "Au revoir!";
			break;
		case 1:
			if (room->coursesDefined){
				message = "Les matieres sont deja definies!";
			} else {
				scanCourses(room);
				message = "Les matieres ont ete enregistrees avec succes!";
			}
			break;
		case 2:
			stud = addNewStudent(room);
			if (stud != NULL){
				if (room->notesDefined){
					printf("\nVeuillez saisir les notes de l'etudiant : \n");
					scanStudentNotes(room->shead, room->courses, COURSE_NUMBER);
				}
			}
			message = (stud != NULL) ? "L'etudiant a ete enregistre avec succes." : "Echec d'enregistrement de l'etudiant.";
			break;
		case 3:
			printStudents(room);
			break;
		case 4:
			out = scanNotes(room);
			message = (out == READ_SUCCESS) ? "Notes lues avec succes." : "Echec de lecture des notes.";
			break;
		case 5:
			printNotes(room);
			break;
		case 6:
			findStudentInfo(room);
			break;
		case 7:
			sortStudents(room);
			printStudents(room);
			break;
		case 8:
			printCourses(room);
			break;
		case 9:
			printf("\033c");
			break;
		//default:
	}
	return (message);
}
