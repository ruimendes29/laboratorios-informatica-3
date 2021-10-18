/** @file filial.h
 *  @brief API do modulo Filial.
 *
 *  Este módulo contém as funções necessárias para manipular uma Filial.
 *
 *  @author Nelson Estevão (A76434)
 *  @author Pedro Ribeiro (A85493)
 *  @author Rui Mendes (A83712)
 *  @bug No known bugs.
 */

#ifndef _FILIAL_H_
#define _FILIAL_H_

#include <string.h>

#include "arraylist.h"
#include "avl.h"
#include "client.h"
#include "product.h"

typedef struct filial* Filial;

typedef struct filialmensal* FilialMensal;

size_t getSizeStructFilial();

typedef struct filialanual* FilialAnual;

typedef struct clienteprods* ClienteProds;

typedef struct infoprod* InfoProd;

/** @brief Função que valida um inicializa um ClienteProds, estrutura que
 * relaciona um Cliente com os produtos comprados pelo mesmo.
 *
 *  @param c Cliente a partir do qual se pretende criar o ClienteProds.
 *  @return O ClienteProds inicializado.
 */
ClienteProds inicializaClienteProds(Cliente c);

/** @brief Função que valida um inicializa uma FilialMensal, estrutura que
 * possui informação sobre um mês numa filial.
 *
 *  @return A FilialMensal inicializada.
 */
FilialMensal inicializaFilialMensal();

/** @brief Função que valida um inicializa uma Filial.
 *
 *  @return A Filial inicializada.
 */
Filial inicializaFilial();

/** @brief Função que compara um InfoProd a um Produto através do Produto de
 * InfoProd.
 *
 *  @param x InfoProd que se pretende comparar.
 *  @param y Produto que se pretende comparar.
 *  @return 0 se o produto do InfoProd tiver o mesmo código do produto, -1 se
 * for menor ou 1 se for maior.
 */
int compareInfoProdToProduto(const void* x, const void* y);

/** @brief Função que insere um ClienteProds numa filial.
 *
 *  @param filial Filial em que se pretende inserir o ClienteProds.
 *  @param c Cliente a partir do qual se pretende criar o ClienteProds para
 * inserir na Filial.
 *  @return A Filial com o ClienteProds inserido.
 */
Filial insereClienteProds(Filial filial, Cliente c);

/** @brief Função que atualiza uma filial a partir de variáveis presentes numa
 * venda.
 *
 *  @param f Filial que se pretende atualizar.
 *  @param mes Mês que se pretende atualizar na filial.
 *  @param c Cliente que se pretende introduzir ou atualizar na filial no mês
 * dado.
 *  @param p Produto que se pretende introduzir ou atualizar na filial no mês
 * dado associado a um cliente.
 *  @param q Quantidade de produtos comprados na venda.
 *  @param fac Total facturado na venda.
 *  @param regime Variável que determine se um produto foi comprado em modo N ou
 * P.
 *  @return A Filial atualizada.
 */
Filial updateFilial(Filial f, int mes, Cliente c, Produto p, int q, float fac,
                    char regime);

/** @brief Função que retorna os produtos associados a um cliente num mês numa
 * filial.
 *
 *  @param f Filial em que se pretende consultar.
 *  @param c Cliente que se pretende consultar.
 *  @param mes Mês que se pretende consultar.
 *  @return ArrayList que contem os produtos associados ao cliente.
 */
ArrayList getProdutosFromCliente(Filial f, Cliente c, int mes);

/** @brief Função auxiliar usada para contar quantos clientes compraram um dado
 * produto.
 *
 *  @param x ClienteProds que se pretende ver se comprou o produto ou não.
 *  @param y Produto a contar o número de clientes.
 *  @param z Apontador para um inteiro onde é guardado o número de clientes
 * contados até ao momento.
 */
void quantosClientesCompraram(void* x, void* y, void* z);

/** @brief Função que retorna a avl de ClienteProds que possuam indices iguais
 * na hashtable.
 *
 *  @param f Filial em que se pretende consultar.
 *  @param i 1º índice da hashtable.
 *  @param j 2º índice da hashtable.
 *  @param k 3º índice da hashtable.
 *  @return Avl que contem os ClienteProds com indices iguais na hashtable.
 */
Avl getFilialAnualAvlCliente(Filial f, int i, int j, int k);

/** @brief Função que retorna o ArrayList de InfoProds de um ClienteProds.
 *
 *  @param cp ClienteProds que se pretende consultar.
 *  @return ArrayList que contem os InfoProds de um ClienteProds.
 */
ArrayList getProdutosFromClienteProds(ClienteProds cp);

/** @brief Função que liberta o espaço de uma Filial.
 *
 *  @param f Filial a libertar.
 */
void freeFilial(Filial f);

/** @brief Função que consulta a quantidade de produtos em modo N comprados num
 * InfoProd
 *
 *  @param ip InfoProd que se pretende consultar.
 *  @return Quantidade de produtos comprados em modo N de um dado InfoProd.
 */
int getQuantidadeNFromInfoProd(InfoProd ip);

/** @brief Função que consulta a quantidade de produtos em modo P comprados num
 * InfoProd
 *
 *  @param ip InfoProd que se pretende consultar.
 *  @return Quantidade de produtos comprados em modo P de um dado InfoProd.
 */
int getQuantidadePFromInfoProd(InfoProd ip);

/** @brief Função que consulta o Cliente de um ClienteProds
 *
 *  @param cp ClienteProds que se pretende consultar.
 *  @return Cliente do ClienteProds dado.
 */
Cliente getClienteFromClienteProds(ClienteProds cp);

/** @brief Função que compara um InfoProd a um InfoProd.
 *
 *  @param x 1º InfoProd que se pretende comparar.
 *  @param y 2º InfoProd que se pretende comparar.
 *  @return 0 se o produto do 1ºInfoProd tiver o mesmo código do produto do
 * 2ºInfoProd, -1 se for menor ou 1 se for maior.
 */
int comparaInfoProd(const void* a, const void* b);

/** @brief Função que copia um InfoProd.
 *
 *  @param ip Infoprod que se pretende copiar.
 *  @return O InfoProd copiado.
 */
InfoProd cloneInfoProd(InfoProd ip);

/** @brief Função que muda a QuantidadeP de um InfoProd.
 *
 *  @param ip Infoprod que se pretende mudar.
 *  @param x Valor para o qual se pretende mudar a QuantidadeP.
 *  @return O InfoProd mudado.
 */
InfoProd setQuantidadePInfoProd(InfoProd ip, int x);

/** @brief Função que consulta o Produto de um InfoProd
 *
 *  @param ip InfoProd que se pretende consultar.
 *  @return Produto do InfoProd dado.
 */
Produto getProdutoFromInfoProd(InfoProd ip);

/** @brief Função que muda a QuantidadeN de um InfoProd.
 *
 *  @param ip Infoprod que se pretende mudar.
 *  @param x Valor para o qual se pretende mudar a QuantidadeN.
 *  @return O InfoProd mudado.
 */
InfoProd setQuantidadeNInfoProd(InfoProd ip, int x);

/** @brief Função que retorna os produtos associados a um cliente numa filial.
 *
 *  @param f Filial em que se pretende consultar.
 *  @param c Cliente que se pretende consultar.
 *  @return ArrayList que contem os produtos associados ao cliente.
 */
ArrayList getAllProdutosFromCliente(Filial f, Cliente c);

/** @brief Função que consulta a facturação de produtos em modo N comprados num
 * InfoProd
 *
 *  @param ip InfoProd que se pretende consultar.
 *  @return Facturação de produtos comprados em modo N de um dado InfoProd.
 */
float getFacturacaoN(InfoProd ip);

/** @brief Função que consulta a facturação de produtos em modo P comprados num
 * InfoProd
 *
 *  @param ip InfoProd que se pretende consultar.
 *  @return Facturação de produtos comprados em modo P de um dado InfoProd.
 */
float getFacturacaoP(InfoProd ip);

/** @brief Função que muda a FacturaçãoN de um InfoProd.
 *
 *  @param ip Infoprod que se pretende mudar.
 *  @param x Valor para o qual se pretende mudar a FacturaçãoN.
 *  @return O InfoProd mudado.
 */
InfoProd setFacturacaoN(InfoProd ip, float x);

/** @brief Função que muda a FacturaçãoP de um InfoProd.
 *
 *  @param ip Infoprod que se pretende mudar.
 *  @param x Valor para o qual se pretende mudar a FacturaçãoP.
 *  @return O InfoProd mudado.
 */
InfoProd setFacturacaoP(InfoProd ip, float x);

/** @brief Função que conta o número de clientes que compraram um dado produto
 * numa filial.
 *
 *  @param p Produto que se pretende consultar.
 *  @param f Filial que se pretende consultar.
 *  @return O número de clientes que comprou o produto.
 */
int getNumeroClientesDoProduto(Produto p, Filial f);

/** @brief Função que liberta o espaço de um InfoProd.
 *
 *  @param x InfoProd a libertar.
 */
void freeInfoProd(void* x);

#endif