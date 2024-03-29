#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"




char *automato_operadores_relacionais(FILE *pos) {
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

char *automato_ident(FILE *pos, dict** tabela) {
    FILE *aux;
    aux = pos;
    char id[100];
    char buffer;

    //Estado q0
    fread(&buffer, sizeof(char), 1, aux);


    if ((buffer >= 66 && buffer <= 90) || (buffer >= 97 && buffer <= 122)) {
        //Primeiro char eh letra
        strcat(id, buffer);

        //Estado q1
        while((buffer >= 48 && buffer <= 57) || (buffer >= 66 && buffer <= 90) || (buffer >= 97 && buffer <= 122))
        {
            fread(&buffer, sizeof(char), 1, aux);
            strcat(id, buffer);
        }

        if(bate_hash(buffer, tabela));
        {

        }

    } else {
        print("Identificador mal formatado");
    }


}


int main() {
    char* simb_reservados = "./dados/simbolosReservados.txt";
    dict** tabela;
    tabela = (dict**)malloc(1000*sizeof(dict*));
    cria_hash(simb_reservados, tabela);

    for(int i=0; i< 1000; i++)
    {
        dict* no = tabela[i];
        
        while(no!=NULL)
        {
            printf("%s ", no->word);
            if(no->next!=NULL){
                no = no->next;
            }
        }
        printf("\n");
    }
    

    free(tabela);
    printf("Hello world!\n");
    return 0;
}
