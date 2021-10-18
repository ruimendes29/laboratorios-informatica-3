#include "sale.h"

struct sale {
    Produto produto;
    double preco;
    int unidades;
    char modalidade;
    Cliente cliente;
    int mes;
    int filial;
};

int validatePreco(double preco) { return preco >= 0.0 && preco <= 999.99; }

int validateUnidades(int unidades) { return unidades >= 1 && unidades <= 200; }

int validateModalidade(char modalidade) {
    return modalidade == 'P' || modalidade == 'N';
}

int validateMes(int mes) { return mes >= 1 && mes <= 12; }

int validateFilial(int filial) { return filial >= 1 && filial <= NUM_FILIAIS; }

Bool validateSale(CatClientes clients, CatProdutos produtos,
                  FacTotal facturacao, Filial filiais[NUM_FILIAIS], Sale s) {
    if (validatePreco(s->preco) && validateUnidades(s->unidades) &&
        validateModalidade(s->modalidade) && validateMes(s->mes) &&
        validateFilial(s->filial) && existeCliente(clients, s->cliente) &&
        existeProduto(produtos, s->produto)) {
        clients = atualizaCatClientes(clients, s->cliente, s->filial);
        produtos = atualizaCatProdutos(produtos, s->produto, s->filial);
        facturacao = updateFacProd(s->produto, s->mes, s->filial, s->modalidade,
                                   s->preco, s->unidades, facturacao);
        filiais[s->filial - 1] =
            updateFilial(filiais[s->filial - 1], s->mes, s->cliente, s->produto,
                         s->unidades, s->unidades * s->preco, s->modalidade);

        return true;
    }

    return false;
}

Sale setProduto(Sale s, char *token) {
    s->produto = criaProduto(token);
    return s;
}

Sale setPreco(Sale s, char *token) {
    s->preco = atof(token);
    return s;
}

Sale setUnidades(Sale s, char *token) {
    s->unidades = atoi(token);
    return s;
}

Sale setModalidades(Sale s, char *token) {
    s->modalidade = token[0];
    return s;
}

Sale setCliente(Sale s, char *token) {
    s->cliente = criaCliente(token);
    return s;
}

Sale setMes(Sale s, char *token) {
    s->mes = atoi(token);
    return s;
}

Sale setFilial(Sale s, char *token) {
    s->filial = atoi(token);
    return s;
}

Sale setStruct(char *buffer, Sale s) {
    char *token;
    s = malloc(sizeof(struct sale));
    const char space[2] = " ";
    int i = 1;

    token = strtok(buffer, "\n\r");
    token = strtok(token, space);
    s = setProduto(s, token);

    while (token != NULL && i < 7) {
        token = strtok(NULL, space);

        switch (i) {
            case 1:
                s = setPreco(s, token);
                break;

            case 2:
                s = setUnidades(s, token);
                break;

            case 3:
                s = setModalidades(s, token);
                break;

            case 4:
                s = setCliente(s, token);
                break;

            case 5:
                s = setMes(s, token);
                break;

            case 6:
                s = setFilial(s, token);
                break;
        }
        i++;
    }
    return s;
}

void freeSale(Sale s) {
    freeProduto(s->produto);
    freeCliente(s->cliente);
    free(s);
}

int processaVendas(CatClientes clientes, CatProdutos produtos, FacTotal ft,
                   Filial filiais[NUM_FILIAIS], const char *read) {
    char buffer[SALESBUFFER];
    Sale tmp = NULL;
    FILE *r;
    int nv = 0;

    r = fopen(read, "r");

    while (fgets(buffer, SALESBUFFER, r)) {
        tmp = setStruct(buffer, tmp);

        if (validateSale(clientes, produtos, ft, filiais, tmp)) {
            nv++;
        }

        freeSale(tmp);
    }
    fclose(r);

    return nv;
}

Produto getSaleProduto(Sale s) { return s->produto; }

Cliente getSaleCliente(Sale s) { return s->cliente; }

int getSaleFilial(Sale s) { return s->filial; }

double getSalePreco(Sale s) { return s->preco; }

int getSaleUnidades(Sale s) { return s->unidades; }

int getSaleMes(Sale s) { return s->mes; }

char getSaleRegime(Sale s) { return s->modalidade; }

char *getSaleProdutoCodigo(Sale s) { return (getCodigoProduto(s->produto)); }

char *getSaleClienteCodigo(Sale s) { return (getCodigoCliente(s->cliente)); }
