/**
* @file funcoes.h
* @brief Arquivo para a exportação das funções principais do programa.
* @author Amanda Bueno
* @date 2021-07-10
*/

#pragma once
#ifndef __FUNCOES_h__
#define __FUNCOES_h__

#include "arvore.h"
#include "lista.h"
#include "prontuario.h"

/* Funções exportadas */
Arvore_t criaArvore();
void ConsultarPaciente(Arvore_t arvore);
void ConsultarData(Arvore_t arvore);
void InserirConsulta(Arvore_t arvore);
void RemoverProntuario(Arvore_t arvore);

#endif 
