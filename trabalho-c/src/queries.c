#include "queries.h"

SGV answerQuery1(SGV sgv, const char *path1r, const char *path2r,
                 const char *path3r) {
    int i;
    sgv = setClientes(sgv, inicializaCatClientes());
    sgv = setProdutos(sgv, inicializaCatProdutos());
    sgv = setFaturacao(sgv, inicializaFacTotal());

    for (i = 0; i < NUM_FILIAIS; i++)
        sgv = setSingleFilial(sgv, i, inicializaFilial());

    sgv = setClientes(
        sgv, processClients(getClientes(sgv), getFiliais(sgv), path1r));

    sgv = setProdutos(
        sgv, processProducts(getProdutos(sgv), getFaturacao(sgv), path2r));

    sgv = setVendasValidas(
        sgv, processaVendas(getClientes(sgv), getProdutos(sgv),
                            getFaturacao(sgv), getFiliais(sgv), path3r));

    return sgv;
}

ArrayList answerQuery2(SGV sgv, char c) {
    ArrayList ret;
    ret = getListProdutosByChar(getProdutos(sgv), c);
    return ret;
}

FacProd *answerQuery3(SGV sgv, char *codigo, int mes) {
    Produto p = criaProduto(codigo);
    FacProd *ret = getFacProdsFiliaisProduto(getFaturacao(sgv), p, mes);
    return ret;
}

ArrayList *answerQuery4(SGV sgv) {
    int i;
    ArrayList *ret = malloc(sizeof(ArrayList) * (NUM_FILIAIS + 1));
    for (i = 0; i < NUM_FILIAIS + 1; i++)
        ret[i] = arraylist_create(comparaProdutos);
    ret = totalNonUsedProducts(ret, getProdutos(sgv));
    return ret;
}

ArrayList answerQuery7(Filial *filiais, Cliente c) {
    ArrayList ret = arraylist_create(NULL);
    char string[MAX_BUFFER];
    int qtd_aux[NUM_FILIAIS];
    unsigned int index;
    InfoProd item;
    ArrayList produtos_aux;

    for (int m = 1; m < 13; m++) {
        for (int i = 0; i < NUM_FILIAIS; i++) {
            produtos_aux = getProdutosFromCliente(filiais[i], c, m);
            qtd_aux[i] = 0;
            arraylist_iterate(produtos_aux, index, item) {
                qtd_aux[i] += getQuantidadeNFromInfoProd(item) +
                              getQuantidadePFromInfoProd(item);
            }
        }
        sprintf(string, " %3d | %8d | %8d | %8d ", m, qtd_aux[0], qtd_aux[1],
                qtd_aux[2]);
        arraylist_add(ret, strdup(string));
    }

    return ret;
}

int answerQuery8(SGV sgv, double *totalFac, int inicio, int fim) {
    double facturacao = 0;
    int vendas = 0;
    FacTotal fac = getFaturacao(sgv);
    for (int i = inicio; i <= fim; i++) {
        vendas += getQuantidadeMes(fac, i - 1);
        facturacao += (double)getFacturacaoMes(fac, i - 1);
    }
    (*totalFac) = facturacao;
    return vendas;
}

void quantosClientesCompraram(void *x, void *y, void *z) {
    ClienteProds cp = (ClienteProds)x;
    Produto p = (Produto)y;
    int *r = (int *)z;
    int n = (*r);
    if (arraylist_find_by(getProdutosFromClienteProds(cp), p,
                          compareInfoProdToProduto) != -1)
        n++;
    (*r) = n;
}

void codigoClientesCompraram(void *x, void *y, void *z) {
    ClienteProds cp = (ClienteProds)x;
    Produto p = (Produto)y;
    ArrayList *r = (ArrayList *)z;
    ArrayList pClientes = getProdutosFromClienteProds(cp);
    int index = arraylist_find_by(pClientes, p, compareInfoProdToProduto);
    if (index != -1) {
        if (getQuantidadeNFromInfoProd(pClientes->body[index]) > 0) {
            arraylist_add(r[0],
                          getCodigoCliente(getClienteFromClienteProds(cp)));
        }
        if (getQuantidadePFromInfoProd(pClientes->body[index]) > 0) {
            arraylist_add(r[1],
                          getCodigoCliente(getClienteFromClienteProds(cp)));
        }
    }
}

/* responde a querie 9 e deixa no ret[0] os clientes que compraram em regime N
e em ret[1] os clientes que compraram em P*/

ArrayList *answerQuery9(Produto p, Filial filial) {
    ArrayList *ret = malloc(sizeof(struct arraylist) * 2);
    ret[0] = arraylist_create(NULL);
    ret[1] = arraylist_create(NULL);
    for (int l1 = 0; l1 < 26; l1++)
        for (int n1 = 0; n1 < 5; n1++)
            for (int n2 = 0; n2 < 10; n2++)
                avltree_for_each2(getFilialAnualAvlCliente(filial, l1, n1, n2),
                                  codigoClientesCompraram, p, ret);
    return ret;
}

ArrayList answerQuery10(SGV sgv, Cliente c, int mes) {
    ArrayList ret = arraylist_create(NULL);
    ArrayList aux = arraylist_create(NULL);
    Filial *filiais = getFiliais(sgv);
    int indp;
    ArrayList infoprods = arraylist_create(comparaInfoProd);
    InfoProd teste;
    InfoProd retor;
    char string[MAX_BUFFER];
    for (int f = 0; f < NUM_FILIAIS; f++) {
        aux = getProdutosFromCliente(filiais[f], c, mes);
        for (unsigned int i = 0; i < aux->size; i++) {
            teste = aux->body[i];
            indp = arraylist_find_by(infoprods, teste, comparaInfoProd);
            if (indp == -1)
                infoprods = arraylist_insertLast(
                    infoprods, cloneInfoProd(teste), comparaInfoProd);
            else {
                retor = infoprods->body[indp];
                retor = setQuantidadeNInfoProd(
                    retor, getQuantidadeNFromInfoProd(retor) +
                               getQuantidadeNFromInfoProd(teste));
                retor = setQuantidadePInfoProd(
                    retor, getQuantidadePFromInfoProd(retor) +
                               getQuantidadePFromInfoProd(teste));
            }
        }
    }
    quickSort(infoprods, 0, infoprods->size - 1, ordenaPorQuantidade);
    InfoProd ip;
    for (unsigned int i = 0; i < infoprods->size; i++) {
        ip = infoprods->body[i];
        sprintf(
            string, "%s  %9d ", getCodigoProduto(getProdutoFromInfoProd(ip)),
            getQuantidadeNFromInfoProd(ip) + getQuantidadePFromInfoProd(ip));
        arraylist_add(ret, strdup(string));
    }
    for (unsigned int i = 0; i < infoprods->size; i++) {
        freeInfoProd(infoprods->body[i]);
    }
    free(infoprods);
    return ret;
}

ArrayList *answerQuery11(SGV sgv, int N) {
    ArrayList *ret = malloc(sizeof(struct arraylist) * NUM_FILIAIS);
    Filial *filiais = getFiliais(sgv);
    FacTotal ft = getFaturacao(sgv);
    ArrayList facprods;
    FacProd teste;
    char string[MAX_BUFFER];
    for (int i = 0; i < NUM_FILIAIS; i++) {
        facprods = getNProdutosMaisVendidos(N, ft, i);
        quickSort(facprods, 0, facprods->size - 1, ordenaFacProdsQuantidade);
        ret[i] = arraylist_create(NULL);
        for (unsigned int a = 0; a < facprods->size; a++) {
            teste = facprods->body[a];
            sprintf(string, "%7s     %16d      %16d",
                    getCodigoProduto(getProdutoFromFacProd(teste)),
                    getQuantidadeFromFacProd(teste),
                    getNumeroClientesDoProduto(getProdutoFromFacProd(teste),
                                               filiais[i]));
            arraylist_add(ret[i], strdup(string));
        }
        arraylist_destroy(facprods);
    }
    return ret;
}

ArrayList answerQuery12(SGV sgv, Cliente c) {
    ArrayList ret = arraylist_create(NULL);
    ArrayList aux = NULL;
    Filial *filiais;
    filiais = getFiliais(sgv);
    int indp;
    ArrayList infoprods = arraylist_create(comparaInfoProd);
    InfoProd teste;
    InfoProd retor;
    char string[MAX_BUFFER];
    for (int f = 0; f < NUM_FILIAIS; f++) {
        aux = getAllProdutosFromCliente(filiais[f], c);
        for (unsigned int i = 0; i < aux->size; i++) {
            teste = aux->body[i];
            indp = arraylist_find_by(infoprods, teste, comparaInfoProd);
            if (indp == -1)
                infoprods = arraylist_insertLast(
                    infoprods, cloneInfoProd(teste), comparaInfoProd);
            else {
                retor = infoprods->body[indp];
                retor = setFacturacaoN(
                    retor, getFacturacaoN(retor) + getFacturacaoN(teste));
                retor = setFacturacaoP(
                    retor, getFacturacaoP(retor) + getFacturacaoP(teste));
            }
        }
    }
    quickSort(infoprods, 0, infoprods->size - 1, ordenaPorFacturacao);
    InfoProd ip;
    for (unsigned int i = 0; i < infoprods->size && i < 3; i++) {
        ip = infoprods->body[i];
        sprintf(string, "%6s    %10.2f",
                getCodigoProduto(getProdutoFromInfoProd(ip)),
                getFacturacaoN(ip) + getFacturacaoP(ip));
        arraylist_add(ret, strdup(string));
    }
    printf("%d\n", ret->size);
    for (unsigned int i = 0; i < infoprods->size; i++) {
        freeInfoProd(infoprods->body[i]);
    }
    arraylist_destroy(infoprods);
    return ret;
}
