#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *automato_operadores_relacionais(FILE *pos) {
    FILE *aux;
    aux = pos;
    char id[100];
    char buffer;
    //Estado q0
    fread(&buffer, sizeof(char), 1, aux);
    if (buffer == '<') {//Estado q1
        if (buffer == '=') {//Estado q2
            return buffer; //retorna  <= simb_meig
        } else if (buffer == '>') {//Estado q3
            return buffer; //retorna  <> simb_dif
        } else {//Estado q4
            return buffer; //retorna  > simb_menor
            // retroceder
        }
    } else if (buffer == '=') {// Estado q5
        return buffer; // retorna  = simb_ig
    } else if (buffer == '>') {// Estado q6
        if (buffer == '=') {// Estado q7
            return buffer; // retorna  <= simb_meig
        } else {//Estado q8
            return buffer; // retorna  > simb_maior
            // retroceder
        }
    }
}

char *automato_ident(FILE *pos) {
    FILE *aux;
    aux = pos;
    char id[100];
    char buffer;

    //Estado q0
    fread(&buffer, sizeof(char), 1, aux);


    if ((buffer >= 66 && buffer <= 90) || (buffer >= 97 && buffer <= 122)) {
        //Primeiro char eh letra

        //Estado q1
        while ((buffer >= 66 && buffer <= 90) || (buffer >= 97 && buffer <= 122))

    } else {
        print("Erro");
    }


}


int main() {
    printf("Hello world!\n");
    return 0;
}
