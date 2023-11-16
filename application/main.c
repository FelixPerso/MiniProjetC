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

    while (true) {
        fonctionnalite = getChoice(menu_options, 5);

        if (fonctionnalite == 1)
            createPerson();
        if (fonctionnalite == 2)
            displayAll();
        if (fonctionnalite == 3)
            research();
        if (fonctionnalite == 4)
            delete();
        if (fonctionnalite == 5)
            break;

        printf("\n");
    }

    printf("Terminé...\n");
    return 0;
}