#include "sgv.h"

struct sgv {
    CatClientes clientes;
    CatProdutos produtos;
    FacTotal faturacao;
    Filial* filiais;
    int vendasValidas;
};

SGV initSGV() {
    SGV ret = malloc(sizeof(struct sgv));
    ret->clientes = NULL;
    ret->produtos = NULL;
    ret->faturacao = NULL;
    ret->filiais = malloc(getSizeStructFilial() * NUM_FILIAIS);
    ret->vendasValidas = 0;
    return ret;
}

void freeSGV(SGV sgv) {
    int i;
    freeCatClientes(sgv->clientes);
    freeCatProds(sgv->produtos);
    freeFacturacao(sgv->faturacao);
    for (i = 0; i < NUM_FILIAIS; i++) freeFilial(sgv->filiais[i]);
    free(sgv->filiais);
    free(sgv);
}

SGV setClientes(SGV sgv, CatClientes cp) {
    sgv->clientes = cp;
    return sgv;
}

CatClientes getClientes(SGV sgv) { return sgv->clientes; }

SGV setProdutos(SGV sgv, CatProdutos cp) {
    sgv->produtos = cp;
    return sgv;
}

CatProdutos getProdutos(SGV sgv) { return sgv->produtos; }

SGV setFaturacao(SGV sgv, FacTotal ft) {
    sgv->faturacao = ft;
    return sgv;
}

FacTotal getFaturacao(SGV sgv) { return sgv->faturacao; }

SGV setSingleFilial(SGV sgv, int filial, Filial f) {
    sgv->filiais[filial] = f;
    return sgv;
}

Filial* getFiliais(SGV sgv) { return sgv->filiais; }

SGV setVendasValidas(SGV sgv, int v) {
    sgv->vendasValidas = v;
    return sgv;
}

int getVendasValidas(SGV sgv) { return sgv->vendasValidas; }