#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
O que precisamos?

fora do codigo:

1 - tratar dataset para que todos os dados tenham o mesmo tamanho, para que a gente
consiga buscar depois da ordenação os amountes.
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

struct Data *datasetReduzido()
{
    FILE *file;
    file = fopen("./dataset_formatado.csv", "r");
    struct Data *Datas = malloc(sizeof(struct Data) * 128975);
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
        if (ch == '\377')
        {
            break;
        }
        if (contador > 19) // esse numero sera trocado apos o tratamento de dados
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
            struct Data lineData;
            lineData.amount = amount;
            lineData.index = linha;
            Datas[adicionarEm] = lineData;
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
    return Datas;
}

// Funcao para comparar duas structs
int compare(const void *a, const void *b)
{
    struct Data *ia = (struct Data *)a;
    struct Data *ib = (struct Data *)b;
    return (ib->amount - ia->amount);
}

// QuickSort
void QuickSort(struct Data *v, int l, int r)
{
    int i, j;
    struct Data x, w;
    i = l;
    j = r;
    x = v[(l + r) / 2];
    do
    {
        while (v[i].amount > x.amount && i < r)
        {
            i++;
        }
        while (v[j].amount < x.amount && j > l)
        {
            j--;
        }
        if (i <= j)
        {
            w = v[i];
            v[i] = v[j];
            v[j] = w;
            i++;
            j--;
        }
    } while (i <= j);
    if (l < j)
    {
        QuickSort(v, l, j);
    }
    if (i < r)
    {
        QuickSort(v, i, r);
    }
}

int main()
{
    // int linhas = 128975;
    // struct Data *Datas = datasetReduzido(linhas);
    // for (int i = 0; i < linhas; i++)
    // {
    //     printf("linha: %d, amount: %.2f\n", Datas[i].index, Datas[i].amount);
    // }

    FILE *file;
    file = fopen("./dataset_formatado.csv", "r");
    fseek(file, 0, SEEK_END);
    int n = ftell(file) / 41;
    printf("%d", n);
    struct Data *items = malloc(sizeof(struct Data) * n);
    items = datasetReduzido();
    QuickSort(items, 0, n - 1);
    int i;
    for (i = 0; i < n; i++)
    {
        printf("linha: %d, %.2f\n", items[i].index, items[i].amount);
    }
    // de Datas gerar saida

    return 0;
}