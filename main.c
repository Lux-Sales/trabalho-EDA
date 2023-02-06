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

struct Data
{
    int index;
    float amount;
};

struct Data *datasetReduzido(int linhas)
{
    FILE *file;
    struct Data *items = malloc(sizeof(struct Data) * linhas);
    file = fopen("./dataset.csv", "r");
    char ch;
    char index = -1;
    char indexStr[100] = "";
    char amountStr[100] = "";
    int adicionarEm = 0;
    float amount = 0;
    int contador = 0;
    int linha = 1;
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
            if (ch != ',')
            {
                strncat(amountStr, &ch, 1);
                amount = atof(amountStr);
            }
        }
        if (ch == '\n')
        {
            // leu a linha inteira, adiciona no vetor de structs {index, amount}
            // limpa os vetores também
            // printf("linha: %d, index: %d, amount:%.2f\n", linha, index, amount);
            if (adicionarEm > linhas)
            {
                break;
            }
            struct Data lineData;
            lineData.amount = amount;
            lineData.index = index;
            items[adicionarEm] = lineData;
            adicionarEm++;
            linha++;
            // if (linha >= 128976)
            // { // EOF nao funcionando, ver isso hj

            //     break;
            // }
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
    return items;
}

int main()
{
    struct Data *items = datasetReduzido(128975);
    printf("////////////////////////////////////////////////////////////////////\n LEU TUDO VAI IMPRIMIR //////////////////////////////////////////////////////////////////////////\n");
    for (int i = 0; i < 128975; i++)
    {
        printf("index: %d, amount: %.2f\n", items[i].index, items[i].amount);
    }
    return 0;
}