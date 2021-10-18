/** @file sort.h
 *  @brief API do modulo Cliente.
 *
 *  Este módulo contém as funções necessárias para ordenar estruturas.
 *
 *  @author Nelson Estevão (A76434)
 *  @author Pedro Ribeiro (A85493)
 *  @author Rui Mendes (A83712)
 *  @bug No know bugs.
 */

#ifndef _SORT_H_
#define _SORT_H_

#include "arraylist.h"
#include "facturacao.h"
#include "filial.h"

/** @brief Permite comparar duas estruturas 'InfoProd' de acordo com a faturação
 *
 * @param a Apontador para a primeira estrutura 'InfoProd'
 * @param b Apontador para a segunda estrutura 'InfoProd'
 * @return Resultado da comparação (menor que zero caso o primeiro 'InfoProd'
 * seja menor que o segundo, de acordo com o critério de comparação, ou maior
 * que zero, caso contrário.)
 */
int ordenaPorFacturacao(const void *a, const void *b);

/** @brief Permite comparar duas estruturas 'InfoProd' de acordo com a
 * quantidade
 *
 * @param a Apontador para a primeira estrutura 'InfoProd'
 * @param b Apontador para a segunda estrutura 'InfoProd'
 * @return Resultado da comparação (menor que zero caso o primeiro 'InfoProd'
 * seja menor que o segundo, de acordo com o critério de comparação, ou maior
 * que zero, caso contrário.)
 */
int ordenaPorQuantidade(const void *a, const void *b);

/** @brief Permite comparar duas estruturas 'FacProd' de acordo com a
 * quantidade
 *
 * @param a Apontador para a primeira estrutura 'FacProd'
 * @param b Apontador para a segunda estrutura 'FacProd'
 * @return Resultado da comparação (menor que zero caso o primeiro 'FacProd'
 * seja menor que o segundo, de acordo com o critério de comparação, ou maior
 * que zero, caso contrário.)
 */
int ordenaFacProdsQuantidade(const void *a, const void *b);

/** @brief Função que opera 'quickSort' num ArrayList
 *
 * @param al ArrayList a ordenar
 * @param low Menor índice
 * @param high Maior índice
 * @param comp Função de comparação
 */
void quickSort(ArrayList al, int low, int high, arraylist_cmpfn comp);

#endif