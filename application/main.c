#include <windows.h>
#include "../actions/actions.h"

const char* menu_options[] = {"Ajouter une personne",
                              "Afficher le repertoire",
                              "Réaliser une recherche",
                              "Supprimer une personne",
                              "Quitter"};

int main() {
    SetConsoleOutputCP(CP_UTF8);
    int fonctionnalite;
    bool run = true;

    while (run) {
        fonctionnalite = getChoice(menu_options, 5, " -=+=- MENU PRINCIPAL -=+=- \n");

        switch(fonctionnalite) {
            case 1:
                createPerson();
                break;
            case 2:
                displayAll();
                break;
            case 3:
                research();
                break;
            case 4:
                delete();
                break;
            case 5:
                run = false;
                break;
        }

        printf("\n");
    }

    printf("Terminé...\n");
    return 0;
}