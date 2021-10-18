#include "sort.h"

static void swap(void **a, void **b) {
    void *temp = (*a);
    (*a) = (*b);
    (*b) = temp;
}

static int partition(ArrayList al, int low, int high, arraylist_cmpfn comp) {
    const void *pivot = al->body[high];  // pivot
    int i = (low - 1);                   // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        // If current element is smaller than or
        // equal to pivot
        if (comp(al->body[j], pivot) < 0) {
            i++;  // increment index of smaller element
            swap(&(al->body[i]), &(al->body[j]));
        }
    }
    swap(&(al->body[i + 1]), &(al->body[high]));
    return (i + 1);
}

void quickSort(ArrayList al, int low, int high, arraylist_cmpfn comp) {
    if (low < high) {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(al, low, high, comp);

        // Separately sort elements before
        // partition and after partition
        quickSort(al, low, pi - 1, comp);
        quickSort(al, pi + 1, high, comp);
    }
}

int ordenaPorQuantidade(const void *a, const void *b) {
    InfoProd ip0 = (InfoProd)a;
    InfoProd ip1 = (InfoProd)b;
    int q0 = getQuantidadeNFromInfoProd(ip0) + getQuantidadePFromInfoProd(ip0);
    int q1 = getQuantidadeNFromInfoProd(ip1) + getQuantidadePFromInfoProd(ip1);
    return q1 - q0;
}

int ordenaPorFacturacao(const void *a, const void *b) {
    InfoProd ip0 = (InfoProd)a;
    InfoProd ip1 = (InfoProd)b;
    float f0 = getFacturacaoN(ip0) + getFacturacaoP(ip0);
    float f1 = getFacturacaoN(ip1) + getFacturacaoP(ip1);
    return f1 - f0;
}

int ordenaFacProdsQuantidade(const void *a, const void *b) {
    FacProd fp0 = (FacProd)a;
    FacProd fp1 = (FacProd)b;
    int q0 = getQuantidadeFromFacProd(fp0);
    int q1 = getQuantidadeFromFacProd(fp1);
    return q1 - q0;
}