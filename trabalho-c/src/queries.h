#include <stdio.h>
#include <stdlib.h>
#define _GNU_SOURCE
#include <string.h>

#include "arraylist.h"
#include "cat_clientes.h"
#include "cat_produtos.h"
#include "defines.h"
#include "facturacao.h"
#include "filial.h"
#include "parse.h"
#include "product.h"
#include "sale.h"
#include "sgv.h"
#include "sort.h"

SGV answerQuery1(SGV sgv, const char *path1r, const char *path2r,
                 const char *path3r);

ArrayList answerQuery2(SGV sgv, char c);

FacProd *answerQuery3(SGV sgv, char *codigo, int mes);

ArrayList *answerQuery4(SGV sgv);

ArrayList answerQuery7(Filial *filiais, Cliente c);

int answerQuery8(SGV, double *, int, int);

ArrayList *answerQuery9(Produto p, Filial filial);

ArrayList answerQuery10(SGV sgv, Cliente c, int mes);

ArrayList *answerQuery11(SGV sgv, int N);

ArrayList answerQuery12(SGV sgv, Cliente c);
