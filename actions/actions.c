#include "actions.h"

const char* personne_attributes[] = {"Nom", "Prénom", "Téléphone", "Mail"};

void createPerson() {
    FILE *file;
    Person personne;

    file = fopen("repertoire.txt", "a");

    if (file == NULL) {
        displayError("Fichier 'repertoire.txt' non retrouvée :(\nUn nouveau a été créé pour vous!\n\n");
        file = fopen("repertoire.txt", "w");
    }

    printf("Nom :");
    scanf("%s", personne.nom);

    printf("Prénom :");
    scanf("%s", personne.prenom);

    printf("Numéro de telephone :");
    scanf("%s", personne.numero_telephone);

    printf("Adresse mail :");
    scanf("%s", personne.adresse_mail);

    fprintf(file, "%s;%s;%s;%s\n", personne.nom, personne.prenom, personne.numero_telephone,
            personne.adresse_mail);

    fclose(file);

    printf("\nLa personne a été ajouté avec succès.\n");
}

void displayAll(){
    FILE *file;
    int nb_personnes = 0;
    Person personne;
    file = fopen("repertoire.txt", "r");

    if (file == NULL) {
        displayError("Fichier 'repertoire.txt' non retrouvée :(\nUn nouveau a été créé pour vous!\n\n");
        fopen("repertoire.txt", "w");
        return;
    }

    Person *personnes = malloc(sizeof(Person));

    while(fscanf(file, "%[^;];%[^;];%[^;];%[^\n]\n", personne.nom, personne.prenom,
                 personne.numero_telephone, personne.adresse_mail) == 4){
        addPerson(personnes, personne, &nb_personnes);
    }

    if(nb_personnes > 0) {
        c_textcolor(WHITE);
        printf("\nVoici le répertoire :\n");

        for (int i = 0; i < nb_personnes; i++) {
            if(i%2 == 0)
                c_textbackground(LIGHTGRAY);
            else
                c_textbackground(DARKGRAY);
            c_textcolor(BLACK);
            displayPerson(personnes[i]);
            c_textbackground(BLACK);
        }
        c_textcolor(LIGHTGRAY);
    }else
        displayError("Aucune personne n'a été trouvé :/\n");

    fclose(file);
}

void research(){
    FILE *file;
    Person personne;
    int nb_personnes = 0;
    bool personneTrouve;
    char champs_recherche[MAX_TAILLE];
    Choice choix_recherche;

    file = fopen("repertoire.txt", "r");

    if (file == NULL) {
        displayError("Fichier 'repertoire.txt' non retrouvée :(\nUn nouveau a été créé pour vous!\n\n");
        fopen("repertoire.txt", "w");
        return;
    }

    choix_recherche = getChoice(personne_attributes, 4, "Entrez le champs de la personne à rechercher :\n");

    do {
        printf("Entrez le %s recherché (%d char max) : ", personne_attributes[choix_recherche-1], MAX_TAILLE);

        fgets(champs_recherche, MAX_TAILLE, stdin);
        printf("\n");

        if (champs_recherche[0] == '\n')
            displayError("Veuillez écrire quelque chose!\n");
    }while(champs_recherche[0] == '\n');

    champs_recherche[strlen(champs_recherche)-1] = '\0';

    Person* personnes = malloc(sizeof(Person));

    while (fscanf(file, "%[^;];%[^;];%[^;];%[^\n]\n", personne.nom, personne.prenom,
                  personne.numero_telephone, personne.adresse_mail) == 4) {
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
            addPerson(personnes, personne, &nb_personnes);
        }
    }

    if (nb_personnes > 0) {
        c_textcolor(WHITE);
        printf(nb_personnes>1?"%d Personnes trouvées :\n\n":"Une personne trouvée :\n\n", nb_personnes);

        for (int i = 0; i < nb_personnes; i++) {
            if(i%2 == 0)
                c_textbackground(LIGHTGRAY);
            else
                c_textbackground(DARKGRAY);
            c_textcolor(BLACK);
            displayPerson(personnes[i]);
            c_textbackground(BLACK);
        }
        c_textcolor(LIGHTGRAY);

    } else {
        char message[1000];
        snprintf(message, sizeof(message), "Aucune personne avec le %s '%s' existe :/\n",
                 personne_attributes[choix_recherche-1], champs_recherche);
        displayError(message);
    }

    fclose(file);
}

void delete(){
    FILE *file, *tmpFile;
    Person personne;
    char champs_recherche[MAX_TAILLE];
    int cpt = 0;

    file = fopen("repertoire.txt", "r");

    if (file == NULL) {
        displayError("Fichier 'repertoire.txt' non retrouvée :(\nUn nouveau a été créé pour vous!\n\n");
        fopen("repertoire.txt", "w");
        return;
    }

    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0) {
        displayError("Le répertoire est vide :/\n\n");
        return;
    }
    fseek(file, 0, SEEK_SET);

    tmpFile = fopen("temp.txt", "w");

    Choice choix_recherche = getChoice(personne_attributes, 4, "Entrez le champs de la personne à supprimer :\n");

    do {
        printf("Entrez le %s recherché (%d char max) : ", personne_attributes[choix_recherche-1], MAX_TAILLE);

        fgets(champs_recherche, MAX_TAILLE, stdin);
        printf("\n");

        if (champs_recherche[0] == '\n')
            displayError("Veuillez écrire quelque chose!\n");
    }while(champs_recherche[0] == '\n');

    champs_recherche[strlen(champs_recherche)-1] = '\0';

    while(fscanf(file, "%[^;];%[^;];%[^;];%[^\n]\n", personne.nom, personne.prenom,
                 personne.numero_telephone, personne.adresse_mail) == 4) {
        switch (choix_recherche) {
            case 1:
                if (strcmp(personne.nom, champs_recherche) != 0) {
                    fprintf(tmpFile, "%s;%s;%s;%s\n", personne.nom, personne.prenom,
                            personne.numero_telephone, personne.adresse_mail);
                }else cpt++;
                break;
            case 2:
                if (strcmp(personne.prenom, champs_recherche) != 0) {
                    fprintf(tmpFile, "%s;%s;%s;%s\n", personne.nom, personne.prenom,
                            personne.numero_telephone, personne.adresse_mail);
                }else cpt++;
                break;
            case 3:
                if (strcmp(personne.numero_telephone, champs_recherche) != 0) {
                    fprintf(tmpFile, "%s;%s;%s;%s\n", personne.nom, personne.prenom,
                            personne.numero_telephone, personne.adresse_mail);
                }else cpt++;
                break;
            case 4:
                if (strcmp(personne.adresse_mail, champs_recherche) != 0) {
                    fprintf(tmpFile, "%s;%s;%s;%s\n", personne.nom, personne.prenom,
                            personne.numero_telephone, personne.adresse_mail);
                }else cpt++;
                break;
        }
    }

    if (cpt == 0) {
        char message[1000];
        snprintf(message, sizeof(message), "Aucune personne avec le %s '%s' existe :/\n",
                 personne_attributes[choix_recherche-1], champs_recherche);
        displayError(message);

    }else
        printf(cpt>1?"%d Personnes ont été supprimées!\n\n":"Une personne a été supprimée!\n\n", cpt);

    fclose(file);
    fclose(tmpFile);

    remove("repertoire.txt");
    rename("temp.txt", "repertoire.txt");

}