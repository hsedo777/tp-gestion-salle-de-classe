#include <stdio.h>
#include <stdlib.h>

#include "mystring.c"
#include "numbers.c"
#include "course.c"
#include "student.c"
#include "note.c"
#include "ecole.c"

/*
* Liste des membres du groupe
* 1. HOVOZOUNKOU Rodrigue
* 2. OUSSA Donatien
* 3. BODJRENOU Daniel
* 4. BLOUD Nel-Arthur
*/

int main(){

	printf("**************************************\tBienvenu sur ecolia, l'application de gestion ");
	printf("d'une salle de classe\t******************************************************\n\n\n");
	printf("Bonjour, cher gestionnaire. Ce programme est pour la gestion d'une salle de classe.\n");
	printf("Pour ce qui est du nombre des etudiants, vous pouvez mettre zero(0), la possibilite ");
	printf("vous est donnee plus tard d'ajouter de nouveaux etudiants.\n");
	printf("Aussi, la saisie des matieres et des notes des etudiants est differee pour eviter ");
	printf("un temps long a passer a saisir les donnees au debut du programme.\n");
	printf("Dans ce programme, chaque fois qu'on vous demande de saisir un nombre positif et que ");
	printf("vous donnez un nombre negatif, le signe moins(-) est simplement ignore.\n\n");
	printf("Nous vous souhaitons la bienvenue !!!\n\n\n");
	classroom room = NULL;
	int *n = NULL;
	do {
		printf("Combien d'etudant voulez-vous enregister ? ");
		n = readNotSignedInt(stdin, 1);
		if (n == NULL){
			printf("\nErreur, vous devez taper un nombre!\n");
		}
	} while (n == NULL);
	if (*n > 0){
		printf("\nLecture de %d etudiant", *n);
		if (*n > 1){
			printf("s");
		}
		printf("\n");
	}
	room = initClassroom(*n);

	int choice;
	char* msg = NULL;
	do {
		choice = menu(msg);
		msg = applyChoice(choice, room);
	} while (choice != 0);

	free(n);
	freeClassroom(room);

	//char* tt = "Great";
	//printf("\nGood '%*s' %d bye!\n", -12, tt, FN_MAX_LENGTH);
	printf("\nGood bye!\n");
	return 0;
}
