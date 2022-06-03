#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int automato_operadores_relacionais_e_sinais_matematicos(FILE *pos) {
    FILE *aux;
    aux = pos;
    char symbol[2];
    char buffer;
    //Estado q0
    fread(&buffer, sizeof(char), 1, aux);
    if (buffer == '<') {//Estado q1
        strcat(symbol,buffer);
        fread(&buffer, sizeof(char), 1, aux);
        if (buffer == '=') {//Estado q2
            strcat(symbol,buffer);// <= simb_meig
        } else if (buffer == '>') {//Estado q3
            strcat(symbol,buffer);// <> simb_dif
        } else {//Estado q4
            // > simb_menor
        }
    } else if (buffer == '=') {// Estado q5
        strcat(symbol,buffer);// = simb_ig
    } else if (buffer == '>') {// Estado q6
        fread(&buffer, sizeof(char), 1, aux);
        strcat(symbol,buffer);
        if (buffer == '=') {// Estado q7
            strcat(symbol,buffer);// <= simb_meig
        } else {//Estado q8
            strcat(symbol,buffer);// > simb_maior
            // retroceder
        }
    }
    return symbol;
}

int automato_ident(FILE *pos, char* token[2]) {
    FILE *aux;
    aux = pos;
    char id[100];
    char buffer;
    char simb[] = "ident";

    //Estado q0
    fread(&buffer, sizeof(char), 1, aux);


    if ((buffer >= 66 && buffer <= 90) || (buffer >= 97 && buffer <= 122)) {
        //Primeiro char eh letra
        strcat(id, &buffer);

        fread(&buffer, sizeof(char), 1, aux); //move o ponteiro
        //Estado q1
        while((buffer >= 48 && buffer <= 57) || (buffer >= 66 && buffer <= 90) || (buffer >= 97 && buffer <= 122))
        {
            strcat(id, &buffer);
            //caractere lido eh letra ou digito
            fread(&buffer, sizeof(char), 1, aux);

        }

        if(/*BATE_HASH(buffer) == 1*/1)
        {
            token[0] = id;
            token[1] = simb;

            return 1;
        }

    } else {
        printf("Identificador mal formatado");
        return 0;
    }

    return 0;
}


int automato_palavraReservada(FILE *pos, char* token) {
    FILE *aux;
    aux = pos;
    char palavra[100];
    char buffer;
    char *simb;

    fread(&buffer, sizeof(char), 1, aux);

    while((buffer >= 66 && buffer <= 90) || (buffer >= 97 && buffer <= 122))
    {
        //caractere lido eh letra
        strcat(simb, &buffer);
        fread(&buffer, sizeof(char), 1, aux);
    }

    if(/*BATE_HASH(palavra, &simb) == 1 */) {
        token[0] = palavra;
        token[1] = simb;

        return 1;
    } else {
        return 0;
    }

    return 0;
}

int main() {
    printf("Hello world!\n");
    return 0;
}
