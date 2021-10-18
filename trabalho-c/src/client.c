#include "client.h"

struct cliente {
    char* codigo;
    Bool usado[NUM_FILIAIS];
};

void freeCliente(void* c) {
    Cliente a = (Cliente)c;
    free(a->codigo);
    free(a);
}

char* getCodigoCliente(Cliente c) { return (c->codigo); }

Cliente setCodigoCliente(Cliente c, char* codigo) {
    c->codigo = strdup(codigo);
    return c;
}

Bool getUsadoCliente(Cliente c, int f) { return c->usado[f]; }

Cliente setUsadoCliente(Cliente c, int f, Bool b) {
    c->usado[f] = b;
    return c;
}

Cliente criaCliente(char* codigo) {
    Cliente ret = malloc(sizeof(struct cliente));
    ret = setCodigoCliente(ret, codigo);
    for (int i = 0; i < NUM_FILIAIS; i++) ret = setUsadoCliente(ret, i, false);
    return ret;
}

int isClientCodeValid(char* c) {
    int r;
    if (!isupper(c[0])) return 0;

    r = atoi(c + 1);

    return (r >= 1000) && (r <= 5000);
}

int comparaClientes(const void* x, const void* y) {
    Cliente a = (Cliente)x;
    Cliente b = (Cliente)y;
    if (a == NULL || b == NULL) return 1;
    return (strcmp(getCodigoCliente((Cliente)a), getCodigoCliente((Cliente)b)));
}

Bool jaUsadoCliente(Cliente c) {
    Bool ret = false;

    for (int i = 0; i < NUM_FILIAIS; i++)
        if (getUsadoCliente(c, i) == true) ret = true;

    return ret;
}

Bool usadoTodasFiliaisCliente(Cliente c) {
    Bool ret = true;

    for (int i = 0; i < NUM_FILIAIS; i++)
        if (getUsadoCliente(c, i) == false) ret = false;

    return ret;
}