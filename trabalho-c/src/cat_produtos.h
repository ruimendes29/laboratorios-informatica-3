/** @file cat_produtos.h
 *  @brief API do módulo catálogo de produtos
 *
 *  Este módulo contém as funções necessários para manipular o catálogo de
 *  produtos
 *
 *  @author Nelson Estevão (A76434)
 *  @author Pedro Ribeiro (A85493)
 *  @author Rui Mendes (A83712)
 *  @bugs No known bugs
 *
 */

#ifndef _CAT_PRODUTOS_H_
#define _CAT_PRODUTOS_H_

#define _GNU_SOURCE
#include <string.h>

#include "arraylist.h"
#include "avl.h"
#include "boolean.h"
#include "product.h"

#define N_PART_PRODUTOS 4

typedef struct cat_produtos* CatProdutos;
typedef struct lista_produtos* ListaProdutos;

/** @brief Aloca memória para o catálogo de produtos
 *
 * @return Catálogo de Produtos vazio
 */
CatProdutos inicializaCatProdutos();

/** @brief Insere um produto no catálogo de produtos
 *
 * @param cp Catálogo de produtos
 * @param p Produto a inserir no catálogo de produtos
 * @return Catálogo de produtos atualizado
 */
CatProdutos insereProduto(CatProdutos cp, Produto p);

/** @brief Verifica se um determinado produto existe no catálogo de produtos
 *
 * @param cp Catálogo de produtos
 * @param p Produto
 * @return 'false' se o produto não exisitir no catálogo ou 'true' caso
 * contrário
 */
Bool existeProduto(CatProdutos, Produto);

/** @brief Permite obter a avl onde está um produto (cujos índices do array de
 * avl's já foram calculados)
 *
 * @param cp Catálogo de produtos
 * @param i Primeiro índice (do array de índices)
 * @param j Segundo índice (do array de índices)
 * @param k Terceiro índice (do array de índices)
 * @param l Quarto índice (do array de índices)
 * @return Avl onde está o produto cujo índice foi calculado
 */
Avl getCatProdsListaIndexBy(CatProdutos cp, int i, int j, int k, int l);

/** @brief Permite obter o número de produtos que constam do catálogo
 *
 * @param cp Catálogo de produtos
 * @return Número de produtos que constam do catálogo
 */
int getCatProdsTotal(CatProdutos);

/** @brief Permite alterar o número total de produtos do catálogo
 *
 * @param cp Catálogo de produtos
 * @param n Número de clientes
 * @return Catálogo de produtos atualizado
 */
CatProdutos setCatProdsTotal(CatProdutos cp, int n);

/** @brief Permite obter o número de produtos não usados que constam do catálogo
 * de produtos
 *
 * @param cp Catálogo de produtos
 * @return Número de produtos não usados
 */
int getCatProdsNaoUsados(CatProdutos cp);

/** @brief Permite atualizar o catálogo de produtos com um novo produto
 *
 * @param cp Catálogo de produtos
 * @param p Produto
 * @param f Filial
 * @return Catálogo de produtos atualizado
 */
CatProdutos atualizaCatProdutos(CatProdutos cp, Produto p, int f);

/** @brief Permite atualizar um array de ArrayList onde se encontram os produtos
 * não usados organizados por filial
 *
 * @param arg Array de ArrayList onde serão guardadas as listas de produtos
 * @param cp Catálogo de produtos
 * @return Array de ArrayList com toda a informação relativa a produtos não
 * usados por filial
 */
ArrayList* totalNonUsedProducts(ArrayList* arg, CatProdutos cp);

/** @brief Permite libertar o espaço alocado para o catálogo de produtos
 *
 * @param cp Catálogo de produtos
 */
void freeCatProds(CatProdutos);

/** \brief Permite obter a lista de produtos cujo código começa por um
 * determinado carater
 * @param cp Catálogo de produtos
 * @param c Carater pelo qual começam os códigos de produto
 * @return Lista dos produtos cujo código começa pelo carater recebido como
 * argumento
 */
ArrayList getListProdutosByChar(CatProdutos cp, char c);

#endif