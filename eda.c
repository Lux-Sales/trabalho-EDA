#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    double amount;
} Amazon;

int retornaItens(int linha, Amazon *itens)
{
    FILE *file;

    file = fopen("dataset_formatado.csv", "r");

    if (file == NULL)
    {
        printf("Arquivo não encontrado.\n");
        return 0;
    }

    char *buffer = malloc(sizeof(linha)); // precisa do sizeof? e seria amazon ou linha?
    int i = 1;
    char *field;

    while (fgets(buffer, linha, file))
    {

        field = strtok(buffer, ",");

        field = strtok(NULL, ",");
        itens[i].amount = atof(field);

        // printf("linha = %i, valor = %f\n", i, itens[i].amount);
        i++;
    }

    printf("linha = %i, valor = %f\n", 99, itens[99].amount);

    fclose(file);
    return 0;
}

int main()
{

    Amazon *itens = malloc(sizeof(Amazon) * 1100000);

    int i = 1200;

    retornaItens(50, itens);

<<<<<<< HEAD
    // printf("linha = %i, valor = %f\n", i, itens[i].amount);
=======
    printf("linha = %i, valor = %f\n", i, itens[i].amount);
>>>>>>> d7472814905beeb9a905ab0516805ade5afcd147

    return 0;
}
