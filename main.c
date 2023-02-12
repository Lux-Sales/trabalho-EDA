#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct Data
{
    int index;
    float amount;
};

int lerDataSet(struct Data *items)
{
    FILE *file;
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
        if (ch == '\377')
        {
            break;
        }
        if (contador > 19)
        {
            if (ch != ',' && ch != '*')
            {
                strncat(amountStr, &ch, 1);
                amount = atof(amountStr);
            }
        }
        if (ch == '\n')
        {
            struct Data lineData;
            lineData.amount = amount;
            lineData.index = linha;
            items[adicionarEm] = lineData;
            adicionarEm++;
            linha++;
            int i = 0;
            for (i = 0; i < 10; i++)
            {
                amountStr[i] = '\000';
            }
            contador = -1;
        }
        contador++;
    } while (ch != EOF);
    fclose(file);
    return 0;
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

int escreveResultado(struct Data *items, int length, FILE *file, FILE *saida)
{
    int i;
    int j;
    for (i = 0; i < length; i++)
    {
        fseek(file, (items[i].index * 41), SEEK_SET);
        char ch;
        char categoria[20] = "";
        do
        {
            ch = fgetc(file);
            if (ch != '*')
                strncat(categoria, &ch, 1);

        } while (ch != '*' && ch != EOF);
        fprintf(saida, "linha: %d, categoria: %s, valor: %.2f\n", items[i].index, categoria, items[i].amount);
        for (j = 0; j < 20; j++)
        {
            categoria[j] = '\000';
        }
    }
}

int main()
{
    FILE *file, *saida;
    file = fopen("./dataset_formatado.csv", "r");
    saida = fopen("./dataset_saida.txt", "w");

    if (file == NULL || saida == NULL)
    {
        printf("Error opening files");
        exit(1);
    }

    // int linhas = 128975;
    // struct Data *Datas = datasetReduzido(linhas);
    // for (int i = 0; i < linhas; i++)
    // {
    //     printf("linha: %d, amount: %.2f\n", Datas[i].index, Datas[i].amount);
    // }
    clock_t start, end, open_time, alloc_time, quicksort_time;

    start = clock();
    open_time = clock();
    file = fopen("./dataset_formatado.csv", "r");
    open_time = clock() - open_time;
    double time_to_open = ((double)open_time) / CLOCKS_PER_SEC;

    alloc_time = clock();

    fseek(file, 0, SEEK_END);
    int n = ftell(file) / 41;
    struct Data *items = malloc(sizeof(struct Data) * n);
    lerDataSet(items);

    alloc_time = clock() - alloc_time;
    double time_to_alloc = ((double)alloc_time) / CLOCKS_PER_SEC;

    quicksort_time = clock();
    QuickSort(items, 0, n - 1);
    quicksort_time = clock() - quicksort_time;
    double time_to_sort = ((double)quicksort_time) / CLOCKS_PER_SEC;
    escreveResultado(items, n, file, saida);

    end = clock();
    fclose(file);
    fclose(saida);
    free(items);
    double duration = ((double)end - start) / CLOCKS_PER_SEC;
    printf("\nTempo de carregamento do arquivo: %f", time_to_open);
    printf("\nTempo de alocação: %f", time_to_alloc);
    printf("\nTempo de ordenação: %f", time_to_sort);
    printf("\nTempo de execução do programa em segundos : %f", duration);
    // de Datas gerar saida

    return 0;
}