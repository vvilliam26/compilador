#include <stdio.h>
#include <stdlib.h>
#include <string.h>



char* automato_ident(FILE *pos) {
    FILE *aux
    aux = pos;
    char id [100];
    char buffer

    //Estado q0
    fread(&buffer, sizeof(char), 1, aux);


    if((buffer >= 66 && buffer <= 90) || (buffer >= 97 && buffer <= 122))
    {
        //Primeiro char eh letra
        strcat(id, buffer);

        //Estado q1
        while((buffer >= 48 && buffer <= 57) || (buffer >= 66 && buffer <= 90) || (buffer >= 97 && buffer <= 122))
        {
            fread(&buffer, sizeof(char), 1, aux);
            strcat(id, buffer);
        }

        if(BATE_HASH(buffer) == true)
        {

        }

    } else {
        print("Identificador mal formatado");
    }




}


int main()
{
    printf("Hello world!\n");
    return 0;
}
