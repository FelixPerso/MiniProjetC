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

void displayPersons(Person* liste_personnes, int nb_personnes){
    int max_values_length = 0;

    for (int i = 0; i < nb_personnes; i++){
        char* personne_values[] = {liste_personnes[i].nom, liste_personnes[i].prenom,
                                   liste_personnes[i].numero_telephone, liste_personnes[i].adresse_mail};

        int tmp = getMaxAttributeLength(personne_values);

        if (tmp > max_values_length)
            max_values_length = tmp;
    }

    for (int i = 0; i < nb_personnes; i++) {
        if(i%2 == 0)
            c_textbackground(LIGHTGRAY);
        else
            c_textbackground(DARKGRAY);
        c_textcolor(BLACK);
        displayPerson(liste_personnes[i], max_values_length);
        c_textbackground(BLACK);
    }
    c_textcolor(LIGHTGRAY);
}


void displayPerson(Person personne, int max_values_length) {
    char* personne_attributes[] = {"Nom", "Prénom", "Téléphone", "Mail"};
    char* personne_values[] = {personne.nom, personne.prenom, personne.numero_telephone, personne.adresse_mail};

    int max_attributes_length = getMaxAttributeLength(personne_attributes);

    char** attributes_formatted = buildHarmonizedString(personne_attributes, max_attributes_length);
    char** values_formatted = buildHarmonizedString(personne_values, max_values_length);

    for (int i = 0; i< NB_ATTRIBUTS; i++){
        printf("%s:%s\n", attributes_formatted[i], values_formatted[i]);
    }

    freeHarmonizedString(attributes_formatted);
    freeHarmonizedString(values_formatted);

}

int getAdjustedLength(char* str) {
    int length = 0;
    for (size_t i = 0; i < strlen(str);) {
        unsigned char first_byte = (unsigned char)str[i];

        if ((first_byte & 0x80) == 0) {
            // Caractère ASCII simple
            i += 1;
        } else if ((first_byte & 0xE0) == 0xC0) {
            // Caractère sur 2 octets
            i += 2;
        } else if ((first_byte & 0xF0) == 0xE0) {
            // Caractère sur 3 octets
            i += 3;
        } else if ((first_byte & 0xF8) == 0xF0) {
            // Caractère sur 4 octets
            i += 4;
        } else {
            // Caractère invalide
            displayError("Erreur : caractère(s) invalide(s) rencontré(s)>.\n");
            exit(EXIT_FAILURE);
        }

        length++;
    }

    return length;
}

int getMaxAttributeLength(char* attributes[]) {
    int max_length = 0;

    for (int i = 0; i < NB_ATTRIBUTS; i++) {
        int length = getAdjustedLength(attributes[i]);
        if (length > max_length) {
            max_length = length;
        }
    }

    return max_length + 1; // for a space before the end of the box
}

char** buildHarmonizedString(char* attributes[], int max_length) {
    char** res = malloc(sizeof(char*) * NB_ATTRIBUTS);

    for (int i = 0; i < NB_ATTRIBUTS; i++) {
        res[i] = malloc(sizeof(char) * (max_length + 2));

        strcpy(res[i], " ");

        strcat(res[i], attributes[i]);

        for (int j = getAdjustedLength(attributes[i]); j < max_length; j++) {
            strcat(res[i], " ");
        }
    }

    return res;
}


void freeHarmonizedString(char** harmonizedString) {
    for (int i = 0; i < NB_ATTRIBUTS; i++) {
        free(harmonizedString[i]);
    }
    free(harmonizedString);
}

void displayError(char* message){
    c_textcolor(RED);
    printf("\n%s", message);
    c_textcolor(LIGHTGRAY);
}