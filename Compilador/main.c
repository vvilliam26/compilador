#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int automato_operel_sinmat_atrib_dp(FILE *pos, char *token[2]) {
    FILE *aux;
    aux = pos;
    char symbol[2];
    char buffer;
    char simb_meig[] = "simb_meig";
    char simb_dif[] = "simb_dif";
    char simb_menor[] = "simb_menor";
    char simb_ig[] = "simb_ig";
    char simb_maig[] = "simb_maig";
    char simb_maior[] = "simb_maior";
    char simb_soma[] = "simb_soma";
    char simb_subt[] = "simb_subt";
    char simb_mult[] = "simb_mult";
    char simb_div[] = "simb_div";
    char simb_dp[] = "simb_dp";
    char simb_atrib[] = "simb_atrib";
    //Estado q0
    fread(&buffer, sizeof(char), 1, aux);
    if (buffer == 60) {//Estado q1 '<'
        strcat(symbol, buffer);
        fread(&buffer, sizeof(char), 1, aux);
        if (buffer == 61) {//Estado q2 '='
            strcat(symbol, buffer);//
            token[0] = symbol; // '<='
            token[1] = simb_meig; // "simb_meig"
            return 1;
        } else if (buffer == 62) {//Estado q3 '>'
            strcat(symbol, buffer);
            token[0] = symbol; // '<>'
            token[1] = simb_dif; // "simb_dif"
            return 1;
        } else {//Estado q4
            token[0] = symbol; // '<'
            token[1] = simb_menor; // "simb_menor"
            aux--; //retroceder
            return 1;
        }
    } else if (buffer == 61) { // Estado q5 '='
        token[0] = symbol; // '='
        token[1] = simb_ig; // "simb_ig"
        return 1;
    } else if (buffer == 62) { // Estado q6 '>'
        fread(&buffer, sizeof(char), 1, aux);
        strcat(symbol, buffer);
        if (buffer == 61) {// Estado q7 '='
            strcat(symbol, buffer);
            token[0] = symbol; // '<='
            token[1] = simb_meig; // "simb_meig"
            return 1;
        } else {//Estado q8
            token[0] = symbol; // '>'
            token[1] = simb_maior; // "simb_maior"
            aux--; //retroceder
            return 1;
        }
    } else if (buffer == 43) { // Estado q9 '+'
        token[0] = symbol; // '+'
        token[1] = simb_soma; // "simb_soma"
        return 1;
    } else if (buffer == 45) { // Estado q10 '-'
        token[0] = symbol; // '-'
        token[1] = simb_subt; // "simb_subt"
        return 1;
    } else if (buffer == 42) { // Estado q11 '*'
        token[0] = symbol; // '*'
        token[1] = simb_mult; // "simb_mult"
        return 1;
    } else if (buffer == 47) { // Estado q12 '/'
        token[0] = symbol; // '/'
        token[1] = simb_div; // "simb_div"
        return 1;
    } else if (buffer == 58) { // Estado q13 ':'
        strcat(symbol, buffer);
        fread(&buffer, sizeof(char), 1, aux);
        if (buffer == 61) { //Estado q15 '='
            token[0] = symbol; // ':='
            token[1] = simb_atrib; // "simb_atrib"
            return 1;
        } else { //Estado q14
            token[0] = symbol; // ':'
            token[1] = simb_dp; // "simb_dp"
            aux--; // retroceder
            return 1;
        }
    }
}

int automato_ident(FILE *pos, char *token[2]) {
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
        while ((buffer >= 48 && buffer <= 57) || (buffer >= 66 && buffer <= 90) || (buffer >= 97 && buffer <= 122)) {
            strcat(id, &buffer);
            //caractere lido eh letra ou digito
            fread(&buffer, sizeof(char), 1, aux);

        }

        if (/*BATE_HASH(buffer) == 1*/1) {
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


int automato_palavraReservada(FILE *pos, char *token) {
    FILE *aux;
    aux = pos;
    char palavra[100];
    char buffer;
    char *simb;

    fread(&buffer, sizeof(char), 1, aux);

    while ((buffer >= 66 && buffer <= 90) || (buffer >= 97 && buffer <= 122)) {
        //caractere lido eh letra
        strcat(palavra, &buffer);
        fread(&buffer, sizeof(char), 1, aux);
    }

    if (/*BATE_HASH(palavra, &simb) == 1 */) {
        token[0] = palavra;
        token[1] = simb;

        return 1;
    } else {
        return 0;
    }

    return 0;
}


int automato_numero(FILE *pos, char *token) {
    FILE *aux;
    aux = pos;
    char numero[100];
    char buffer;
    char simb_int[] = "num_int";
    char simb_real[] = "num_real";

    fread(&buffer, sizeof(char), 1, aux);

    //estado q0 -> q1
    if (buffer == 43 || buffer == 45) {
        //buffer eh +, - ou digito
        strcat(numero, &buffer);

    } else if (buffer >= 48 && buffer <= 57) {
        //estado qo -> q2
        strcat(numero, &buffer);
    } else {
        return 0;
    }

    fread(&buffer, sizeof(char), 1, aux);

    //estado q2
    while (buffer >= 48 && buffer <= 57) {
        //eh digito
        strcat(numero, &buffer);
        fread(&buffer, sizeof(char), 1, aux);
    }

    //checando o simbolo pos digito
    if (buffer == 44) {
        //eh virgula
        fread(&buffer, sizeof(char), 1, aux);

        if (buffer >= 48 && buffer <= 57) {
            //pelo menos um digito pos virgula
            strcat(numero, &buffer);
        } else {
            //numero mal formatado
            return 0;
        }

        fread(&buffer, sizeof(char), 1, aux);

        while (buffer >= 48 && buffer <= 57) {
            //eh digito
            strcat(numero, &buffer);
            &buffer, sizeof(char), 1, aux);
        }
        fread(
    } else if (buffer == SIMB_VALIDO) {
        //nao eh virgula mas eh um simbolo valido que encerra o numero inteiro
        token[0] = numero;
        token[1] = simb_int;
        return 1;
    } else {
        //simbolo invalido
        return 0;
    }

    if (buffer == SIMB_VALIDO) {
        //simb valido para determinar o numero real
        token[0] = numero;
        token[1] = simb_real;
        return 1;
    } else {
        //numero mal formatado
        return 0;
    }


    return 0;
}


int automato_comentario(FILE *pos, char *token) {
    FILE *aux;
    aux = pos;
    char chaves[2] = "{}";
    char buffer;
    char simb_coment = "simb_comentario";

    fread(&buffer, sizeof(char), 1, aux);

    if (buffer == 123) {
        //abre chaves
        fread(&buffer, sizeof(char), 1, aux);
        while (buffer != 125 && buffer != EOF) {
            //comentario nao fechado
            fread(&buffer, sizeof(char), 1, aux);
        }

        if (buffer == 125) {
            token[0] = chaves;
            token[1] = simb_coment;
            return 1;
        } else {
            //comentario nao fechado
            return -1;
        }

    } else {
        //nao eh comentario
        return 0;
    }

    return 0;
}

int automato_parPontoPv(FILE *pos, char *token) {

}

int main() {
    printf("Hello world!\n");
    return 0;
}
