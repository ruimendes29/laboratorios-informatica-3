/** @file navegador.h
 *  @brief API do navegador.
 *
 *  Este módulo contém as funções necessárias para fazer o display de dados
 * através de um sistema de navegação entre páginas.
 *
 *  @author Nelson Estevão (A76434)
 *  @author Pedro Ribeiro (A85493)
 *  @author Rui Mendes (A83712)
 *  @bug No know bugs.
 */

#ifndef _NAVEGADOR_H_
#define _NAVEGADOR_H_

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define _GNU_SOURCE
#include <string.h>

#include "arraylist.h"
#include "colors.h"
#include "menu.h"

#define STRPPAG 30

typedef struct strings *ListaStrings;
typedef struct pagina *Pagina;

/** @brief Função que mostra resultados páginados.
 *
 *  @param l Um ArrayList de strings de resultados.
 *  @param cabecalho Uma string com o cabeçalho.
 */
void displayStructure(ArrayList l, char *cabecalho);

/** @brief Função que mostra resultados de várias tabelas páginadas.
 *
 *  @param l Um Array de ArrayList de strings de resultados.
 *  @param cabecalho Uma string com o cabeçalho.
 */
void displayStructureArray(ArrayList *l, int size);

#endif
