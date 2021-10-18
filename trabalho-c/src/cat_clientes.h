/** @file cat_clientes.h
 *  @brief API do módulo catálogo de clientes
 *
 *  Este módulo contém as funções necessários para manipular o catálogo de
 *  clientes
 *
 *  @author Nelson Estevão (A76434)
 *  @author Pedro Ribeiro (A85493)
 *  @author Rui Mendes (A83712)
 *  @bugs No known bugs
 *
 */

#ifndef _CAT_CLIENTES_H_
#define _CAT_CLIENTES_H_

#define _GNU_SOURCE
#include <string.h>

#include "arraylist.h"
#include "avl.h"
#include "boolean.h"
#include "client.h"

#define N_PART_CLIENTES 3

typedef struct cat_clientes* CatClientes;
typedef struct lista_clientes* ListaClientes;

/** @brief Aloca memória para o catálogo de clientes
 *
 * @return Catálogo de Clientes vazio
 */
CatClientes inicializaCatClientes();

/** @brief Insere um cliente no catálogo de clientes
 *
 * @param cc Catálogo de clientes onde será inserido o cliente
 * @param c Cliente a inserir no catálogo de clientes
 * @return Catálogo de Clientes atualizado
 */
CatClientes insereCliente(CatClientes cc, Cliente c);

/** @brief Verifica se um determinado cliente existe no catálogo de clientes
 *
 * @param cc Catálogo de clientes
 * @param c Cliente
 * @return 'false' se o cliente não existir no catálogo ou 'true' caso contrário
 */
Bool existeCliente(CatClientes cc, Cliente c);

/** @brief Permite obter a avl onde está um cliente (cujos índices do array de
 * avl's já foram calculados)
 *
 * @param cc Catálogo de clientes
 * @param i Primeiro indice (do array de índices)
 * @param j Segundo indice (do array de índices)
 * @param k Terceiro indice (do array de índices)
 * @return Avl onde está o cliente cujo índice foi calculado
 */
Avl getCatClientesListaIndexBy(CatClientes cc, int i, int j, int k);

/** \brief Permite obter um cliente no array de arrays de avls
 * @param cc Catálogo de clientes
 * @param c Cliente a encontrar
 * @return Cliente a encontrar
 */
Cliente getCliente(CatClientes cc, Cliente c);

/** @brief Permite alterar o número de clientes no catálogo
 *
 * @param cc Catálogo de clientes
 * @param x Número de clientes
 * @return Catálogo de clientes atualizado
 */
CatClientes setCatClientesTotal(CatClientes cc, int x);

/** @brief Permite obter o número de clientes total do catálogo
 *
 * @param cc Catálogo de clientes
 * @return Número total de clientes no catálogo
 */
int getCatClientesTotal(CatClientes cc);

/** @brief Permite obter o número de clientes não usados que constam do catálogo
 *
 * @param cc Catálogo de clientes
 * @return Número de clientes não utilizados
 */
int getCatClientesNaoUsados(CatClientes cc);

/** @brief Permite atualizar o catálogo de clientes com um novo cliente
 *
 * @param cc Catálogo de clientes
 * @param c Cliente
 * @param f Filial
 * @return Catálogo de clientes atualizado
 */
CatClientes atualizaCatClientes(CatClientes cc, Cliente c, int f);

/** @rief Permite obter a lista de clientes que foram utilizados em todas as
 * filiais
 *
 * @param cc Catálogo de clientes
 * @return Lista dos clientes utilizados em todas as filiais
 */
ArrayList getListClientesUsadosTodasFiliais(CatClientes cc);

/** @brief Permite libertar o espaço alocado para o catálogo de clientes
 *
 * @param cc Catálogo de clientes
 */
void freeCatClientes(CatClientes);

#endif