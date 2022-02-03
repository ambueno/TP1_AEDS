/**
* @file arvore.h
* @brief Arquivo com as definições do tipo arvore.
* @author Amanda Bueno
* @date 2021-07-10
*/

#pragma once
#ifndef __ARVORE_h__
#define __ARVORE_h__

#include "prontuario.h"
/// 
struct No_s {
	Prontuario_t prontuario;
	struct No_s *esquerda;
	struct No_s *direita;
};
typedef struct No_s *No_t;

struct Arvore_s {
	struct No_s *raiz;
};
typedef struct Arvore_s *Arvore_t;

/* Funções exportadas */
Arvore_t criaArvore();
int insereArvoreIterativo(Arvore_t arvore, Prontuario_t prontuario);
void criaNoArvore(Arvore_t arvore, Prontuario_t prontuario);
void liberaArvore(Arvore_t arvore);
Prontuario_t arvoreBuscaProntuario(Arvore_t arvore, char* nome);
No_t buscaArvoreRecursivaNo(No_t no, Prontuario_t prontuario);
void arvoreIteraEmOrdemRecursivo(No_t no);
Prontuario_t removeArvore(Arvore_t arvore, Prontuario_t prontuario);
void acessaProntuarioArvoreRecursivo(No_t no, Data_t data);

#endif 
