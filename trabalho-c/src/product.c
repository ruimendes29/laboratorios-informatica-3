#include "product.h"

struct produto {
    char* codigo;
    Bool usado[NUM_FILIAIS];
};

void freeProduto(void* p) {
    Produto a = (Produto)p;
    free(a->codigo);
    free(a);
}

char* getCodigoProduto(Produto p) { return (p->codigo); }

Produto setCodigoProduto(Produto p, char* codigo) {
    p->codigo = strdup(codigo);
    return p;
}

Produto setUsadoProduto(Produto p, int f, Bool b) {
    p->usado[f] = b;
    return p;
}

Bool jaUsadoProduto(Produto p) {
    Bool ret = false;
    for (int i = 0; i < NUM_FILIAIS && !ret; i++) {
        if (getUsadoProduto(p, i) == true) ret = true;
    }
    return ret;
}

Produto criaProduto(char* codigo) {
    Produto ret = malloc(sizeof(struct produto));
    ret = setCodigoProduto(ret, codigo);
    for (int i = 0; i < NUM_FILIAIS; i++) ret = setUsadoProduto(ret, i, false);
    return ret;
}

Bool getUsadoProduto(Produto p, int f) { return p->usado[f]; }

int isProductCodeValid(char* c) {
    int r;

    if ((!isupper(c[0])) || (!isupper(c[1]))) return 0;

    r = atoi(c + 2);

    return (r >= 1000) && (r <= 9999);
}

int comparaProdutos(const void* x, const void* y) {
    Produto a = (Produto)x;
    Produto b = (Produto)y;
    if (a == NULL || b == NULL) return 1;
    return (strcmp(getCodigoProduto((Produto)a), getCodigoProduto((Produto)b)));
}