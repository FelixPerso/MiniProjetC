#include "tools.h"

Output intVerify(int min, int max, char input[]){
    int integer = 0, index = strlen(input), asciiValue;
    char tmpChar;

    if(index == 0){
        Output output = {-1, "Écrivez quelque chose!\n"};
        return output;
    }

    do{
        tmpChar = input[--index];
        if(tmpChar==' '){
            Output output = {-1, "N'utilisez pas d'espaces!\n"};
            return output;
        }

        asciiValue = (int)tmpChar;
        if( asciiValue > 57 || asciiValue < 48 ) {
            Output output = {-1, "Utilisez que des chiffres!\n"};
            return output;
        }

        integer += (asciiValue-48) * (int)pow(10,(int)strlen(input) - index-1) ; // integer += digit * 10^unit
    }while(index > 0);

    if(integer>max || integer<min) {
        char message[1000];
        snprintf(message, sizeof(message), "choix ∉ [%d;%d]\n", min, max);
        Output output = {-1, message};
        return output;
    }else {
        Output output = {integer, ""};
        return output;
    }
}

Choice getChoice(const char* choices[], int size, char* title){
    int choix_recherche;
    char input[MAX_TAILLE];
    Output output;
    output.message = "";

    do {
        c_textbackground(WHITE);
        c_textcolor(BLACK);
        printf("%s", title);
        c_textcolor(LIGHTGRAY);
        c_textbackground(BLACK);
        for(int i=0; i<size; i++)
            printf("%d - %s\n", i+1, choices[i]);

        displayError(output.message);

        printf(">>>");

        fflush(stdin);
        gets(input);

        output = intVerify(1,size,input);
        choix_recherche = output.integer;

        printf("\n\n");

    } while(choix_recherche == -1);

    return choix_recherche;
}

void addPerson(Person* liste_personnes, Person new_personne, int* nb_personnes){
    (*nb_personnes)++;
    liste_personnes = realloc(liste_personnes, (*nb_personnes) * sizeof(Person));
    liste_personnes[(*nb_personnes)-1] = new_personne;
}

int getMaxValuesLength(){
    FILE *file;
    int nb_personnes = 0;
    Person personne;
    file = fopen("repertoire.txt", "r");

    if (file == NULL) {
        displayError("Fichier 'repertoire.txt' non retrouvée :(\nUn nouveau a été créé pour vous!\n\n");
        fopen("repertoire.txt", "w");
        return 0;
    }

    Person *personnes = malloc(sizeof(Person));

    while(fscanf(file, "%[^;];%[^;];%[^;];%[^\n]\n", personne.nom, personne.prenom,
                 personne.numero_telephone, personne.adresse_mail) == 4){
        addPerson(personnes, personne, &nb_personnes);
    }

    if(nb_personnes > 0) {
        c_textcolor(WHITE);
        printf("\nVoici le répertoire :\n");
        int max = 0;
        const int size = 4;
        for (int i = 0; i < nb_personnes; i++) {
            char* attributes[] = {personne.nom, personne.prenom, personne.numero_telephone, personne.adresse_mail};
            int tmp = getMaxAttributeLength(attributes, size);
            if (tmp > max)
                max = tmp;
        }
        return max;
    }

    return 0;
}

void displayPerson(Person personne) {
    char* personne_attributes[] = {"Nom", "Prénom", "Téléphone", "Mail"};
    char* personne_values[] = {personne.nom, personne.prenom, personne.numero_telephone, personne.adresse_mail};

    const int size = sizeof(personne_attributes) / sizeof(personne_attributes[0]);

    char** attributes_formatted = buildHarmonizedString((char **) personne_attributes, size);
    char** values_formatted = buildHarmonizedString((char **) personne_values, size);

    for(int i = 0; i < size; i++)
        printf(" %s : %s\n", attributes_formatted[i], values_formatted[i]);

    for(int i = 0; i < size; i++) {
        free(attributes_formatted[i]);
        free(values_formatted[i]);
    }
    free(attributes_formatted);
    free(values_formatted);
}

int getMaxAttributeLength(char* attributes[], int size) {
    int max_length = 0;

    for (int i = 0; i < size; i++) {
        int length = strlen(attributes[i]);
        if (length > max_length) {
            max_length = length;
        }
    }

    return max_length;
}

char** buildHarmonizedString(char* attributes[], int size) {
    char** res = malloc(sizeof(char*) * size);

    int max_lengths = getMaxAttributeLength(attributes, size);

    for (int i = 0; i < size; i++) {
        res[i] = malloc(sizeof(char) * (max_lengths + 1));

        snprintf(res[i], max_lengths + 1, "%-*s", max_lengths, attributes[i]);
    }

    return res;
}

void displayError(char* message){
    c_textcolor(RED);
    printf("\n%s", message);
    c_textcolor(LIGHTGRAY);
}