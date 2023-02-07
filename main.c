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

struct Data pegaLinha(int index)
{
    FILE *file;
    char linha[100];
    file = fopen("./dataset_formatado.csv", "r");
    if (file == NULL)
    {
        printf("error opening file");
    }
    fseek(file, (index - 1) * 41, SEEK_SET);
    if (fgets(linha, 100, file) == NULL)
    {
        printf("error reading line\n");
    }
    else
    {
        printf("linha %s\n", linha);
    }
}

struct Data *datasetReduzido(int linhas)
{
    FILE *file;
    struct Data *items = malloc(sizeof(struct Data) * linhas);
    file = fopen("./dataset_formatado.csv", "r");
    char ch;
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
        if (contador > 20) // esse numero sera trocado apos o tratamento de dados
        {
            if (ch != ',' && ch != '*')
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
            lineData.index = linha;
            items[adicionarEm] = lineData;
            adicionarEm++;
            linha++;
            // if (linha >= 128976)
            // { // EOF nao funcionando, ver isso hj

            //     break;
            // }
            int i = 0;
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
    // int linhas = 129000;
    // struct Data *items = datasetReduzido(linhas);
    // for (int i = 0; i < linhas; i++)
    // {
    //     printf("linha: %d, amount: %.2f\n", items[i].index, items[i].amount);
    // }

    pegaLinha(5);
    // quicck no items

    // de items gerar saida

    return 0;
}