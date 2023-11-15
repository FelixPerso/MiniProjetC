#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <windows.h>
#include "utils/tools.h"

const char* personne_attributes[] = {"Nom", "Prénom", "Téléphone", "Mail"};
const char* menu_options[] = {"Ajouter une personne", "Afficher le repertoire", "Réaliser une recherche", "Supprimer une personne", "Quitter"};


void Afficher_Personne(Personne personne){
    printf("Nom : %s\n", personne.nom);
    printf("Prénom : %s\n", personne.prenom);
    printf("Téléphone : %s\n", personne.numero_telephone);
    printf("Mail : %s\n", personne.adresse_mail);
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

    fprintf(file, "%s;%s;%s;%s\n", personne.nom, personne.prenom, personne.numero_telephone, personne.adresse_mail);

    fclose(file);

    printf("\nLa personne a été ajouté avec succès.\n");
}

void Affiche_Repertoire(){
    FILE *file;
    int nb_personnes = 0;
    Personne personne;
    file = fopen("repertoire.txt", "r");

    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier repertoire.txt\n\n");
        exit(1);
    }

    Personne *personnes = malloc(sizeof(Personne));

    printf("\nVoici le répertoire :\n\n");

    while(fscanf(file, "%[^;];%[^;];%[^;];%[^\n]\n", personne.nom, personne.prenom, personne.numero_telephone, personne.adresse_mail) == 4){
        add_personne(personnes, personne, &nb_personnes);
    }

    if(nb_personnes > 0) {
        for (int i = 0; i < nb_personnes; i++) {
            printf("---------------------------\n");
            Afficher_Personne(personnes[i]);
        }
        printf("---------------------------\n");
    }else
        printf("Aucune personne n'a été trouvé :/\n");

    fclose(file);
}

void Recherche(){
    FILE *file;
    Personne personne;
    int nb_personnes = 0;
    bool personneTrouve;
    char champs_recherche[MAX_TAILLE];

    file = fopen("repertoire.txt", "r");

    if (file == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier repertoire.txt\n\n");
        exit(1);
    }

    printf("Entrez le champs de la personne à rechercher :");
    CHOIX choix_recherche = get_choix(personne_attributes, 4);

    printf("Entrez le %s recherché :", personne_attributes[choix_recherche-1]);

    scanf("%s", champs_recherche);
    printf("\n");

    Personne* personnes = malloc(sizeof(Personne));

    while (fscanf(file, "%[^;];%[^;];%[^;];%[^\n]\n", personne.nom, personne.prenom, personne.numero_telephone, personne.adresse_mail) == 4) {
        personneTrouve = false;

        switch (choix_recherche) {
            case 1:
                if (strcmp(personne.nom, champs_recherche) == 0) {
                    personneTrouve = true;
                }
                break;
            case 2:
                if (strcmp(personne.prenom, champs_recherche) == 0) {
                    personneTrouve = true;
                }
                break;
            case 3:
                if (strcmp(personne.numero_telephone, champs_recherche) == 0) {
                    personneTrouve = true;
                }
                break;
            case 4:
                if (strcmp(personne.adresse_mail, champs_recherche) == 0) {
                    personneTrouve = true;
                }
                break;
        }

        if (personneTrouve) {
            add_personne(personnes, personne, &nb_personnes);
        }
    }

    if (nb_personnes > 0) {
        printf(nb_personnes>1?"%d Personnes trouvées :\n\n":"Une personne trouvée :\n\n", nb_personnes);

        for (int i = 0; i < nb_personnes; i++) {
            printf("---------------------------\n");
            Afficher_Personne(personnes[i]);
        }
        printf("---------------------------\n\n");

    } else
        printf("Aucune personne avec le %s '%s' existe :/\n", personne_attributes[choix_recherche-1], champs_recherche);

    fclose(file);
}

void Supprimer(){
    FILE *file, *tmpFile;
    Personne personne;
    char champs_recherche[MAX_TAILLE];
    bool personneTrouve;
    int cpt = 0;

    file = fopen("repertoire.txt", "r");

    if (file == NULL) {
        fprintf(stderr, "Fichier repertoire.txt introuvable...\n\n");
        exit(1);
    }

    tmpFile = fopen("temp.txt", "w");

    if (tmpFile == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture du fichier temp.txt\n\n");
        exit(1);
    }

    printf("Entrez le champs de la personne à supprimer :\n\n");
    CHOIX choix_recherche = get_choix(personne_attributes, 4);

    printf("\nEntrez le %s de(s) personne(s) à supprimer: ", personne_attributes[choix_recherche-1]);

    scanf("%s", champs_recherche);
    printf("\n");

    while(fscanf(file, "%[^;];%[^;];%[^;];%[^\n]\n", personne.nom, personne.prenom, personne.numero_telephone, personne.adresse_mail) == 4) {
        personneTrouve = false;

        switch (choix_recherche) {
            case 1:
                if (strcmp(personne.nom, champs_recherche) != 0) {
                    fprintf(tmpFile, "%s;%s;%s;%s\n", personne.nom, personne.prenom, personne.numero_telephone, personne.adresse_mail);
                    personneTrouve = true;
                }else cpt++;
                break;
            case 2:
                if (strcmp(personne.prenom, champs_recherche) != 0) {
                    fprintf(tmpFile, "%s;%s;%s;%s\n", personne.nom, personne.prenom, personne.numero_telephone, personne.adresse_mail);
                    personneTrouve = true;
                }else cpt++;
                break;
            case 3:
                if (strcmp(personne.numero_telephone, champs_recherche) != 0) {
                    fprintf(tmpFile, "%s;%s;%s;%s\n", personne.nom, personne.prenom, personne.numero_telephone, personne.adresse_mail);
                    personneTrouve = true;
                }else cpt++;
                break;
            case 4:
                if (strcmp(personne.adresse_mail, champs_recherche) != 0) {
                    fprintf(tmpFile, "%s;%s;%s;%s\n", personne.nom, personne.prenom, personne.numero_telephone, personne.adresse_mail);
                    personneTrouve = true;
                }else cpt++;
                break;
        }
    }

    if (cpt == 0)
        printf("La personne recherché par %s avec la valeur %s n'existe pas\n\n", personne_attributes[choix_recherche-1], champs_recherche);
    else
        printf(cpt>1?"%d Personnes ont été supprimées!\n\n":"Une personne a été supprimée!\n\n", cpt);

    fclose(file);
    fclose(tmpFile);

    remove("repertoire.txt");
    rename("temp.txt", "repertoire.txt");

}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    int fonctionnalite;

    while (true) {
        fonctionnalite = get_choix(menu_options, 5);

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