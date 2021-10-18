/** @file product.h
 *  @brief API do modulo Produto.
 *
 *  Este módulo contém as funções necessárias para manipular um Produto.
 *
 *  @author Nelson Estevão (A76434)
 *  @author Pedro Ribeiro (A85493)
 *  @author Rui Mendes (A83712)
 *  @bug No know bugs.
 */

#ifndef _PRODUCT_H_
#define _PRODUCT_H_

#include <ctype.h>
#include <stdlib.h>

#define _GNU_SOURCE
#include <string.h>

#include "boolean.h"
#include "defines.h"

typedef struct produto *Produto;

#define STRLEN_PRODUCT 10

/** @brief Função que valida um Código de Produto.
 *
 *  @param codigo Código de Produto a validar.
 *  @return 0 se não for válido.
 */
int isProductCodeValid(char *codigo);

/** @brief Função que cria um Cliente.
 *
 *  @param codigo Código de Cliente a criar.
 *  @return Cliente criado.
 */
Produto criaProduto(char *codigo);

/** @brief Função que liberta a memória alocada por um Produto.
 *
 *  @param produto Produto a destruir.
 */
void freeProduto(void *produto);

/** @brief Função que devolve o código de Produto.
 *
 *  @param produto Produto do qual se pertende o código.
 *  @return código de produto.
 */
char *getCodigoProduto(Produto produto);

/** @brief Função que define se o Produto é usado ou não numa filial.
 *
 *  @param produto Produto a modificar.
 *  @param filial A filial a que se refere.
 *  @param b Booleano true ou false consoante se é usado ou não.
 *  @return Produto modificado.
 */
Produto setUsadoProduto(Produto produto, int filial, Bool b);

/** @brief Função que indica se um Produto é ou não usado numa filial.
 *
 *  @param produto Produto a verificar.
 *  @param filial A filial a que se refere.
 *  @return b Booleano true ou false consoante se é usado ou não.
 */
Bool getUsadoProduto(Produto produto, int filial);

/** @brief Função de comparação entre dois produtos.
 *
 *  @param p1 Produto 1 a comparar.
 *  @param p2 Produto 2 a comparar.
 *  @return Um inteiro inferiror a zero se p1 for menor que p2, 0 se forem
 * iguais, maior que zero se p1 for maior que p2.
 */
int comparaProdutos(const void *p1, const void *p2);

/** @brief Função que indica se um Produto é ou não usado numa qualquer.
 *
 *  @param produto Produto a verificar.
 *  @return b Booleano true ou false consoante se é usado ou não.
 */
Bool jaUsadoProduto(Produto produto);

#endif
