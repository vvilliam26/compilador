#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct token {
    char simbolo_lido[50];
    char nome_simbolo[40];
} token;


int automato_operel_sinmat_atrib_dp(FILE *pos, char *token[2]) {
    FILE *aux;  // ponteiro ancora
    aux = pos; // ponteiro auxiliar q avanca
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
            return 1; // retorna true
        } else if (buffer == 62) {//Estado q3 '>'
            strcat(symbol, buffer);
            token[0] = symbol; // '<>'
            token[1] = simb_dif; // "simb_dif"
            return 1; // retorna true
        } else {//Estado q4
            token[0] = symbol; // '<'
            token[1] = simb_menor; // "simb_menor"
            aux--; //retroceder
            return 1; // retorna true
        }
    } else if (buffer == 61) { // Estado q5 '='
        token[0] = symbol; // '='
        token[1] = simb_ig; // "simb_ig"
        return 1; // retorna true
    } else if (buffer == 62) { // Estado q6 '>'
        fread(&buffer, sizeof(char), 1, aux);
        strcat(symbol, buffer);
        if (buffer == 61) {// Estado q7 '='
            strcat(symbol, buffer);
            token[0] = symbol; // '>='
            token[1] = simb_maig; // "simb_maig"
            return 1; // retorna true
        } else {//Estado q8
            token[0] = symbol; // '>'
            token[1] = simb_maior; // "simb_maior"
            aux--; //retroceder
            return 1; // retorna true
        }
    } else if (buffer == 43) { // Estado q9 '+'
        token[0] = symbol; // '+'
        token[1] = simb_soma; // "simb_soma"
        return 1; // retorna true
    } else if (buffer == 45) { // Estado q10 '-'
        token[0] = symbol; // '-'
        token[1] = simb_subt; // "simb_subt"
        return 1; // retorna true
    } else if (buffer == 42) { // Estado q11 '*'
        token[0] = symbol; // '*'
        token[1] = simb_mult; // "simb_mult"
        return 1; // retorna true
    } else if (buffer == 47) { // Estado q12 '/'
        token[0] = symbol; // '/'
        token[1] = simb_div; // "simb_div"
        return 1; // retorna true
    } else if (buffer == 58) { // Estado q13 ':'
        strcat(symbol, buffer);
        fread(&buffer, sizeof(char), 1, aux);
        if (buffer == 61) { //Estado q14 '='
            token[0] = symbol; // ':='
            token[1] = simb_atrib; // "simb_atrib"
            return 1; // retorna true
        } else { //Estado q15
            token[0] = symbol; // ':'
            token[1] = simb_dp; // "simb_dp"
            aux--; // retroceder
            return 1; // retorna true
        }
    } else{ // Estado q16 eh um caractere n aceito por este automato
        aux--; // retroceder
        return 0; // retorna false
    }
}


int automato_ident(FILE *pos, token* tk) {
    int pos_count = 0;
    char id[50];
    char buffer[2];
    char simb[] = "ident";

    //Estado q0
    fread(&buffer[0], sizeof(char), 1, pos);
    pos_count++;
    buffer[1] = '\0';


    if ((buffer[0] >= 66 && buffer[0] <= 90) || (buffer[0] >= 97 && buffer[0] <= 122)) {
        //Primeiro chars eh letra
        strcat(id, buffer);

        fread(&buffer[0], sizeof(char), 1, pos); //move o ponteiro
        //Estado q1
        while ((buffer[0] >= 48 && buffer[0] <= 57) || (buffer[0] >= 66 && buffer[0] <= 90) || (buffer[0] >= 97 && buffer[0] <= 122)) {
            strcat(id, &buffer);
            //caractere lido eh letra ou digito
            fread(&buffer[0], sizeof(char), 1, pos);
            pos_count++;
        }

        if(buffer[0] == ';' || buffer[0] == '*' || buffer[0] == '=')
        {
            //simbolo valido apos ident
            strcpy(tk->simbolo_lido,id);
            strcpy(tk->nome_simbolo,simb);
            fseek(pos, -1, SEEK_CUR);
            return 1;
        }

    } else {
//        printf("Identificador mal formatado");
        //identificador mal formado
        fseek(pos, -1 * pos_count, SEEK_CUR);
        return -1;
    }

    return 0;
}


int automato_palavraReservada(FILE *pos, token* tk) {
    int pos_count = 0;
    char palavra[50] = "";
    char buffer[2];
    char simb[40];

    fread(&buffer[0], sizeof(char), 1, pos);
//    pos_count++;
    buffer[1] = '\0';

    while ((buffer[0] >= 66 && buffer[0] <= 90) || (buffer[0] >= 97 && buffer[0] <= 122)) {
        //caractere lido eh letra
        strcat(palavra, buffer);
        fread(&buffer[0], sizeof(char), 1, pos);
        pos_count++;
    }

    if(strcmp(palavra,"program") == 0) {
        strcpy(tk->simbolo_lido,palavra);
        strcpy(tk->nome_simbolo,"simb_program");
        fseek(pos, -1, SEEK_CUR);
        return 1;
    } else {
        //nao eh palavra reservada
        fseek(pos, -1 * pos_count, SEEK_CUR);
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

    } else if(buffer >= 48 && buffer <= 57)
    {
        //estado qo -> q2 eh digito
        strcat(numero, &buffer);
    }else
    {
        //nao eh numero
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
            return -1;
        }

        fread(&buffer, sizeof(char), 1, aux);

        while (buffer >= 48 && buffer <= 57) {
            //eh digito
            strcat(numero, &buffer);
            fread(&buffer, sizeof(char), 1, aux);
        }
    } else if(buffer == 1)
    {
        //nao eh virgula mas eh um simbolo valido que encerra o numero inteiro
        token[0] = numero;
        token[1] = simb_int;
        pos = aux;
        fseek(pos, -1, SEEK_CUR);
        return 1;
    } else
    {
        //simbolo invalido -> numero mal formatado
        return -1;
    }

    if(buffer == ';')
    {
        //simb valido para determinar o numero real
        token[0] = numero;
        token[1] = simb_real;
        pos = aux;
        fseek(pos, -1, SEEK_CUR);
        return 1;
    } else {
        //numero mal formatado
        return -1;
    }


    return 0;
}


int automato_comentario(FILE *pos, char *token) {
    FILE *aux;
    aux = pos;
    char chaves[2] = "{}";
    char buffer;
    char simb_coment[] = "simb_comentario";

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
            pos = aux;
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

int automato_parPontoPv(FILE* pos, char* token) {
    FILE *aux;
    aux = pos;
    char buffer;
    char simb_apar[] = "simb_apar";
    char simb_fpar[] = "simb_fpar";
    char simb_p[] = "simb_p";
    char simb_v[] = "simb_v";
    char simb_pv[] = "simb_pv";

    fread(&buffer, sizeof(char), 1, aux);

    switch(buffer)
    {
        case '(':
            token[0] = &buffer;
            token[1] = simb_apar;
            pos = aux;
            return 1;
        break;

        case ')':
            token[0] = &buffer;
            token[1] = simb_fpar;
            pos = aux;
            return 1;
        break;

        case '.':
            token[0] = &buffer;
            token[1] = simb_p;
            pos = aux;
            return 1;
        break;

        case ',':
            token[0] = &buffer;
            token[1] = simb_v;
            pos = aux;
            return 1;
        break;

        case 'pv':
            token[0] = &buffer;
            token[1] = simb_pv;
            pos = aux;
            return 1;
        break;

        default:
            //nao eh nenhum simbolo acima
            return 0;
    }

    return 0;
}


int main() {
    FILE* pos;
//    char *filename;
    token tk;

//    printf("Digite o nome do arquivo");
//    scanf("%s", filename);


    pos = fopen("../../casos_Teste/1.txt", "r");


    while(feof(pos) == 0)
    {
        if(automato_palavraReservada(pos, &tk) == 1)
        {
            printf("%s,%s",tk.simbolo_lido,tk.nome_simbolo);
        }
        else if(automato_ident(&pos,&tk) == 1) {
            printf("%s,%s\n",tk.simbolo_lido,tk.nome_simbolo);
        }
    }

    fclose(pos);

    return 0;
}
