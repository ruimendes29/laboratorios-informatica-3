/** @file facturacao.h
 *  @brief API do modulo Facturacao.
 *
 *  Este módulo contém as funções necessárias para manipular a Facturacao.
 *
 *  @author Nelson Estevão (A76434)
 *  @author Pedro Ribeiro (A85493)
 *  @author Rui Mendes (A83712)
 *  @bug No known bugs.
 */

#ifndef _FACTURACAO_H_
#define _FACTURACAO_H_

#include "arraylist.h"
#include "avl.h"
#include "cat_produtos.h"
#include "defines.h"
#include "product.h"

typedef struct facprod* FacProd;

typedef struct facmensal* FacMensal;

typedef struct factotal* FacTotal;

typedef struct facanual* FacAnual;

/** @brief Aloca espaço para a estrutura da faturação
 *
 * @return Estrutura da faturação vazia
 */
extern FacTotal inicializaFacTotal();

/** @brief Permite inserir a faturação de um produto na faturação total
 *
 * @param ft Faturação total a atualizar
 * @pram p Produto a inserir
 * @return Faturação total atualizada
 */
extern FacTotal insereFacProd(FacTotal ft, Produto p);

/** @brief Permite atualizara faturação referente a um produto
 *
 * @param p Produto cuja faturação será atualizada
 * @param mes Mês cuja faturação será atualizada
 * @param filial Filiaj cuja faturação será alterada
 * @param regime Regime em que foi adquirido o produto
 * @param unidades Unidades do produto que foram transacionadas
 * @param ft Faturação total a ser atualizada
 * @return Faturação total atualizada
 */
extern FacTotal updateFacProd(Produto p, int mes, int filial, char regime,
                              double preco, int unidades, FacTotal ft);

/** @brief Permite obter o total faturado num determinado mês
 *
 * @param f Faturação total
 * @param mes Mês
 * @return Total faturado durante esse mẽs
 */
double getFacturacaoMes(FacTotal f, int mes);

/** @brief Permite obter o total faturado com um determinado produto
 *
 * @param fp Facturação referente a um produto
 * @return Total faturado com o produto
 */
double getFacturacaoTotalFromProd(FacProd fp);

/** @brief Permite obter o total fatuaado com um determinado produto com
 *
 * transações em regime N
 * @param fp Faturação referente a um produto
 * @return Total faturado com o produto em regime N
 */
double getFacturacaoNFromProd(FacProd fp);

/** @brief Permite obter o total fatuaado com um determinado produto com
 * transações em regime P
 *
 * @param fp Faturação referente a um produto
 * @return Total faturado com o produto em regime P
 */
double getFacturacaoPFromProd(FacProd fp);

/** @brief Liberta o espaço alocado para a estrutura da faturação
 *
 * @param f Estrutura de faturação a libertar
 */
void freeFacturacao(FacTotal f);

/** @brief Liberta o espaço alocado para estrutura de faturação de um produto
 *
 * @param x Apontador para a estrutura de faturação de um produto
 */
void freeFacProd(void* x);

/** @brief Permite obter o produto de uma faturação de produto
 *
 * @param Faturação referente a um produto
 * @return Produto ao qual diz respeito a faturação
 */
Produto getProdutoFromFacProd(FacProd fp);

/** @brief Permite obter o número de unidades transacionadas de um produto
 *
 * @param fp Faturação do produto
 * @return Número de unidades transacionadas desse produto
 */
int getQuantidadeFromFacProd(FacProd fp);

/** @brief Permite obter o número de linhas de vendas referentes a um produto em
 * modo N
 *
 * @param fp Faturação referente ao produto
 * @return Número de linhas em regime N referentes ao produto
 */
int getRegistosVendaN(FacProd fp);

/** @brief Permite obter o número de linhas de vendas referentes a um produto em
 * modo P
 *
 * @param fp Faturação referente ao produto
 * @return Número de linhas em regime P referentes ao produto
 */
int getRegistosVendaP(FacProd);

/** @brief Permite obter a faturação de um produto em todas as filiais
 *
 * @param ft Faturação total
 * @param p Produto
 * @param mes Mês de faturação
 * @return Array com as faturações do produto, num determinado, em todas as
 * filiais
 */
FacProd* getFacProdsFiliaisProduto(FacTotal ft, Produto p, int mes);

/** @brief Permite obter a quantidade de produtos transacionada num mês
 *
 * @param ft Faturação total
 * @param mes Mês
 * @return Quantidade de produtos transacionada durante o mês
 */
int getQuantidadeMes(FacTotal ft, int mes);

/** @brief Permite obter a lista dos N produtos mais vendidos numa filial
 *
 * @param N Número de produtos
 * @param ft Faturação total
 * @param f Filial
 * @return ArrayList com N produtos mais vendidos na filial recebida como
 * argumento
 */
ArrayList getNProdutosMaisVendidos(int N, FacTotal ft, int f);

#endif