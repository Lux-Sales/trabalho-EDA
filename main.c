#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
O que precisamos?

fora do codigo:

1 - tratar dataset para que todos os dados tenham o mesmo tamanho, para que a gente
consiga buscar depois da ordenação os valores.
2 - Calcular complexidade computacional do algoritmo


dentro do codigo:

1 - Fazer função que pega x linhas aleatórias e cria um dataset para testarmos com um
dataset reduzido
2 - Ler dataset e fazer vetor de structs
3 - Ordenar de forma decrescente com quick sort utilizando o campo amount do dataset.
4 - Escrever em um arquivo esse vetor ordenado
5 - Calcular tempo de processamento
*/

typedef struct
{
    int index;
    float amount;
} Data;

struct Data *datasetReduzido(int linhas)
{
    FILE *file;
    struct Data *items = malloc(sizeof(Data) * linhas);
    file = fopen("./dataset.csv", "r");
    char ch;
    char index = -1;
    char indexStr[100] = "";
    char amountStr[100] = "";
    float amount = 0;
    int contador = 0;
    if (file == NULL)
    {
        printf("error opening file");
        exit(1);
    }
    do
    {
        ch = fgetc(file);
        if (contador >= 0 && contador < 1) // esses numeros serao trocados apos o tratamento de dados
        {
            strncat(indexStr, &ch, 1);
            index = atoi(indexStr);
        }
        if (contador > 5) // esse numero sera trocado apos o tratamento de dados
        {
            if (ch != ",")
            {
                strncat(amountStr, &ch, 1);
                amount = atof(amountStr);
            }
        }
        if (ch == '\n')
        {
            printf("index: %d, amount:%.2f\n", index, amount);
            int i = 0;
            for (i = 0; i < 5; i++)
            {
                indexStr[i] = '\000';
            }
            for (i = 0; i < 10; i++)
            {
                amountStr[i] = '\000';
            }
            contador = -1;
        }
        contador++;
    } while (ch != EOF);
}

int main()
{
    datasetReduzido(2);
    return 0;
}