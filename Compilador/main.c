#include <stdio.h>
#include <stdlib.h>
#include <string.h>



char* automato_ident(FILE *pos) {
    FILE *aux;
    aux = pos;
    char id [100];
    char buffer;

    //Estado q0
    fread(&buffer, sizeof(char), 1, aux);


    if((buffer >= 66 && buffer <= 90) || (buffer >= 97 && buffer <= 122))
    {
        //Primeiro char eh letra

        //Estado q1
        while((buffer >= 66 && buffer <= 90) || (buffer >= 97 && buffer <= 122)){
            
        }

    } else {
        print("Erro");
    }




}


int main()
{
    printf("Hello world!\n");
    return 0;
}
