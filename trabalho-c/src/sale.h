/** @file sale.h
 *  @brief API do modulo Venda.
 *
 *  Este módulo contém as funções necessárias para manipular uma Venda.
 *
 *  @author Nelson Estevão (A76434)
 *  @author Pedro Ribeiro (A85493)
 *  @author Rui Mendes (A83712)
 *  @bug No know bugs.
 */

#ifndef _SALE_H_
#define _SALE_H_

#include <stdio.h>
#include <stdlib.h>

#define _GNU_SOURCE
#include <string.h>

#include "avl.h"
#include "cat_clientes.h"
#include "cat_produtos.h"
#include "client.h"
#include "defines.h"
#include "facturacao.h"
#include "filial.h"
#include "product.h"

#define SALESBUFFER 100
#define REALLOC_SIZE_VENDAS 100

typedef struct sale *Sale;

/** @brief Função que verifica se uma String se encontra num Array de Strings
 *
 * @param array Array de Strings.
 * @param low Inteiro que indica em que índice do array começamos a verificar.
 * @param high Inteiro que indica em que índice do array acabamos de verificar.
 * @param keyword String cuja presença no Array vamos testar.
 * @return O índice em que se encontra no Array caso esteja lá presente ou -1
      caso contrário.
 */
int isInArrayBinary(char **array, int low, int high, char *keyword);

/** @brief Função que verifica se um produto se encontra no array de prdoutos
 * válidos.
 *
 * @param product Produto a testar
 * @param produtcs Array de produtos válidos
 * @param productsSize Tamanho do array de produtos válidos
 * @return O índice em que se encontra no Array caso esteja lá presente ou -1
 *    caso contrário.
 */
int doesProductExist(char *product, char **products, int productsSize);

/** @brief Função que verifica se um cliente se encontra no Array de clientes
 * válidos.
 *
 * @param client Cliente a testar
 * @param clients Array de clientes válidos
 * @param clientsSize Tamanho do array de clientes válidos
 * @return O índice em que se encontra no Array caso esteja lá presente ou -1
 * caso contrário.
 */
int doesClientExist(char *client, char **clients, int clientsSize);

/** @brief Função que devolve um produto associado a uma venda.
 *
 * @param s A venda do qual se pretende o produto.
 * @return O Produto dessa venda.
 */
Produto getSaleProduto(Sale s);

/** @brief Função que devolve um cliente associado a uma venda.
 *
 * @param s A venda do qual se pretende o produto.
 * @return O Produto dessa venda.
 */
Cliente getSaleCliente(Sale s);

/** @brief Função que devolve a filial associada a essa venda.
 *
 * @param s A venda da qual se pretende a filial.
 * @return O número da filial associada a essa venda.
 */
int getSaleFilial(Sale s);

/** @brief Função que devolve o preço associada a essa venda.
 *
 * @param s A venda da qual se pretende saber o preço.
 * @return O valor da venda.
 */
double getSalePreco(Sale s);

/** @brief Função que devolve o número de unidades associadas a essa venda.
 *
 * @param s A venda da qual se pretende saber o número de unidades.
 * @return O número de unidades associadas a essa venda.
 */
int getSaleUnidades(Sale s);

/** @brief Função que devolve o mês em que ocorreu a venda.
 *
 * @param s A venda do qual se pretende saber o mês.
 * @return O mês em que a venda ocorreu.
 */
int getSaleMes(Sale s);

/** @brief Função que devolve em que modo ocorreu a venda.
 *
 * @param s A venda do qual se pretende saber o modo.
 * @return O modo da venda, se foi promoção ou venda normal.
 */
char getSaleRegime(Sale s);

/** @brief Função que devolve o código de cliente associado à venda.
 *
 * @param s A venda do qual se pretende saber o código de cliente.
 * @return O código de cliente associado à venda.
 */
char *getSaleClienteCodigo(Sale s);

/** @brief Função que devolve o código de produto associado à venda.
 *
 * @param s A venda do qual se pretende saber o código de produto.
 * @return O código de produto associado à venda.
 */
char *getSaleProdutoCodigo(Sale s);

/** @brief Função que valida as vendas contidas no ficheiro: Vendas_1M.txt
 *
 * @param clientes Array de clientes válidos
 * @param cSize Tamanho do array de clientes válidos
 * @param produtos Array de produtos válidos
 * @param pSize Tamanho do array de produtos válidos
 * @param read String do nome do ficheiro de vendas a ler
 * @param write String do nome do ficheiro onde serão escritas as vendas válidas
 * @return Número de vendas válidas contidas no ficheiro Vendas_1M.txt
 */
int processaVendas(CatClientes clientes, CatProdutos produtos, FacTotal ft,
                   Filial filiais[NUM_FILIAIS], const char *read);

#endif
