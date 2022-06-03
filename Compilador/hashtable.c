#include<stdio.h>
#include <stdlib.h>
#include <string.h>

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

unsigned long
    hash(unsigned char *str)
    {
        unsigned long hash = 5381;
        int c;

        while (c = *str++)
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

        return hash;
    }

int main(){
    FILE* fPtr;
    fPtr = fopen("./dados/simbolosReservados.csv", "r");
    if(fPtr == NULL)
    {
        /* File not created hence exit */
        perror("Error");
        exit(0);
    }
    char** table;
    table = (char**)malloc(1000*sizeof(char*));
    for(int i =0; i<1000; i++){
        table[i]=(char*)malloc(30*sizeof(char));
        table[i][0] = '\0';
    }
    char line[1024];
    while (fgets(line, 1024, fPtr))
    {
        char* tmp = strdup(line);
        tmp = getfield(tmp, 1);
        char* trimmedtmp = trim(tmp);
        unsigned long hashvalue = hash(trimmedtmp);
        table[hashvalue%1000] = trimmedtmp;
        // NOTE strtok clobbers tmp
    }
    for(int i=0; i< 1000; i++)
    {
        if(table[i][0]!='\0')
        for(int j=0; i<100; i++){
            printf("%s\n", table[i]);
        }
    }


}


