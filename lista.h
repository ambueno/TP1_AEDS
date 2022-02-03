/**
* @file lista.h
* @brief Arquivo com as definições do tipo lista.
* @author Amanda Bueno
* @date 2021-07-10
*/

#pragma once

#ifndef __LISTA_h__
#define __LISTA_h__

/* Inclusões */

/* Estrtuturas e tipos */
/// tipo item lista
struct ItemLista_s {
	void  *consulta;
	struct ItemLista_s *proximo;
};
typedef struct ItemLista_s *ItemLista_t;

struct Lista_s {
	ItemLista_t primeiro;
};
typedef struct Lista_s *Lista_t;

/* Funções exportadas */
Lista_t novaLista();
void insereOrdenadoLista(Lista_t lista, void* consulta);
void liberaLista(Lista_t lista);
void imprimeLista(Lista_t lista);
int buscaListaItem(Lista_t lista, void* consulta);
int listaBuscaData(Lista_t lista, void* data);
void removeLista(Lista_t lista, void* consulta); 


#endif 