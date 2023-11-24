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

void displayPerson(Person personne, int max_attribute_length){
    const char* attributes[] = {personne.nom, personne.prenom, personne.numero_telephone, personne.adresse_mail};
    const char* personne_attributes[] = {"Nom", "Prénom", "Téléphone", "Mail"};
    char** attributes_formatted = buildPersonAttributes((char **) personne_attributes, 4);
    const int size = 4;

    for(int i = 0; i < size; i++)
        printf(" %s : %s\n", attributes_formatted[i], attributes[i]);
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

char** buildPersonAttributes(char* attributes[], int size) {
    int max_attribute_length = getMaxAttributeLength(attributes, size);
    char** res = malloc(sizeof(char*) * size);

    for (int i = 0; i < size; i++) {
        res[i] = malloc(sizeof(char) * (max_attribute_length + 1));

        int nbspace = max_attribute_length - strlen(attributes[i]);

        for (int j = 0; j < nbspace; j++) {
            strcat(res[i], " ");
        }
        res[i] = realloc(res[i], sizeof(char) * (strlen(res[i]) + 1));
    }

    return res;
}

void displayError(char* message){
    c_textcolor(RED);
    printf("\n%s", message);
    c_textcolor(LIGHTGRAY);
}