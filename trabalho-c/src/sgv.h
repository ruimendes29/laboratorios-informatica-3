/** @file sgv.h
 *  @brief API do modulo SGV.
 *
 *  Este módulo contém as funções necessárias para manipular a estrutura SGV.
 *
 *  @author Nelson Estevão (A76434)
 *  @author Pedro Ribeiro (A85493)
 *  @author Rui Mendes (A83712)
 *  @bug No know bugs.
 */

#ifndef _SGV_H_
#define _SGV_H_

#include "cat_clientes.h"
#include "cat_produtos.h"
#include "facturacao.h"
#include "filial.h"

typedef struct sgv* SGV;

/** @brief Aloca memória para a estrutura SGV
 *
 * @return SGV atualizado
 */
SGV initSGV();

/** @brief Liberta a memória alocado para a estrutura SGV
 *
 * @param sgv SGV a libertar
 */
void freeSGV(SGV sgv);

/** @brief Permite atribuir um catálogo de clientes a um SGV
 *
 * @param sgv SGV a atualizar
 * @param cp Catálogo de clientes
 * @return SGV atualizado
 */
SGV setClientes(SGV sgv, CatClientes cc);

/** @brief Permite obter o catálogo de clientes que consta do SGV
 *
 * @param sgv SGV de onde será obtido o catálogo de clientes
 * @return Catálogo de clientes
 */
CatClientes getClientes(SGV sgv);

/** @brief Permite atribuir um catálogo de produtos a um SGV
 *
 * @param sgv SGV a atualizar
 * @param cp Catálogo de produtos
 * @return SGV atualizado
 */
SGV setProdutos(SGV sgv, CatProdutos cp);

/** @brief Permite obter o catálogo de produtos que consta do SGV
 *
 * @param sgv SGV de onde será obtido o catálogo de produtos
 * @return Catálogo de produtos
 */
CatProdutos getProdutos(SGV sgv);

/** @brief Permite atribuir uma faturação a um SGV
 *
 * @param sgv SGV a atualizar
 * @param ft Faturação
 * @return SGV atualizado
 */
SGV setFaturacao(SGV sgv, FacTotal ft);

/** @brief Permiter obter a faturação associada a um SGV
 *
 * @param SGV de onde será obtida a informação
 * @return Faturação
 */
FacTotal getFaturacao(SGV sgv);

/** @brief Permite associar uma filial a um SGV
 *
 * @param sgv SGV a atualizar
 * @param filial Número da filial
 * @param f Estrutura da filial
 * @return SGV atualizado
 */
SGV setSingleFilial(SGV sgv, int filial, Filial f);

/** @brief Permite obter as filiais associada a um SGV (sob a forma de array)
 *
 * @param sgv SGV de onde serão obtidas as filiais
 * @return Array de filiais
 */
Filial* getFiliais(SGV sgv);

/** @brief Permite alterar o número de vendas válidas associadas a uma filial
 *
 * @param sgv SGV a atualizar
 * @param v Número de vendas válidas
 * @return SGV atualizado
 */
SGV setVendasValidas(SGV sgv, int v);

/** @brief Permite obter o número de vendas válidas associadas a uma filial
 *
 * @param SGV de onde será obtida a informação
 * @return Número de vendas válidas associadas ao SGV
 */

int getVendasValidas(SGV sgv);

#endif