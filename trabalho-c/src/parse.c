#include "parse.h"

#define STRLEN_CLIENTS 6
#define PATH_DATA "data/"

CatProdutos readProducts(const char *path, CatProdutos produtos, FacTotal ft) {
    char buf[STRLEN_PRODUCT];
    char *tmp = NULL;
    FILE *fp = fopen(path, "r");

    while (fgets(buf, STRLEN_PRODUCT, fp)) {
        tmp = strtok(buf, "\n\r");

        if (isProductCodeValid(tmp)) {
            Produto c = criaProduto(tmp);
            produtos = insereProduto(produtos, c);
            ft = insereFacProd(ft, c);
        }
    }

    fclose(fp);

    return produtos;
}

CatProdutos processProducts(CatProdutos produtos, FacTotal ft,
                            const char *input) {
    produtos = readProducts(input, produtos, ft);
    return produtos;
}

CatClientes readClients(const char *path, CatClientes clientes,
                        Filial filiais[NUM_FILIAIS]) {
    char buf[STRLEN_CLIENT];
    char *tmp;
    FILE *fp = fopen(path, "r");

    while (fgets(buf, STRLEN_CLIENT, fp)) {
        tmp = strtok(buf, "\n\r");

        if (isClientCodeValid(tmp)) {
            Cliente c = criaCliente(tmp);
            clientes = insereCliente(clientes, c);
            for (int i = 0; i < NUM_FILIAIS; i++)
                filiais[i] = insereClienteProds(filiais[i], c);
        }
    }

    fclose(fp);

    return clientes;
}

CatClientes processClients(CatClientes clientes, Filial filiais[NUM_FILIAIS],
                           const char *input) {
    clientes = readClients(input, clientes, filiais);
    return clientes;
}
