#ifndef HASHTABLE_H
#define HASHTABLE_H


typedef struct dict{
    char* word;
    dict* next;
} dict;

char* getfield(char*, int);
char *ltrim(char *);
char *rtrim(char *);
char *trim(char *);
unsigned int hash(unsigned char *);

int insere_hash(const char*, char**);

#endif