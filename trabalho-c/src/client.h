/** @file client.h
 *  @brief API do modulo Cliente.
 *
 *  Este módulo contém as funções necessárias para manipular um Cliente.
 *
 *  @author Nelson Estevão (A76434)
 *  @author Pedro Ribeiro (A85493)
 *  @author Rui Mendes (A83712)
 *  @bug No know bugs.
 */

#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <ctype.h>
#include <stdlib.h>

#define _GNU_SOURCE
#include <string.h>

#include "boolean.h"
#include "defines.h"

typedef struct cliente *Cliente;

#define STRLEN_CLIENT 10

/** @brief Função que valida um Código de Cliente.
 *
 *  @param codigo Código de Cliente a validar.
 *  @return 0 se não for válido.
 */
int isClientCodeValid(char *codigo);

/** @brief Função que cria um Cliente.
 *
 *  @param codigo Código de Cliente a criar.
 *  @return Cliente criado.
 */
Cliente criaCliente(char *codigo);

/** @brief Função que liberta a memória alocada por um Cliente.
 *
 *  @param cliente Cliente a destruir.
 */
void freeCliente(void *cliente);

/** @brief Função que devolve o código de Cliente.
 *
 *  @param cliente Cliente do qual se pertende o código.
 *  @return código de cliente.
 */
char *getCodigoCliente(Cliente);

/** @brief Função que define se o Cliente é usado ou não numa filial.
 *
 *  @param cliente Cliente a modificar.
 *  @param filial A filial a que se refere.
 *  @param b Booleano true ou false consoante se é usado ou não.
 *  @return Cliente modificado.
 */
Cliente setUsadoCliente(Cliente cliente, int filial, Bool b);

/** @brief Função que indica se um Cliente é ou não usado numa filial.
 *
 *  @param cliente Cliente a verificar.
 *  @param filial A filial a que se refere.
 *  @return b Booleano true ou false consoante se é usado ou não.
 */
Bool getUsadoCliente(Cliente cliente, int filial);

/** @brief Função de comparação de dois clientes.
 *
 *  @param c1 Cliente 1 a comparar.
 *  @param c2 Cliente 2 a comparar.
 *  @return Um inteiro inferiror a zero se c1 for menor que c2, 0 se forem
 * iguais, maior que zero se c1 for maior que c2.
 */
int comparaClientes(const void *c1, const void *c2);

/** @brief Função que indica se um Cliente é ou não usado numa qualquer.
 *
 *  @param cliente Cliente a verificar.
 *  @return b Booleano true ou false consoante se é usado ou não.
 */
Bool jaUsadoCliente(Cliente);

/** @brief Função que indica se um Cliente é ou não usado em todas as filiais.
 *
 *  @param cliente Cliente a verificar.
 *  @return b Booleano true ou false consoante se é usado ou não em todas as
 * filiais.
 */
Bool usadoTodasFiliaisCliente(Cliente);

#endif
