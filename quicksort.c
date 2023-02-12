
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// struct
struct Item {
    int valor;
    char categoria[100];
};

// Funcao para comparar duas structs
int compare(const void *a, const void *b) {
    struct Item *ia = (struct Item *)a;
    struct Item *ib = (struct Item *)b;
    return (ib->valor - ia->valor);
}

// QuickSort
void QuickSort(struct Item *v, int l, int r) {
    int i, j;
    struct Item x, w;
    i = l;
    j = r;
    x = v[(l + r) / 2];
    do {
        while (v[i].valor > x.valor && i < r) {
            i++;
        }
        while (v[j].valor < x.valor && j > l) {
            j--;
        }
        if (i <= j) {
            w = v[i];
            v[i] = v[j];
            v[j] = w;
            i++;
            j--;
        }
    } while (i <= j);
    if (l < j) {
        QuickSort(v, l, j);
    }
    if (i < r) {
        QuickSort(v, i, r);
    }
}

int main() {
    int n = 5;
    struct Item v[5] = {{1645, "brasil"}, {251566, "alemanha"}, {151616, "japao"}, {26514564, "canada"}, {1561465, "franca"}};
    QuickSort(v, 0, n - 1);
    for (int i = 0; i < n; i++) {
        printf("%s,%d\n", v[i].categoria, v[i].valor);
    }
    return 0;
}