#ifndef MINI_PROJET_C_TOOLS_H
#define MINI_PROJET_C_TOOLS_H

#endif //MINI_PROJET_C_TOOLS_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "conio.h"

#define MAX_TAILLE 40

typedef enum {
    NOM = 1,
    PRENOM = 2,
    TELEPHONE = 3,
    MAIL = 4
}Choice ;

typedef struct{
    int integer; //returns -1 when error
    char* message; //for error messages
}Output;

typedef struct  {
    char nom[MAX_TAILLE];
    char prenom[MAX_TAILLE];
    char numero_telephone[MAX_TAILLE];
    char adresse_mail[MAX_TAILLE];
}Person;

Output intVerify(int min, int max, char input[]);
Choice getChoice(const char* choices[], int size);
void addPerson(Person* liste_personnes, Person new_personne, int* nb_personnes);
void displayPerson(Person personne);