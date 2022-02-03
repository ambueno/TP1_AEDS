/**
 * @file   arvore.c
 * @brief  Arquivo com a implementação do TAD de arvore.
 * @author Amanda Bueno
* @date 2021-07-10
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvore.h"

Arvore_t criaArvore() {
	Arvore_t nova = (Arvore_t)malloc(sizeof(struct Arvore_s));
	nova->raiz = NULL;
	return nova;
}

static void insereArvoreRecursivo(No_t arvore, No_t novoNo) {
	int resultadoComparacao = comparaNome(novoNo->prontuario, arvore->prontuario);
	if (resultadoComparacao > 0) {
		if (arvore->direita) (insereArvoreRecursivo(arvore->direita, novoNo));
		else (arvore->direita = novoNo);
	}
	else {
		if (arvore->esquerda) (insereArvoreRecursivo(arvore->esquerda, novoNo));
		else (arvore->esquerda = novoNo);
	}
}

void criaNoArvore(Arvore_t arvore, Prontuario_t prontuario) {
	No_t novoNo = (No_t)malloc(sizeof(struct No_s));
	novoNo->prontuario = prontuario;
	novoNo->esquerda = NULL;
	novoNo->direita = NULL;
	if (arvore->raiz)(insereArvoreRecursivo(arvore->raiz, novoNo));
	else (arvore->raiz = novoNo);
}

int insereArvoreIterativo(Arvore_t arvore, Prontuario_t prontuario){
	if (arvore == NULL) return 1;
	No_t novo = (No_t)malloc(sizeof(struct No_s));
	if (novo == NULL) return 1;

	novo->prontuario = prontuario;
	novo->direita = NULL;
	novo->esquerda = NULL;

	if (arvore->raiz == NULL)
	{
		arvore->raiz = novo;
		return 0;
	}

	No_t atual = arvore->raiz;
	No_t pai = NULL;

	int resultado = strcmp(prontuario->nome, atual->prontuario->nome);
	while (atual != NULL)
	{
		pai = atual;
		if (resultado == 0)
		{
			free(novo);
			return 1; // elemento já existe
		}

		if (resultado > 0) atual = atual->direita;
		else atual = atual->esquerda;
	}
	int resultadoAux = strcmp(prontuario->nome, pai->prontuario->nome);
	if (resultadoAux > 0) pai->direita = novo;
	else pai->esquerda = novo;
	return 0;
}

static void liberaNoRecursivo(No_t no) {
	if (no == NULL) return;
	liberaNoRecursivo(no->esquerda);
	liberaNoRecursivo(no->direita);
	free(no);
	no = NULL;
}

void liberaArvore(Arvore_t arvore) {
	if (arvore == NULL) return;
	liberaNoRecursivo(arvore->raiz);
	free(arvore);
}

static Prontuario_t arvoreBuscaRecursivaProntuario(No_t arvore, char *nome) {
	if (!arvore) return NULL;
	int resultado = comparaNome(nome, arvore->prontuario);
	if (resultado > 0) return arvoreBuscaRecursivaProntuario(arvore->direita, nome);
	else if (resultado < 0) return arvoreBuscaRecursivaProntuario(arvore->esquerda, nome);
	else return arvore->prontuario;
}

Prontuario_t arvoreBuscaProntuario(Arvore_t arvore, char *nome) {
	return arvoreBuscaRecursivaProntuario(arvore->raiz, nome);
}


No_t buscaArvoreRecursivaNo(No_t no, Prontuario_t chave) {
	if (!no) return NULL;
	int resultado = comparaNomeProntuario(chave, no->prontuario);
	if ((resultado == 0)) return no;
	else if (resultado > 0) (no->esquerda = buscaArvoreRecursivaNo(no->esquerda, chave));
	else if (resultado < 0) (no->direita = buscaArvoreRecursivaNo(no->direita, chave));
	return NULL;
}

void arvoreIteraEmOrdemRecursivo(No_t no) {
	if (no) {
		arvoreIteraEmOrdemRecursivo(no->esquerda);
		// operação
		arvoreIteraEmOrdemRecursivo(no->direita);
	}
	return;
}

static Prontuario_t removeNo(No_t no, Prontuario_t prontuario) {
	No_t aSerRemovido = buscaArvoreRecursivaNo(no->prontuario, prontuario);
	if (!(aSerRemovido->direita)) return (aSerRemovido->esquerda);
	if (!(aSerRemovido->esquerda)) return (aSerRemovido->direita);
	No_t aux = (No_t)malloc(sizeof(struct No_s));
	aux = aSerRemovido;
	if (!(aSerRemovido->direita->esquerda)) {
		aux->prontuario = aSerRemovido->direita->prontuario;
		aux->direita = aSerRemovido->direita->esquerda;
		return aSerRemovido;
	}
	No_t sucessorPai = (No_t)malloc(sizeof(struct No_s));;
	while (aSerRemovido->direita->esquerda) {
		sucessorPai = aSerRemovido;
		aSerRemovido = aSerRemovido->esquerda;
	}
	aux->prontuario = aSerRemovido->prontuario;
	sucessorPai->esquerda = aSerRemovido->direita;

	free(aux);
	free(sucessorPai);

	return aSerRemovido->prontuario;
	// eu sei que eu deveria dar um free no nó, mas não sei como fazê=lo sem perder o seu dado 
}

Prontuario_t removeArvore(Arvore_t arvore, Prontuario_t prontuario) {
	Prontuario_t prontuarioAux = (removeNo(arvore->raiz, prontuario));
	return prontuarioAux;
}

int comparaArvoreRecursivo(No_t no, Prontuario_t prontuario) {
	if (no) {
		comparaArvoreRecursivo(no->esquerda, prontuario);
		comparaArvoreRecursivo(no->direita, prontuario);
	}
	return 0;
}

void acessaProntuarioArvoreRecursivo(No_t no, Data_t data) {
	if (no) {
		acessaProntuarioArvoreRecursivo(no->esquerda, data);
		imprimeProntuarioNomeData(no->prontuario, data);
		acessaProntuarioArvoreRecursivo(no->direita, data);
	}
	return;
}
