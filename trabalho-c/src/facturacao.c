#include "facturacao.h"

struct facprod {
    Produto produto;
    double totalFacturadoN;
    double totalFacturadoP;
    int unidadesN;
    int unidadesP;
    int registosVendaN;
    int registosVendaP;
};

struct facanual {
    Avl produtos[26][26][9][10];
};

struct facmensal {
    double totalFacturado;
    int totalVendas;  // numero de linhas de venda
    Avl produtos[26][26][9][10];
};

struct factotal {
    FacMensal factFilialMensal[NUM_FILIAIS][12];
    FacAnual factFilialAnual[NUM_FILIAIS];
};

void freeFacProd(void* x) { free(x); }

static FacAnual getFacAnual(FacTotal ft, int filial) {
    return ft->factFilialAnual[filial];
}

static Avl getFacAnualAvlProduto(FacAnual fa, int i, int j, int k, int h) {
    return fa->produtos[i][j][k][h];
}

void dropFacProdtoAL(void* x, void* y) {
    FacProd fp = (FacProd)x;
    ArrayList list = (ArrayList)y;
    arraylist_add(list, fp);
}

static ArrayList getFacProdsFromAvl(Avl a) {
    ArrayList ret = arraylist_create(NULL);
    avltree_for_each(a, dropFacProdtoAL, ret);
    return ret;
}

Produto getProdutoFromFacProd(FacProd fp) { return fp->produto; }

int getQuantidadeFromFacProd(FacProd fp) {
    return (fp->unidadesN + fp->unidadesP);
}

int getRegistosVendaN(FacProd fp) { return fp->registosVendaN; }

int getRegistosVendaP(FacProd fp) { return fp->registosVendaP; }

static void freeFacturacaoMensal(FacMensal fm) {
    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 26; j++)
            for (int k = 0; k < 9; k++)
                for (int h = 0; h < 10; h++) {
                    avltree_delete(fm->produtos[i][j][k][h]);
                }
    free(fm);
}

static void freeFacturacaoAnual(FacAnual fa) {
    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 26; j++)
            for (int k = 0; k < 9; k++)
                for (int h = 0; h < 10; h++) {
                    avltree_delete(fa->produtos[i][j][k][h]);
                }
    free(fa);
}

void freeFacturacao(FacTotal f) {
    for (int i = 0; i < 12; i++)
        for (int j = 0; j < NUM_FILIAIS; j++) {
            freeFacturacaoMensal(f->factFilialMensal[j][i]);
        }
    for (int j = 0; j < NUM_FILIAIS; j++)
        freeFacturacaoAnual(f->factFilialAnual[j]);
    free(f);
}

static int* getIndexFacProd(Produto p, int filial, int mes) {
    int* indices = malloc(sizeof(int) * 6);
    char* codigo = getCodigoProduto(p);
    indices[0] = filial - 1;
    indices[1] = mes - 1;
    indices[2] = codigo[0] - 'A';
    indices[3] = codigo[1] - 'A';
    indices[4] = codigo[2] - '1';
    indices[5] = codigo[3] - '0';
    return indices;
}

static int* getIndexFacAnual(Produto p, int filial) {
    int* indices = malloc(sizeof(int) * 5);
    char* codigo = getCodigoProduto(p);
    indices[0] = filial - 1;
    indices[1] = codigo[0] - 'A';
    indices[2] = codigo[1] - 'A';
    indices[3] = codigo[2] - '1';
    indices[4] = codigo[3] - '0';
    return indices;
}

static FacProd criaFacProd(Produto p) {
    FacProd ret = malloc(sizeof(struct facprod));
    ret->produto = p;
    ret->totalFacturadoN = ret->totalFacturadoP = 0.L;
    ret->unidadesN = ret->unidadesP = 0;
    ret->registosVendaN = ret->registosVendaP = 0;
    return ret;
}

extern FacTotal insereFacProd(FacTotal ft, Produto p) {
    int* i;
    int* a;
    for (int f = 1; f <= NUM_FILIAIS; f++)
        for (int m = 1; m <= 12; m++) {
            i = getIndexFacProd(p, f, m);
            avltree_add(ft->factFilialMensal[i[0]][i[1]]
                            ->produtos[i[2]][i[3]][i[4]][i[5]],
                        criaFacProd(p));
            free(i);
        }
    for (int f = 1; f <= NUM_FILIAIS; f++) {
        a = getIndexFacAnual(p, f);
        avltree_add(ft->factFilialAnual[a[0]]->produtos[a[1]][a[2]][a[3]][a[4]],
                    criaFacProd(p));
        free(a);
    }
    return ft;
}

static int comparaFacProdtoProd(const void* a, const void* b) {
    FacProd fp = (FacProd)a;
    Produto p = (Produto)b;
    return comparaProdutos(fp->produto, p);
}

extern FacTotal updateFacProd(Produto p, int mes, int filial, char regime,
                              double preco, int unidades, FacTotal ft) {
    int* i = getIndexFacProd(p, filial, mes);
    int* a = getIndexFacAnual(p, filial);
    FacMensal fm = ft->factFilialMensal[i[0]][i[1]];
    Avl avlProduto = fm->produtos[i[2]][i[3]][i[4]][i[5]];
    Avl anual = ft->factFilialAnual[a[0]]->produtos[a[1]][a[2]][a[3]][a[4]];
    FacProd needle = avltree_find_by(avlProduto, p, comparaFacProdtoProd);
    FacProd prodAnual = avltree_find_by(anual, p, comparaFacProdtoProd);
    double total = preco * unidades;
    if (regime == 'N') {
        needle->totalFacturadoN += total;
        needle->unidadesN += unidades;
        needle->registosVendaN += 1;
        prodAnual->totalFacturadoN += total;
        prodAnual->unidadesN += unidades;
        prodAnual->registosVendaN += 1;
    } else {
        needle->totalFacturadoP += total;
        needle->unidadesP += unidades;
        needle->registosVendaP += 1;
        prodAnual->totalFacturadoP += total;
        prodAnual->unidadesP += unidades;
        prodAnual->registosVendaP += 1;
    }
    fm->totalFacturado += total;
    fm->totalVendas++;
    free(i);
    free(a);
    return ft;
}

static int comparaFacProds(const void* a, const void* b) {
    FacProd x = (FacProd)a;
    FacProd y = (FacProd)b;
    int r = strcmp(getCodigoProduto(x->produto), getCodigoProduto(y->produto));
    return (r);
}

static FacMensal inicializaFacMensal() {
    FacMensal ret = malloc(sizeof(struct facmensal));
    ret->totalFacturado = 0;
    ret->totalVendas = 0;
    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 26; j++)
            for (int k = 0; k < 9; k++)
                for (int h = 0; h < 10; h++)
                    ret->produtos[i][j][k][h] =
                        avltree_create(comparaFacProds, freeFacProd);

    return ret;
}

static FacAnual inicializaFacAnual() {
    FacAnual ret = malloc(sizeof(struct facanual));
    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 26; j++)
            for (int k = 0; k < 9; k++)
                for (int h = 0; h < 10; h++)
                    ret->produtos[i][j][k][h] =
                        avltree_create(comparaFacProds, freeFacProd);

    return ret;
}

extern FacTotal inicializaFacTotal() {
    FacTotal ret = malloc(sizeof(struct factotal));
    for (int f = 0; f < NUM_FILIAIS; f++)
        for (int i = 0; i < 12; i++) {
            ret->factFilialMensal[f][i] = inicializaFacMensal();
        }
    for (int f = 0; f < NUM_FILIAIS; f++)
        ret->factFilialAnual[f] = inicializaFacAnual();
    return ret;
}

double getFacturacaoMes(FacTotal ft, int mes) {
    double ret = 0.L;
    for (int f = 0; f < NUM_FILIAIS; f++)
        ret += ft->factFilialMensal[f][mes]->totalFacturado;
    return ret;
}

double getFacturacaoTotalFromProd(FacProd fp) {
    return (fp->totalFacturadoN + fp->totalFacturadoP);
}

double getFacturacaoNFromProd(FacProd fp) { return fp->totalFacturadoN; }

double getFacturacaoPFromProd(FacProd fp) { return fp->totalFacturadoP; }

int getQuantidadeMes(FacTotal ft, int mes) {
    int q = 0;
    for (int f = 0; f < NUM_FILIAIS; f++)
        q += ft->factFilialMensal[f][mes]->totalVendas;
    return q;
}

static FacProd getFacProdFromProduto(FacTotal ft, Produto p, int mes,
                                     int filial) {
    int* i = getIndexFacProd(p, filial, mes);
    FacMensal fm = ft->factFilialMensal[i[0]][i[1]];
    Avl avlProduto = fm->produtos[i[2]][i[3]][i[4]][i[5]];
    FacProd needle = avltree_find_by(avlProduto, p, comparaFacProdtoProd);
    free(i);
    return needle;
}

FacProd* getFacProdsFiliaisProduto(FacTotal ft, Produto p, int mes) {
    int i;
    FacProd* ret = malloc(sizeof(FacProd) * NUM_FILIAIS);
    for (i = 0; i < NUM_FILIAIS; i++)
        ret[i] = getFacProdFromProduto(ft, p, mes, i + 1);
    return ret;
}

unsigned int minIndProd(ArrayList l) {
    unsigned int r = 0;
    int min = getQuantidadeFromFacProd((FacProd)l->body[0]);
    for (unsigned int i = 1; i < l->size; i++) {
        int comp = getQuantidadeFromFacProd((FacProd)l->body[i]);
        if (comp < min) {
            r = i;
            min = comp;
        }
    }
    return r;
}

ArrayList getNProdutosMaisVendidos(int N, FacTotal ft, int f) {
    ArrayList ret = arraylist_create(NULL);
    ArrayList produtos;
    int espaco = 0;
    Avl tree;
    FacAnual fa = getFacAnual(ft, f);
    for (int l1 = 0; l1 < 26; l1++)
        for (int l2 = 0; l2 < 26; l2++)
            for (int n1 = 0; n1 < 9; n1++)
                for (int n2 = 0; n2 < 10; n2++) {
                    tree = getFacAnualAvlProduto(fa, l1, l2, n1, n2);
                    produtos = getFacProdsFromAvl(tree);
                    for (int ap = 0; ap < (int)produtos->size; ap++) {
                        if (espaco < N) {
                            arraylist_add(ret, produtos->body[ap]);
                            espaco++;
                        } else if (getQuantidadeFromFacProd(
                                       produtos->body[ap]) >
                                   getQuantidadeFromFacProd(
                                       arraylist_get(ret, minIndProd(ret))))
                            arraylist_set(ret, minIndProd(ret),
                                          produtos->body[ap]);
                    }
                }
    return ret;
}