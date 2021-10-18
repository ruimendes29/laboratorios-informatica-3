/** @file parse.h
 *  @brief Modulo de Parsing.
 *
 *  Este módulo contém as funções para ler os ficheiros de produtos e clientes.
 *
 *  @author Nelson Estevão (A76434)
 *  @author Pedro Ribeiro (A85493)
 *  @author Rui Mendes (A83712)
 *  @bug No know bugs.
 */

#ifndef _PARSE_H_
#define _PARSE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "avl.h"
#include "cat_clientes.h"
#include "cat_produtos.h"
#include "facturacao.h"
#include "filial.h"
#include "product.h"

/** @brief Função que lê um ficheiro de Produtos e constrói o catalogo de
 * produtos e a faturação.
 *
 *  @param input Caminho para o ficheiro de Produtos.
 *  @return Um catalogo de produtos.
 */
CatProdutos processProducts(CatProdutos, FacTotal, const char *input);

/** @brief Função que lê um ficheiro de Clientes e constrói o catalogo de
 * clientes e as Filiais.
 *
 *  @param input Caminho para o ficheiro de Clientes.
 *  @return Um catalogo de clientes.
 */
CatClientes processClients(CatClientes, Filial filiais[NUM_FILIAIS],
                           const char *input);

#endif
