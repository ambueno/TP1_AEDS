/**
 * @file   lista.c
 * @brief  Arquivo com a implementação do TAD de lista.
 * @author Amanda Bueno
* @date 2021-07-10
 */

 /* Inclusões */
#include <stdio.h>
#include <stdlib.h>

#include "lista.h"
#include "prontuario.h"

/* Funções exportadas */
Lista_t novaLista() {
	Lista_t novaLista = (Lista_t)malloc(sizeof(struct Lista_s));
	novaLista->primeiro = NULL;
	return novaLista;
}

void insereOrdenadoLista(Lista_t lista, void* consulta) {
	ItemLista_t novo = (ItemLista_t)malloc(sizeof(struct ItemLista_s));
	novo->proximo = NULL;
	novo->consulta = consulta;
	if (!(lista->primeiro)) lista->primeiro = novo;

	if (comparaConsulta(novo->consulta, lista->primeiro->consulta) < 0) {
		novo->proximo = lista->primeiro;
		lista->primeiro = novo;
	}
	else {
		ItemLista_t aux = (ItemLista_t)lista->primeiro;
		while ((aux->proximo != NULL) && (comparaConsulta(novo->consulta, aux->proximo->consulta) < 0)) {
			aux = aux->proximo;
		}
		novo->proximo = aux->proximo;
		aux->proximo = novo;
	}
}

void liberaLista(Lista_t lista) {
	ItemLista_t aux = (ItemLista_t)lista->primeiro;
	while (aux) {
		ItemLista_t proximo = aux->proximo;
		liberaConsulta(aux->consulta);
		free(aux);
		aux = proximo;
	}
	free(lista);
}

void imprimeLista(Lista_t lista) {
	if (lista == NULL || lista->primeiro == NULL) return;
	ItemLista_t aux = (ItemLista_t)lista->primeiro;
	while (aux) {
		imprimeConsulta(aux->consulta);
		aux = aux->proximo;
	}
	(void)fprintf(stdout, "\n");
}

int buscaListaItem(Lista_t lista, void* consulta) {
	if (lista == NULL || lista->primeiro == NULL) return NULL;
	ItemLista_t aux = lista->primeiro;
	while (aux) {
		if ((comparaConsulta(consulta, aux->proximo->consulta) == 0)) return 1;
		aux = aux->proximo;
	}
	return NULL;
}

int listaBuscaData(Lista_t lista, void *data) {
	ItemLista_t atual = lista->primeiro;
	ItemLista_t proximo;
	while (atual != NULL) {
		proximo = atual->proximo;
		Consulta_t consulta = atual->consulta;
		if (comparaData(data, consulta->data ) == 0) {
			return 1;
		}
		atual = proximo;
	}
	return NULL;
}

void removeLista(Lista_t lista, void* consulta) {
	ItemLista_t aSerRemovido = (ItemLista_t)lista->primeiro;
	ItemLista_t aux = NULL;
	while (aSerRemovido) {
		if ((comparaConsulta(consulta, aux->proximo->consulta) == 0)) break;
		aux = aSerRemovido;
		aSerRemovido = aSerRemovido->proximo;
	}
	if (!(aSerRemovido)) return;
	if (!(aux)) {
		lista->primeiro = aSerRemovido->proximo;
	}
	else {
		aux->proximo = aSerRemovido->proximo;
	}
	free(aSerRemovido);
}