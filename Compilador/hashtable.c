#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../hashtable.h"
#define ERRO 0;
#define OK 1;

#define table_SIZE 1000;

char* getfield(char* line, int num)
{
    char* tok;
    for (tok = strtok(line, ";");
            tok && *tok;
            tok = strtok(NULL, ";\n"))
    {
        if (!--num)
            return tok;
    }
    return NULL;
}

char *ltrim(char *s)
{
    while(isspace(*s)) s++;
    return s;
}

char *rtrim(char *s)
{
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

char *trim(char *s)
{
    return rtrim(ltrim(s)); 
}

unsigned int
    hash(unsigned char *str)
    {
        unsigned int hash = 5381;
        int c;

        while (c = *str++)
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
        
        hash %= table_SIZE;

        return hash;
    }




//Insere tokens reconhecidos
void cria_hash(const char* fileName, dict** tabela){

    FILE* arq = fopen(fileName, "r");
    //Verifica arquivo aberto;
    if(arq == NULL){
        printf("insere_hash:\n");
        perror("Error");
        exit(0);
    }
    dict* elemento = (dict*)malloc(sizeof(dict));

    char* word;
    int hash_value;
    dict* next = NULL;
    while (fgets(word, 1024, arq))
    {
        dict* elemento = (dict*)malloc(sizeof(dict));
        char* trimmedWord = trim(word);
        hash_value = hash(trimmedWord)%1000;
        elemento->word = trimmedWord;
        if(tabela[hash_value] == NULL){
            tabela[hash_value] = elemento;
        }
        else{
            dict* atual = tabela[hash_value];
            dict* aux = tabela[hash_value]->next;
            while(aux!=NULL){
                atual = aux;
                aux = atual->next;
            }
            atual->next = elemento;
        }
        // NOTE strtok clobbers tmp
    }
}

int bate_hash(char* word, dict **tabela){
    char* trimmedWord = trim(word);
    int hash_value = hash(trimmedWord)%1000;
    if(tabela[hash_value] == NULL){
        return ERRO;
    }
    else{
        dict* no = tabela[hash_value];
        if(no->word == trimmedWord){
            return OK;
        }
        while(no = no->next){
            if(no->word == trimmedWord){
                return OK;
                break;
            }
        }
        return ERRO;
    }
}




int main()
{

    char* simb_reservados = "./dados/simbolosReservados.txt";
    dict** tabela;
    tabela = (dict**)malloc(1000*sizeof(dict*));
    for(int i =0; i<1000; i++)
    cria_hash(simb_reservados, tabela);

        for(int i=0; i< 1000; i++)
        {
            for(int j=0; i<100; i++)
            {
                printf("%s\n", tabela[i]->word);
            }
        }
    

    free(tabela);

}


