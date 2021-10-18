#include "cat_produtos.h"

struct cat_produtos {
    int total;
    Avl lista[26][26][9][10];
    int usados;
};

struct lista_produtos {
    ArrayList codigos;
};

void freeCatProds(CatProdutos cp) {
    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 26; j++)
            for (int k = 0; k < 9; k++)
                for (int h = 0; h < 10; h++) {
                    avltree_delete(cp->lista[i][j][k][h]);
                }
    free(cp);
}

CatProdutos inicializaCatProdutos() {
    CatProdutos ret = malloc(sizeof(struct cat_produtos));
    ret->total = ret->usados = 0;
    for (int i = 0; i < 26; i++)
        for (int j = 0; j < 26; j++)
            for (int k = 0; k < 9; k++)
                for (int h = 0; h < 10; h++)
                    ret->lista[i][j][k][h] =
                        avltree_create(comparaProdutos, freeProduto);
    return ret;
}

static int* getIndexProduto(Produto c) {
    int* indices = malloc(sizeof(int) * N_PART_PRODUTOS);
    char* codigo = getCodigoProduto(c);
    indices[0] = codigo[0] - 'A';
    indices[1] = codigo[1] - 'A';
    indices[2] = codigo[2] - '1';
    indices[3] = codigo[3] - '0';
    return indices;
}

CatProdutos insereProduto(CatProdutos catC, Produto c) {
    int* i = getIndexProduto(c);
    avltree_add(catC->lista[i[0]][i[1]][i[2]][i[3]], c);
    catC->total++;
    free(i);
    return catC;
}

Bool existeProduto(CatProdutos produtos, Produto c) {
    Produto ret;
    int* i = getIndexProduto(c);
    ret = avltree_find(produtos->lista[i[0]][i[1]][i[2]][i[3]], c);
    free(i);
    if (ret == NULL)
        return false;
    else
        return true;
}

Avl getCatProdsListaIndexBy(CatProdutos cp, int i, int j, int k, int h) {
    return (cp->lista[i][j][k][h]);
}

int getCatProdsTotal(CatProdutos cp) { return (cp->total); }

int getCatProdsNaoUsados(CatProdutos cp) { return cp->total - cp->usados; }

CatProdutos setCatProdsTotal(CatProdutos cp, int x) {
    cp->total = x;
    return cp;
}

static int getCatProdsUsados(CatProdutos cp) { return cp->usados; }

static CatProdutos setCatProdsUsados(CatProdutos cp, int x) {
    cp->usados = x;
    return cp;
}

static Produto getProduto(CatProdutos cp, Produto p) {
    int* i = getIndexProduto(p);
    Produto ret = avltree_find(cp->lista[i[0]][i[1]][i[2]][i[3]], p);
    free(i);
    return ret;
}

CatProdutos atualizaCatProdutos(CatProdutos produtos, Produto p, int f) {
    p = getProduto(produtos, p);
    if (getUsadoProduto(p, f - 1) == false) {
        if (jaUsadoProduto(p) == false)
            produtos =
                setCatProdsUsados(produtos, getCatProdsUsados(produtos) + 1);
        p = setUsadoProduto(p, f - 1, true);
    }
    return produtos;
}

static ArrayList* dumpNonUsedProductsAvl(ArrayList* arg,
                                         const avltreenode* root) {
    int i;
    Produto temp;
    if (root == NULL) return arg;
    if (root->left != NULL) {
        dumpNonUsedProductsAvl(arg, root->left);
    }
    temp = (Produto)root->data;
    for (i = 0; i < NUM_FILIAIS; i++)
        if (getUsadoProduto(temp, i) == false)
            arraylist_add(arg[i], getCodigoProduto(temp));
    if (jaUsadoProduto(temp) == false)
        arraylist_add(arg[NUM_FILIAIS], getCodigoProduto(temp));
    if (root->right != NULL) {
        dumpNonUsedProductsAvl(arg, root->right);
    }
    return arg;
}

ArrayList* totalNonUsedProducts(ArrayList* arg, CatProdutos cp) {
    int i, j, k, l;
    for (i = 0; i < 26; i++)
        for (j = 0; j < 26; j++)
            for (k = 0; k < 9; k++)
                for (l = 0; l < 10; l++)
                    arg = dumpNonUsedProductsAvl(arg,
                                                 cp->lista[i][j][k][l]->root);
    return arg;
}

static void addProdutoToList(void* x, void* l) {
    Produto p = (Produto)x;
    ArrayList* a = (ArrayList*)l;
    arraylist_add(*a, getCodigoProduto(p));
}

ArrayList getListProdutosByChar(CatProdutos cp, char c) {
    ArrayList ret = arraylist_create(comparaProdutos);
    int i = toupper(c) - 'A';
    for (int j = 0; j < 26; j++)
        for (int k = 0; k < 9; k++)
            for (int l = 0; l < 10; l++)
                avltree_for_each(cp->lista[i][j][k][l], addProdutoToList, &ret);
    return ret;
}
