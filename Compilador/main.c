#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct token {
    char simbolo_lido[50];
    char nome_simbolo[40];
} token;

int checa_palavraReservada(char* palavra, token* tk) {
    if(strcmp(palavra,"var") == 0)
    {
        strcpy(tk->nome_simbolo, "simb_var");
        return 1;
    }
    else if(strcmp(palavra,"program") == 0)
    {
        strcpy(tk->nome_simbolo, "simb_program");
        return 1;
    }
    else if(strcmp(palavra,"begin") == 0)
    {
        strcpy(tk->nome_simbolo, "simb_begin");
        return 1;
    }
     else if(strcmp(palavra,"end") == 0)
    {
        strcpy(tk->nome_simbolo, "simb_end");
        return 1;
    }
     else if(strcmp(palavra,"const") == 0)
    {
        strcpy(tk->nome_simbolo, "simb_const");
        return 1;
    }
     else if(strcmp(palavra,"real") == 0)
    {
        strcpy(tk->nome_simbolo, "simb_real");
        return 1;
    }
     else if(strcmp(palavra,"integer") == 0)
    {
        strcpy(tk->nome_simbolo, "simb_integer");
        return 1;
    }
     else if(strcmp(palavra,"procedure") == 0)
    {
        strcpy(tk->nome_simbolo, "simb_procedure");
        return 1;
    }
     else if(strcmp(palavra,"else") == 0)
    {
        strcpy(tk->nome_simbolo, "simb_else");
        return 1;
    }
     else if(strcmp(palavra,"read") == 0)
    {
        strcpy(tk->nome_simbolo, "simb_read");
        return 1;
    }
     else if(strcmp(palavra,"write") == 0)
    {
        strcpy(tk->nome_simbolo, "simb_write");
        return 1;
    }
         else if(strcmp(palavra,"while") == 0)
    {
        strcpy(tk->nome_simbolo, "simb_while");
        return 1;
    }
     else if(strcmp(palavra,"if") == 0)
    {
        strcpy(tk->nome_simbolo, "simb_if");
        return 1;
    }
     else if(strcmp(palavra,"do") == 0)
    {
        strcpy(tk->nome_simbolo, "simb_do");
        return 1;
    }
     else if(strcmp(palavra,"then") == 0)
    {
        strcpy(tk->nome_simbolo, "simb_then");
        return 1;
    }
     else if(strcmp(palavra,"for") == 0)
    {
        strcpy(tk->nome_simbolo, "simb_for");
        return 1;
    }

    return 0;
}

int valida_simbolo(char* simb) {
    if(strcmp(simb, "="))
        return 1;
    else if(strcmp(simb, "<>"))
        return 1;
    else if(strcmp(simb, ">="))
        return 1;
    else if(strcmp(simb, "<="))
        return 1;
    else if(strcmp(simb, ">"))
        return 1;
    else if(strcmp(simb, "<"))
        return 1;
    else if(strcmp(simb, "+"))
        return 1;
    else if(strcmp(simb, "-"))
        return 1;
    else if(strcmp(simb, "*"))
        return 1;
    else if(strcmp(simb, "/"))
        return 1;
    else if(strcmp(simb, ";"))
        return 1;
    else if(strcmp(simb, ":"))
        return 1;
    else if(strcmp(simb, ":="))
        return 1;
    else if(strcmp(simb, "("))
        return 1;
    else if(strcmp(simb, ")"))
        return 1;
    else if(strcmp(simb, "."))
        return 1;

    return 0;
}

int automato_operel_sinmat_atrib_dp(FILE *pos, token* tk) {
    char symbol[3];
    char buffer[2];
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
    fread(&buffer[0], sizeof(char), 1, pos);
    buffer[1] = '\0';

    symbol[0] = buffer[0];

    if (buffer[0] == 60) {//Estado q1 '<'
        fread(&buffer[0], sizeof(char), 1, pos);

        if (buffer[0] == 61) {//Estado q2 '='
            strcat(symbol, buffer);//
            strcpy(tk->simbolo_lido, symbol); // '<='
            strcpy(tk->nome_simbolo, simb_meig); // "simb_meig"
            return 1; // retorna true
        } else if (buffer[0] == 62) {//Estado q3 '>'
            strcat(symbol, buffer);
            strcpy(tk->simbolo_lido, symbol); // '<>'
            strcpy(tk->nome_simbolo, simb_dif); // "simb_dif"
            return 1; // retorna true
        } else {//Estado q4
            strcpy(tk->simbolo_lido, symbol); // '<'
            strcpy(tk->nome_simbolo, simb_menor); // "simb_menor"
            fseek(pos, -1, SEEK_CUR);
            return 1; // retorna true
        }
    } else if (buffer[0] == 61) { // Estado q5 '='
        strcpy(tk->simbolo_lido, buffer); // '='
        strcpy(tk->nome_simbolo, simb_ig); // "simb_ig"
        return 1; // retorna true
    } else if (buffer[0] == 62) { // Estado q6 '>'
        fread(&buffer[0], sizeof(char), 1, pos);

        if (buffer[0] == 61) {// Estado q7 '='
            strcat(symbol, buffer);
            strcpy(tk->simbolo_lido, symbol); // '>='
            strcpy(tk->nome_simbolo, simb_maig); // "simb_maig"
            return 1; // retorna true
        } else {//Estado q8
            strcpy(tk->simbolo_lido, symbol); // '>'
            strcpy(tk->nome_simbolo, simb_maior); // "simb_maior"
            fseek(pos, -1, SEEK_CUR); //retroceder
            return 1; // retorna true
        }
    } else if (buffer[0] == 43) { // Estado q9 '+'
        strcpy(tk->simbolo_lido, buffer); // '+'
        strcpy(tk->nome_simbolo, simb_soma); // "simb_soma"
        return 1; // retorna true
    } else if (buffer[0] == 45) { // Estado q10 '-'
        strcpy(tk->simbolo_lido, buffer); // '-'
        strcpy(tk->nome_simbolo, simb_subt); // "simb_subt"
        return 1; // retorna true
    } else if (buffer[0] == 42) { // Estado q11 '*'
        strcpy(tk->simbolo_lido, buffer); // '*'
        strcpy(tk->nome_simbolo, simb_mult); // "simb_mult"
        return 1; // retorna true
    } else if (buffer[0] == 47) { // Estado q12 '/'
        strcpy(tk->simbolo_lido, buffer); // '/'
        strcpy(tk->nome_simbolo, simb_div); // "simb_div"
        return 1; // retorna true
    } else if (buffer[0] == 58) { // Estado q13 ':'
        fread(&buffer[0], sizeof(char), 1, pos);
        if (buffer[0] == 61) { //Estado q14 '='
            strcat(symbol,buffer);
            strcpy(tk->simbolo_lido, symbol); // ':='
            strcpy(tk->nome_simbolo, simb_atrib); // "simb_atrib"
            return 1; // retorna true
        } else { //Estado q15
            strcpy(tk->simbolo_lido, symbol); // ':'
            strcpy(tk->nome_simbolo, simb_dp); // "simb_dp"
            fseek(pos, -1, SEEK_CUR); // retroceder
            return 1; // retorna true
        }
    } else{ // Estado q16 eh um caractere n aceito por este automato
        fseek(pos, -1, SEEK_CUR); // retroceder
        return 0; // retorna false
    }
}

int automato_ident(FILE *pos, token* tk) {
//    int pos_count = 0;
    char id[50];
    char buffer[2];
    char simb_ident[] = "ident";

    //Estado q0
    fread(&buffer[0], sizeof(char), 1, pos);
//    pos_count++;
    buffer[1] = '\0';


    if ((buffer[0] >= 66 && buffer[0] <= 90) || (buffer[0] >= 97 && buffer[0] <= 122)) {
        //Primeiro chars eh letra
        strcat(id, buffer);

        fread(&buffer[0], sizeof(char), 1, pos); //move o ponteiro
//        pos_count++;
        //Estado q1
        while ((buffer[0] >= 48 && buffer[0] <= 57) || (buffer[0] >= 66 && buffer[0] <= 90) || (buffer[0] >= 97 && buffer[0] <= 122)) {
            strcat(id, buffer);
            //caractere lido eh letra ou digito
            fread(&buffer[0], sizeof(char), 1, pos);
//            pos_count++;
        }

        if(valida_simbolo(buffer) == 1)
        {
            //simbolo valido apos ident
            strcpy(tk->simbolo_lido,id);
            strcpy(tk->nome_simbolo,simb_ident);
            fseek(pos, -1, SEEK_CUR);
            return 1;
        } else {
            //identificador mal formatado
            fseek(pos, -1, SEEK_CUR);
            return 0;
        }

    } else {
        //nao eh ident
        fseek(pos, -1, SEEK_CUR);
        return 0;
    }

    return 0;
}

int automato_palavraReservada(FILE *pos, token* tk) {
    int pos_count = 0;
    char palavra[50] = "";
    char buffer[2];
    char simb[40];

    fread(&buffer[0], sizeof(char), 1, pos);
    pos_count++;
    buffer[1] = '\0';

    while ((buffer[0] >= 66 && buffer[0] <= 90) || (buffer[0] >= 97 && buffer[0] <= 122)) {
        //caractere lido eh letra
        strcat(palavra, buffer);
        fread(&buffer[0], sizeof(char), 1, pos);
        pos_count++;
    }

    if(checa_palavraReservada(palavra, tk) == 1) {
        strcpy(tk->simbolo_lido,palavra);
        fseek(pos, -1, SEEK_CUR);
        return 1;
    } else {
        //nao eh palavra reservada
        fseek(pos, -1 * pos_count, SEEK_CUR);
        return 0;
    }

    return 0;
}

int automato_numero(FILE *pos, token* tk) {
    char numero[50] = "";
    char buffer[2];
    char simb_int[] = "num_int";
    char simb_real[] = "num_real";

    fread(&buffer[0], sizeof(char), 1, pos);
    buffer[1]='\0';

    //estado q0 -> q1
//    if (buffer[0] == 43 || buffer[0] == 45) {
//        buffer eh +, -
//        strcat(numero, buffer);
//
//    } else
    if(buffer[0] >= 48 && buffer[0] <= 57)
    {
        //estado qo -> q2 eh digito
        strcat(numero, buffer);
    }else
    {
        //nao eh numero
        fseek(pos, -1, SEEK_CUR);
        return 0;
    }

    fread(&buffer[0], sizeof(char), 1, pos);

    //estado q2
    while (buffer[0] >= 48 && buffer[0] <= 57) {
        //eh digito
        strcat(numero, buffer);
        fread(&buffer[0], sizeof(char), 1, pos);
    }

    //checando o simbolo pos digito
    if (buffer[0] == 46) {
        //eh ponto
        strcat(numero, buffer);
        fread(&buffer[0], sizeof(char), 1, pos);

        if (buffer[0] >= 48 && buffer[0] <= 57) {
            //pelo menos um digito pos virgula
            strcat(numero, buffer);
        } else {
            //numero mal formatado
            fseek(pos, -1, SEEK_CUR);
            return -1;
        }

        fread(&buffer[0], sizeof(char), 1, pos);

        while (buffer[0] >= 48 && buffer[0] <= 57) {
            //eh digito
            strcat(numero, buffer);
            fread(&buffer[0], sizeof(char), 1, pos);
        }
    } else if(valida_simbolo(buffer) == 1)
    {
        //nao eh virgula mas eh um simbolo valido que encerra o numero inteiro
        strcpy(tk->simbolo_lido,numero);
        strcpy(tk->nome_simbolo,simb_int);
        fseek(pos, -1, SEEK_CUR);
        return 1;
    } else
    {
        //simbolo invalido -> numero mal formatado
        fseek(pos, -1, SEEK_CUR);
        return -1;
    }

    if(buffer[0] == ';')
    {
        //simb valido para determinar o numero real
        strcpy(tk->simbolo_lido,numero);
        strcpy(tk->nome_simbolo,simb_real);
        fseek(pos, -1, SEEK_CUR);
        return 1;
    } else {
        //numero mal formatado
        fseek(pos, -1, SEEK_CUR);
        return -1;
    }


    return 0;
}

int automato_comentario(FILE *pos, token* tk) {
    char chaves[2] = "{}";
    char buffer[2];
    char simb_coment[] = "simb_comentario";

    fread(&buffer[0], sizeof(char), 1, pos);
    buffer[1]='\0';

    if (buffer[0] == 123) {
        //abre chaves
        fread(&buffer[0], sizeof(char), 1, pos);
        while (buffer[0] != 125 && buffer[0] != EOF) {
            //comentario nao fechado
            fread(&buffer[0], sizeof(char), 1, pos);
        }

        if (buffer[0] == 125) {
            strcpy(tk->simbolo_lido,chaves);
            strcpy(tk->nome_simbolo,simb_coment);
            fseek(pos, -1, SEEK_CUR);
            return 1;
        } else {
            //comentario nao fechado
            return -1;
        }

    } else {
        //nao eh comentario
        fseek(pos, -1, SEEK_CUR);
        return 0;
    }

    return 0;
}

int automato_parPontoPv(FILE* pos, token* tk) {
    char buffer[2];
    char simb_apar[] = "simb_apar";
    char simb_fpar[] = "simb_fpar";
    char simb_p[] = "simb_p";
    char simb_v[] = "simb_v";
    char simb_pv[] = "simb_pv";

    fread(&buffer[0], sizeof(char), 1, pos);
    buffer[1]='\0';

    switch(buffer[0])
    {
        case '(':
            strcpy(tk->simbolo_lido,buffer);
            strcpy(tk->nome_simbolo,simb_apar);
            return 1;
        break;

        case ')':
            strcpy(tk->simbolo_lido,buffer);
            strcpy(tk->nome_simbolo,simb_fpar);
            return 1;
        break;

        case '.':
            strcpy(tk->simbolo_lido,buffer);
            strcpy(tk->nome_simbolo,simb_p);
            return 1;
        break;

        case ',':
            strcpy(tk->simbolo_lido,buffer);
            strcpy(tk->nome_simbolo,simb_v);
            return 1;
        break;

        case ';':
            strcpy(tk->simbolo_lido,buffer);
            strcpy(tk->nome_simbolo,simb_pv);
            return 1;
        break;

        default:
            //nao eh nenhum simbolo acima
            fseek(pos, -1, SEEK_CUR); //retroceder()
            return 0;
    }

    return 0;
}

int automato_caractereInvalido(FILE* pos, token* tk){
    char buffer[2];

    fread(&buffer[0], sizeof(char), 1, pos);
    buffer[1]='\0';

    if(buffer[0] == '\n' || buffer[0] == ' ' || buffer[0] == '\t'){
        //ignorar
        return 0;
    }

    strcpy(tk->simbolo_lido, buffer);
    strcpy(tk->nome_simbolo, "erro(\"caractere nao permitido\")");

    return 1;
}

int main() {
    FILE* pos;
//    char filename[50];
    token tk;
    char c;

//    printf("Digite o nome do arquivo");
//    scanf("%s", filename);


    pos = fopen("../casos_Teste/1.txt", "r");

    if(!pos) {
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }


    while((c = getc(pos) ) != EOF)
    {
        fseek(pos,-1,SEEK_CUR);
        if(automato_palavraReservada(pos, &tk) == 1)
        {
            printf("%s,%s\n",tk.simbolo_lido,tk.nome_simbolo);
        }
        else if(automato_ident(pos,&tk) == 1) {
            printf("%s,%s\n",tk.simbolo_lido,tk.nome_simbolo);
        }
        else if(automato_parPontoPv(pos,&tk) == 1)
        {
            printf("%s,%s\n",tk.simbolo_lido,tk.nome_simbolo);
        }
        else if(automato_comentario(pos,&tk) == 1)
        {
            printf("%s,%s\n",tk.simbolo_lido,tk.nome_simbolo);
        }
        else if(automato_numero(pos,&tk) == 1)
        {
            printf("%s,%s\n",tk.simbolo_lido,tk.nome_simbolo);
        }
        else if(automato_operel_sinmat_atrib_dp(pos,&tk) == 1)
        {
            printf("%s,%s\n",tk.simbolo_lido,tk.nome_simbolo);
        }
        else if(automato_caractereInvalido(pos,&tk) == 1)
        {
            printf("%s,%s\n",tk.simbolo_lido,tk.nome_simbolo);
        }

    }

    fclose(pos);

    return 0;
}
