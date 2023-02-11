#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 typedef struct
{
    int id;
    char category[100];
    double amount;
} Amazon;

Amazon itens[10];

int retornaItens(int linhas){
    FILE *file;

    file = fopen("teste.csv", "r");

    if (file == NULL){
    printf("Arquivo não encontrado.\n");
    return 0;
    }

    char *buffer = malloc(sizeof(linhas));
    int i = 0;
    char *field = NULL;

    while(fgets(buffer, linhas, file)){
        if ((strlen(buffer)>0) && (buffer[strlen (buffer) - 1] == '\n'))
            buffer[strlen (buffer) - 1] = '\0';

        field = strtok(buffer, ";");
        itens[i].id = atoi(field? field:"");
        field = strtok(NULL, ";");
        strcpy(itens[i].category, (field?:""));
        field = strtok(NULL, ";");
        itens[i].amount = atoi(field?:"");

        printf("id = %i, categoria = %s, valor = %i\n", itens[i].id, itens[i].category, itens[i].amount);
        i++;

    }

    fclose(file);
    return 0;
}

int main()
{   
    retornaItens(10);
    return 0;
}

