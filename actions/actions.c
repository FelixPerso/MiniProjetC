#include "actions.h"

const char* personne_attributes[] = {"Nom", "Prénom", "Téléphone", "Mail"};

void createPerson() {
    FILE *file;
    Person personne;

    file = fopen(REPERTOIRE, "a");

    if (file == NULL) {
        displayError("Fichier 'repertoire.txt' non retrouvée :(\nUn nouveau a été créé pour vous!\n\n");
        FILE *newFile = fopen(REPERTOIRE, "w");
        fclose(newFile);
        return;
    }

    int i = 0;
    while(i < NB_ATTRIBUTS) {
        char input[MAX_TAILLE];
        printf("%s :", personne_attributes[i]);
        fgets(input, sizeof(input) + 1, stdin);
        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) >= MAX_TAILLE) {
            c_textcolor(RED);
            printf("\nLe %s de la personne ne doit pas dépasser %d caractères.\n\n", personne_attributes[i], MAX_TAILLE);
            c_textcolor(LIGHTGRAY);
            fclose(file);
            return;
        }

        if (isSeparator(input) == 1) {
            displayError("Le caractère ';' ne doit pas être utilisé.\n\n");
            fclose(file);
            return;
        }

        switch (i) {
            case 0:
                strncpy(personne.nom, input, MAX_TAILLE);
                break;
            case 1:
                strncpy(personne.prenom, input, MAX_TAILLE);
                break;
            case 2:
                strncpy(personne.numero_telephone, input, MAX_TAILLE);
                break;
            case 3:
                strncpy(personne.adresse_mail, input, MAX_TAILLE);
                break;
        }
        i++;

    }

    fprintf(file, "%s;%s;%s;%s\n", personne.nom, personne.prenom, personne.numero_telephone,
            personne.adresse_mail);

    fclose(file);

    printf("\nLa personne a été ajouté avec succès.\n");
}

void displayAll(){
    FILE *file;
    int nb_personnes = 0;
    Person personne;
    file = fopen(REPERTOIRE, "r");

    if (file == NULL) {
        displayError("Fichier 'repertoire.txt' non retrouvée :(\nUn nouveau a été créé pour vous!\n\n");
        FILE *newFile = fopen(REPERTOIRE, "w");
        fclose(newFile);
        return;
    }

    Person *personnes = malloc(sizeof(Person));

    while(fscanf(file, "%[^;];%[^;];%[^;];%[^\n]\n", personne.nom, personne.prenom,
                 personne.numero_telephone, personne.adresse_mail) == NB_ATTRIBUTS){
        addPerson(personnes, personne, &nb_personnes);
    }

    if(nb_personnes > 0) {
        c_textcolor(WHITE);
        printf("\nVoici le répertoire :\n");
        displayPersons(personnes, nb_personnes);
    }else
        displayError("Il n'y a aucune personne enregistrée dans le répertoire :/\n");

    fclose(file);
    free(personnes);
}

void research(){
    FILE *file;
    Person personne;
    int nb_personnes = 0;
    bool personneTrouve;
    char champs_recherche[MAX_TAILLE];
    Choice choix_recherche;

    file = fopen(REPERTOIRE, "r");

    if (file == NULL) {
        displayError("Fichier 'repertoire.txt' non retrouvée :(\nUn nouveau a été créé pour vous!\n\n");
        FILE *newFile = fopen(REPERTOIRE, "w");
        fclose(newFile);
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
                  personne.numero_telephone, personne.adresse_mail) == NB_ATTRIBUTS) {
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

        displayPersons(personnes, nb_personnes);

    } else {
        char message[1000];
        snprintf(message, sizeof(message), "Aucune personne avec le %s '%s' existe :/\n",
                 personne_attributes[choix_recherche-1], champs_recherche);
        displayError(message);
    }

    fclose(file);
    free(personnes);
}

void delete(){
    FILE *file, *tmpFile;
    Person personne;
    char champs_recherche[MAX_TAILLE];
    int cpt = 0;

    file = fopen(REPERTOIRE, "r");

    if (file == NULL) {
        displayError("Fichier 'repertoire.txt' non retrouvée :(\nUn nouveau a été créé pour vous!\n\n");
        FILE *newFile = fopen(REPERTOIRE, "w");
        fclose(newFile);
        return;
    }

    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0) {
        displayError("Le répertoire est vide :/\n\n");
        return;
    }
    fseek(file, 0, SEEK_SET);

    tmpFile = fopen("temp.txt", "w");

    Choice choix_recherche = getChoice(personne_attributes, NB_ATTRIBUTS, "Entrez le champs de la personne à supprimer :\n");

    do {
        printf("Entrez le %s recherché (%d char max) : ", personne_attributes[choix_recherche-1], MAX_TAILLE);

        fgets(champs_recherche, MAX_TAILLE, stdin);
        printf("\n");

        if (champs_recherche[0] == '\n')
            displayError("Veuillez écrire quelque chose!\n");
    }while(champs_recherche[0] == '\n');

    champs_recherche[strlen(champs_recherche)-1] = '\0';

    while(fscanf(file, "%[^;];%[^;];%[^;];%[^\n]\n", personne.nom, personne.prenom,
                 personne.numero_telephone, personne.adresse_mail) == NB_ATTRIBUTS) {
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

    remove(REPERTOIRE);
    rename("temp.txt", REPERTOIRE);

}