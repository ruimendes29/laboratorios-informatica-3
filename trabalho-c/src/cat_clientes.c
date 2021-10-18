#include "cat_clientes.h"

struct cat_clientes {
    int total;
    /*1º campo : Letra
    2º campo : Milhares
    3º campo : Centenas
    4º campo : Dezenas*/
    Avl lista[26][5][10];
    int usados;
};

struct lista_clientes {
    ArrayList codigos;
};

void freeCatClientes(CatClientes cc) {
    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 5; j++)
            for (int k = 0; k < 10; k++) {
                avltree_delete(cc->lista[i][j][k]);
            }
    free(cc);
}

CatClientes inicializaCatClientes() {
    CatClientes ret = malloc(sizeof(struct cat_clientes));
    ret->total = ret->usados = 0;
    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 5; j++)
            for (int k = 0; k < 10; k++)
                ret->lista[i][j][k] =
                    avltree_create(comparaClientes, freeCliente);
    return ret;
}

static int* getIndexCliente(Cliente c) {
    int* indices = malloc(sizeof(int) * N_PART_CLIENTES);
    char* codigo = getCodigoCliente(c);
    indices[0] = codigo[0] - 'A';
    indices[1] = codigo[1] - '1';
    indices[2] = codigo[2] - '0';
    return indices;
}

CatClientes insereCliente(CatClientes catC, Cliente c) {
    int* i = getIndexCliente(c);
    avltree_add(catC->lista[i[0]][i[1]][i[2]], c);
    catC->total++;
    free(i);
    return catC;
}

Bool existeCliente(CatClientes clientes, Cliente c) {
    Cliente ret;
    int* i = getIndexCliente(c);
    ret = avltree_find(clientes->lista[i[0]][i[1]][i[2]], c);
    free(i);
    if (ret == NULL)
        return false;
    else
        return true;
}

static int getCatClientesUsados(CatClientes cp) { return cp->usados; }

static CatClientes setCatClientesUsados(CatClientes cp, int x) {
    cp->usados = x;
    return cp;
}

CatClientes atualizaCatClientes(CatClientes clients, Cliente c, int f) {
    c = getCliente(clients, c);
    if (getUsadoCliente(c, f - 1) == false) {
        if (jaUsadoCliente(c) == false)
            clients = setCatClientesUsados(clients,
                                           getCatClientesUsados(clients) + 1);
        c = setUsadoCliente(c, f - 1, true);
    }
    return clients;
}

Cliente getCliente(CatClientes clientes, Cliente c) {
    int* i = getIndexCliente(c);
    Cliente ret = avltree_find(clientes->lista[i[0]][i[1]][i[2]], c);
    free(i);
    return ret;
}

Avl getCatClientesListaIndexBy(CatClientes cp, int i, int j, int k) {
    return (cp->lista[i][j][k]);
}

int getCatClientesTotal(CatClientes cp) { return (cp->total); }

int getCatClientesNaoUsados(CatClientes cp) { return cp->total - cp->usados; }

CatClientes setCatClientesTotal(CatClientes cp, int x) {
    cp->total = x;
    return cp;
}

static void addClienteToListIfUsadoTodasFiliais(void* x, void* l) {
    Cliente c = (Cliente)x;
    ArrayList* a = (ArrayList*)l;
    if (usadoTodasFiliaisCliente(c) == true) {
        arraylist_add(*a, getCodigoCliente(c));
    }
}

ArrayList getListClientesUsadosTodasFiliais(CatClientes cc) {
    ArrayList ret = arraylist_create(comparaClientes);

    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 5; j++)
            for (int k = 0; k < 10; k++) {
                avltree_for_each(cc->lista[i][j][k],
                                 addClienteToListIfUsadoTodasFiliais, &ret);
            }

    return ret;
}
