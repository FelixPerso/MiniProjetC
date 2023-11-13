#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TAILLE 40

typedef enum {
    NOM = 1,
    PRENOM = 2,
    TELEPHONE = 3,
    MAIL = 4
}CHOIX ;

const char* listeChoix = {"nom", "prénom", "telephone", "mail"};

typedef struct  {
    char nom[MAX_TAILLE];
    char prenom[MAX_TAILLE];
    char numero_telephone[MAX_TAILLE];
    char adresse_mail[MAX_TAILLE];
}Personne;

void Afficher_Personne(Personne personne){
    printf("Nom : %s\n", personne.nom);
    printf("Prenom : %s\n", personne.prenom);
    printf("Telephone : %s\n", personne.numero_telephone);
    printf("Mail : %s\n", personne.adresse_mail);
    printf("------------------\n\n");
}

CHOIX get_choix(){
    int choix_recherche;
    do {
        printf("Les choix disponibles sont : \n"
               "* Nom (1)\n"
               "* Prénom (2)\n"
               "* Téléphone (3)\n"
               "* Mail (4)\n\n");

        printf("Votre choix :");

        scanf("%d", &choix_recherche);

        if (choix_recherche <= 0 || choix_recherche > 4){
            printf("WELSH-POWELL TU SAIS PAS CHOISIR ENTRE 1 ET 4\n\n");
            choix_recherche = 0;
        }

    } while(!choix_recherche);

    return choix_recherche;
}


void Creer_Enregistrement() {
    FILE *file;
    Personne personne;

    file = fopen("repertoire.txt", "a");

    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier repertoire.txt\n\n");
        exit(1);
    }

    printf("Nom :");
    scanf("%s", personne.nom);

    printf("Prenom :");
    scanf("%s", personne.prenom);

    printf("Numero de telephone :");
    scanf("%s", personne.numero_telephone);

    printf("Adresse mail :");
    scanf("%s", personne.adresse_mail);

    fprintf(file, "\n%s;%s;%s;%s", personne.nom, personne.prenom, personne.numero_telephone, personne.adresse_mail);

    fclose(file);

    printf("\nLa personne a été ajouté avec succès.\n");
}

void Affiche_Repertoire(){
    FILE *file;

    Personne personne;
    file = fopen("repertoire.txt", "r");

    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier repertoire.txt\n\n");
        exit(1);
    }

    printf("\nVoici le répertoire :\n\n");

    while(fscanf(file, "%[^;];%[^;];%[^;];%[^\n]\n", personne.nom, personne.prenom, personne.numero_telephone, personne.adresse_mail) == 4){
        Afficher_Personne(personne);
    }

    fclose(file);
}

void Recherche(){
    FILE *file;
    Personne personne;
    bool personneTrouve = false;
    char champs_recherche[MAX_TAILLE];

    file = fopen("repertoire.txt", "r");

    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier repertoire.txt\n\n");
        exit(1);
    }

    printf("Entrez le champs de la personne à rechercher :\n\n");
    CHOIX choix_recherche = get_choix();

    printf("\nEntrez le %s recherché :", );

    scanf("%s", champs_recherche);

    printf("\n");

    while(fscanf(file, "%[^;];%[^;];%[^;];%[^\n]\n", personne.nom, personne.prenom, personne.numero_telephone, personne.adresse_mail) == 4){



    }

    if (!personneTrouve)
        printf("La personne recherché par %s avec la valeur %s n'existe pas ", choix_recherche, champs_recherche);

    fclose(file);
}



void Supprimer(){
    FILE *file, *tmpFile;
    Personne personne;
    char champs_recherche[MAX_TAILLE];
    bool personneTrouve = false;
    const char* tab[] = {"nom", "prénom", "téléphone", "mail"};

    file = fopen("repertoire.txt", "r");

    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier repertoire.txt\n\n");
        exit(1);
    }

    tmpFile = fopen("temp.txt", "w");

    if (tmpFile == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier temp.txt\n\n");
        exit(1);
    }

    printf("Entrez le champs de la personne à supprimer :\n\n");
    int choix_recherche = get_choix();

    printf("\nEntrez le %s à supprimer: ", tab[choix_recherche-1]);

    scanf("%s", champs_recherche);

    printf("\n");

    while(fscanf(file, "%[^;];%[^;];%[^;];%[^\n]\n", personne.nom, personne.prenom, personne.numero_telephone, personne.adresse_mail) == 4) {
        if (strcmp("nom", tab[choix_recherche-1]) == 0)
            if (strcmp(personne.nom, champs_recherche) != 0) {
                fprintf(tmpFile, "%s;%s;%s;%s\n", personne.nom, personne.prenom, personne.numero_telephone, personne.adresse_mail);
                personneTrouve = true;
            }

        if (strcmp("prénom", tab[choix_recherche-1]) == 0)
            if (strcmp(personne.prenom, champs_recherche) != 0) {
                fprintf(tmpFile, "%s;%s;%s;%s\n", personne.nom, personne.prenom, personne.numero_telephone, personne.adresse_mail);
                personneTrouve = true;
            }

        if (strcmp("téléphone", tab[choix_recherche-1]) == 0)
            if (strcmp(personne.numero_telephone, champs_recherche) != 0) {
                fprintf(tmpFile, "%s;%s;%s;%s\n", personne.nom, personne.prenom, personne.numero_telephone, personne.adresse_mail);
                personneTrouve = true;
            }

        if (strcmp("mail", tab[choix_recherche-1]) == 0)
            if (strcmp(personne.adresse_mail, champs_recherche) != 0) {
                fprintf(tmpFile, "%s;%s;%s;%s\n", personne.nom, personne.prenom, personne.numero_telephone, personne.adresse_mail);
                personneTrouve = true;
            }

    }

    if (!personneTrouve)
        printf("La personne recherché par %s avec la valeur %s n'existe pas\n\n", tab[choix_recherche-1], champs_recherche);
    else
        printf("La personne a été supprimé avec succès !\n\n");


    fclose(file);
    fclose(tmpFile);

    remove("repertoire.txt");
    rename("temp.txt", "repertoire.txt");

}


int main() {
    int fonctionnalite;

    while (1) {
        printf("Que voulez-vous faire :\n");
        printf("* Ajouter une personne (1)\n");
        printf("* Afficher le repertoire (2)\n");
        printf("* Réaliser une recherche (3)\n");
        printf("* Supprimer une personne (4)\n");
        printf("* Quitter (5)\n");

        printf("\nVotre choix :");

        scanf("%d", &fonctionnalite);

        printf("\n");

        if (fonctionnalite == 1)
            Creer_Enregistrement();
        if (fonctionnalite == 2)
            Affiche_Repertoire();
        if (fonctionnalite == 3)
            Recherche();
        if (fonctionnalite == 4)
            Supprimer();
        if (fonctionnalite == 5)
            break;

        printf("\n");
    }

    printf("Terminé...\n");
    return 0;
}
