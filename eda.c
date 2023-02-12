#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 typedef struct
{
    double amount;
} Amazon;


int retornaItens(int linha, Amazon *itens){
    FILE *file;

    file = fopen("dataset_formatado.csv", "r");

    if (file == NULL){
    printf("Arquivo não encontrado.\n");
    return 0;
    }

    char *buffer = malloc(sizeof(linha)); //precisa do sizeof? e seria amazon ou linha?
    int i = 1;
    char *field;

    while(fgets(buffer, linha, file)){


        field = strtok(buffer, ",");
  
        field = strtok(NULL, ",");
        itens[i].amount = (field? atof(field): 0.0);

        //printf("linha = %i, valor = %f\n", i, itens[i].amount);
        i++;
    }

    fclose(file);
    return 0;
}

int main(){  
     
    Amazon *itens = malloc(sizeof(Amazon) * 1100);

    int i=5;
    retornaItens(50, itens);

    //for (i = 0; i <= sizeof(itens); i++){

    printf("linha = %i, valor = %f\n", i, itens[i].amount);

    //}

    return 0;
}


