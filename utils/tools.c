#include "tools.h"

Output intVerify(int min, int max, char input[]){
    int integer = 0, index = strlen(input), asciiValue;
    char tmpChar;

    if(index == 0){
        Output output = {-1, "Ecrivez quelque chose!\n"};
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

CHOIX get_choix(const char* choices[], int size){
    int choix_recherche;
    char input[MAX_TAILLE];
    Output output;
    output.message = "";

    do {
        printf("Les choix disponibles sont : \n");
        for(int i=0; i<size; i++)
            printf("%d - %s\n", i+1, choices[i]);

        c_textcolor(RED);
        printf("\n%s",output.message);
        c_textcolor(LIGHTGRAY);

        printf("Votre choix :");

        fflush(stdin);
        gets(input);

        output = intVerify(1,size,input);
        choix_recherche = output.integer;

        printf("\n\n");

    } while(choix_recherche == -1);

    return choix_recherche;
}

void add_personne(Personne* liste_personnes, Personne new_personne, int* nb_personnes){
    (*nb_personnes)++;
    liste_personnes = realloc(liste_personnes, (*nb_personnes) * sizeof(Personne));
    liste_personnes[(*nb_personnes)-1] = new_personne;
}
