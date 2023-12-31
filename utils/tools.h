#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "conio.h"

#define MAX_TAILLE 40
#define NB_ATTRIBUTS 4
#define REPERTOIRE "repertoire.txt"

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
Choice getChoice(const char* choices[], int size, char* title);
void displayError(char* message);

void addPerson(Person* liste_personnes, Person new_personne, int* nb_personnes);
void displayPersons(Person* liste_personnes, int nb_personnes);
void displayPerson(Person personne, int max_values_length);
int getAdjustedLength(char* str);
int getMaxAttributeLength(char** attributes);
char** buildHarmonizedString(char* attributes[], int max_lenght);
void freeHarmonizedString(char** harmonizedString);
int isSeparator(char* message);