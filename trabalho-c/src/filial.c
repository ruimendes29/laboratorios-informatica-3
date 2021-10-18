#include "filial.h"

struct infoprod {
    Produto p;
    int quantidadeN;
    int quantidadeP;
    float facturacaoN;
    float facturacaoP;
};

struct filialanual {
    Avl clientes[26][5][10];
};

struct clienteprods {
    Cliente c;
    ArrayList produtos;
};

struct filialmensal {
    Avl clientes[26][5][10];
};

struct filial {
    FilialMensal meses[12];
    FilialAnual anual;
};

void freeClienteProds(void* a) {
    ClienteProds cp = (ClienteProds)a;
    for (unsigned int i = 0; i < cp->produtos->size; i++)
        freeInfoProd(cp->produtos->body[i]);
    arraylist_destroy(cp->produtos);
    free(cp);
}

int getQuantidade(InfoProd ip) { return (ip->quantidadeN + ip->quantidadeP); }

size_t getSizeStructFilial() { return sizeof(struct filial); }

InfoProd setQuantidade(InfoProd ip, char regime, int x) {
    if (regime == 'N')
        ip->quantidadeN = x;
    else
        ip->quantidadeP = x;
    return ip;
}

InfoProd setFacturacao(InfoProd ip, char regime, int x) {
    if (regime == 'N')
        ip->facturacaoN = x;
    else
        ip->facturacaoP = x;
    return ip;
}

float getFacturacaoN(InfoProd ip) { return ip->facturacaoN; }

float getFacturacaoP(InfoProd ip) { return ip->facturacaoP; }

extern int comparaInfoProd(const void* a, const void* b) {
    InfoProd x = (InfoProd)a;
    InfoProd y = (InfoProd)b;
    return comparaProdutos(x->p, y->p);
}

extern InfoProd setQuantidadeNInfoProd(InfoProd ip, int x) {
    ip->quantidadeN = x;
    return ip;
}

extern InfoProd setQuantidadePInfoProd(InfoProd ip, int x) {
    ip->quantidadeP = x;
    return ip;
}

extern Produto getProdutoFromInfoProd(InfoProd ip) { return ip->p; }

extern InfoProd setFacturacaoN(InfoProd ip, float x) {
    ip->facturacaoN = x;
    return ip;
}

extern InfoProd setFacturacaoP(InfoProd ip, float x) {
    ip->facturacaoP = x;
    return ip;
}

static char* getCodigoFromInfoProd(InfoProd ip) {
    return getCodigoProduto(ip->p);
}

extern InfoProd cloneInfoProd(InfoProd ip) {
    InfoProd ret = malloc(sizeof(struct infoprod));
    ret->facturacaoN = ip->facturacaoN;
    ret->facturacaoP = ip->facturacaoP;
    ret->p = criaProduto(getCodigoFromInfoProd(ip));
    ret->quantidadeN = ip->quantidadeN;
    ret->quantidadeP = ip->quantidadeP;
    return ret;
}

static InfoProd criaInfoProd(Produto p, int q, char regime, float fac) {
    InfoProd ret = malloc(sizeof(struct infoprod));
    ret->p = criaProduto(getCodigoProduto(p));
    if (regime == 'N') {
        ret->quantidadeN = q;
        ret->facturacaoN = fac;
        ret->quantidadeP = 0;
        ret->facturacaoP = 0;
    } else {
        ret->quantidadeP = q;
        ret->facturacaoP = fac;
        ret->quantidadeN = 0;
        ret->facturacaoN = 0;
    }

    return ret;
}

void freeInfoProd(void* x) {
    InfoProd ip = (InfoProd)x;
    freeProduto(ip->p);
    free(ip);
}

ClienteProds inicializaClienteProds(Cliente c) {
    ClienteProds ret = malloc(sizeof(struct clienteprods));
    ret->c = c;
    ret->produtos = arraylist_create(comparaInfoProd);
    return ret;
}

static int comparaClientesProds(const void* a, const void* b) {
    ClienteProds x = (ClienteProds)a;
    ClienteProds y = (ClienteProds)b;

    return (comparaClientes(x->c, y->c));
}

FilialMensal inicializaFilialMensal() {
    FilialMensal ret = malloc(sizeof(struct filialmensal));
    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 5; j++)
            for (int k = 0; k < 10; k++)
                ret->clientes[i][j][k] =
                    avltree_create(comparaClientesProds, freeClienteProds);
    return ret;
}

FilialAnual inicializaFilialAnual() {
    FilialAnual ret = malloc(sizeof(struct filialanual));
    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 5; j++)
            for (int k = 0; k < 10; k++)
                ret->clientes[i][j][k] =
                    avltree_create(comparaClientesProds, freeClienteProds);
    return ret;
}

Filial inicializaFilial() {
    Filial ret = malloc(sizeof(struct filial));
    for (int i = 0; i < 12; i++) ret->meses[i] = inicializaFilialMensal();
    ret->anual = inicializaFilialAnual();
    return ret;
}

static int* getIndicesFilial(int mes, Cliente c) {
    int* ret = malloc(sizeof(int) * 4);
    char* codigo = getCodigoCliente(c);
    ret[0] = mes - 1;
    ret[1] = codigo[0] - 'A';
    ret[2] = codigo[1] - '1';
    ret[3] = codigo[2] - '0';
    return ret;
}

static int* getIndicesFilialAnual(Cliente c) {
    int* ret = malloc(sizeof(int) * 3);
    char* codigo = getCodigoCliente(c);
    ret[0] = codigo[0] - 'A';
    ret[1] = codigo[1] - '1';
    ret[2] = codigo[2] - '0';
    return ret;
}

static int compareClienteProdsToCliente(const void* x, const void* y) {
    ClienteProds cp = (ClienteProds)x;
    Cliente c = (Cliente)y;
    return (comparaClientes(cp->c, c));
}

extern Filial insereClienteProds(Filial filial, Cliente c) {
    int* i;
    int* a;
    Avl tree;
    Avl anual;
    for (int m = 1; m <= 12; m++) {
        i = getIndicesFilial(m, c);
        tree = filial->meses[i[0]]->clientes[i[1]][i[2]][i[3]];

        avltree_add(tree, inicializaClienteProds(c));
        free(i);
    }
    a = getIndicesFilialAnual(c);
    anual = filial->anual->clientes[a[0]][a[1]][a[2]];
    avltree_add(anual, inicializaClienteProds(c));
    free(a);
    return filial;
}

extern int compareInfoProdToProduto(const void* x, const void* y) {
    InfoProd ip = (InfoProd)x;
    Produto p = (Produto)y;
    return (comparaProdutos(ip->p, p));
}

Avl getFilialAnualAvlCliente(Filial f, int i, int j, int k) {
    return f->anual->clientes[i][j][k];
}

extern ArrayList getProdutosFromClienteProds(ClienteProds cp) {
    return cp->produtos;
}

extern ArrayList getProdutosFromCliente(Filial f, Cliente c, int mes) {
    int* i = getIndicesFilial(mes, c);
    Avl avlCliente = f->meses[i[0]]->clientes[i[1]][i[2]][i[3]];
    ClienteProds tree =
        avltree_find_by(avlCliente, c, compareClienteProdsToCliente);
    ArrayList al = tree->produtos;
    free(i);
    return al;
}

extern ArrayList getAllProdutosFromCliente(Filial f, Cliente c) {
    int* i = getIndicesFilialAnual(c);
    Avl tree = f->anual->clientes[i[0]][i[1]][i[2]];
    ClienteProds cp = avltree_find_by(tree, c, compareClienteProdsToCliente);
    ArrayList al = cp->produtos;
    free(i);
    return al;
}

static InfoProd updateInfoProd(InfoProd ip, char regime, int q, float fac) {
    if (regime == 'N') {
        ip->quantidadeN += q;
        ip->facturacaoN += fac;
    } else {
        ip->quantidadeP += q;
        ip->facturacaoP += fac;
    }
    return ip;
}

Filial updateFilial(Filial f, int mes, Cliente c, Produto p, int q, float fac,
                    char regime) {
    ArrayList al = getProdutosFromCliente(f, c, mes);
    ArrayList anual = getAllProdutosFromCliente(f, c);
    int indexMes = arraylist_find_by(al, p, compareInfoProdToProduto);
    int indexAnual = arraylist_find_by(anual, p, compareInfoProdToProduto);
    InfoProd an = NULL;
    InfoProd ip = NULL;
    if (indexAnual != -1) {
        an = anual->body[indexAnual];
        an = updateInfoProd(an, regime, q, fac);
    } else
        anual = arraylist_insertLast(anual, criaInfoProd(p, q, regime, fac),
                                     comparaInfoProd);
    if (indexMes != -1) {
        ip = al->body[indexMes];
        ip = updateInfoProd(ip, regime, q, fac);
    } else
        al = arraylist_insertLast(al, criaInfoProd(p, q, regime, fac),
                                  comparaInfoProd);
    return f;
}

static int comparaString(const void* a, const void* b) {
    return strcmp((char*)a, (char*)b);
}

static void dumpToArrayList(void* a, void* b) {
    InfoProd ip = (InfoProd)a;
    ArrayList* ret = (ArrayList*)b;
    arraylist_add(*ret, ip);
}

FilialMensal getMes(Filial f, int mes) { return f->meses[mes - 1]; }

static void freeFilialMes(FilialMensal fm) {
    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 5; j++)
            for (int k = 0; k < 10; k++) {
                avltree_delete(fm->clientes[i][j][k]);
            }
    free(fm);
}

static void freeFilialAnual(FilialAnual fa) {
    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 5; j++)
            for (int k = 0; k < 10; k++) {
                avltree_delete(fa->clientes[i][j][k]);
            }
    free(fa);
}

void freeFilial(Filial f) {
    for (int i = 0; i < 12; i++) freeFilialMes(f->meses[i]);
    freeFilialAnual(f->anual);
    free(f);
}

int getQuantidadeNFromInfoProd(InfoProd ip) { return ip->quantidadeN; }
int getQuantidadePFromInfoProd(InfoProd ip) { return ip->quantidadeP; }

Cliente getClienteFromClienteProds(ClienteProds cp) { return cp->c; }

int getNumeroClientesDoProduto(Produto p, Filial f) {
    int ret = 0;
    for (int l1 = 0; l1 < 26; l1++)
        for (int n1 = 0; n1 < 5; n1++)
            for (int n2 = 0; n2 < 10; n2++)
                avltree_for_each2(getFilialAnualAvlCliente(f, l1, n1, n2),
                                  quantosClientesCompraram, p, &ret);

    return ret;
}
