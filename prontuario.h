/**
* @file prontuario.h
* @brief Arquivo com as definições das estruturas que compõe o prontuario.
* @author Amanda Bueno
* @date 2021-07-10
*/

#pragma once
#ifndef __PRONTUARIO_h__
#define __PRONTUARIO_h__

/* Inclusões */
#include "lista.h"

/* Estrtuturas */
/// estrutura que representa os membros de um tipo de dado Data
struct Data_s {
	int dia, mes, ano;
};
typedef struct Data_s *Data_t;

/* Funções exportadas de data */
Data_t novaData(Data_t data, int ano, int mes, int dia);
int comparaData(Data_t dataComparada, Data_t dataReferencia);
void liberaData(Data_t data);

/// estrutura que representa os membros de um tipo de dado Consulta
struct Consulta_s {
	Data_t data;
	char *observacao;
};
typedef struct Consulta_s *Consulta_t;
/* Funções exportadas de data */
Consulta_t novaConsulta(char* observacao, Data_t data);
int comparaConsulta(Consulta_t consultaComparada, Consulta_t consultaReferencia);
void liberaConsulta(Consulta_t consulta);
void imprimeConsulta(Consulta_t consulta);

/// estrutura que representa os membros de um tipo de dado Prontuario
struct Prontuario_s {
	char *nome;
	Lista_t listaConsultas;
};
typedef struct Prontuario_s *Prontuario_t;

/* Funções exportadas de prontuario */
Prontuario_t novoProntuario(char* nome);
int comparaNomeProntuario(Prontuario_t prontuarioComparado, Prontuario_t prontuarioReferencia);
int comparaNome(char* nome, Prontuario_t prontuario);
void imprimeProntuario(Prontuario_t prontuario);
void imprimeProntuarioNomeData(Prontuario_t prontuario, Data_t data);
void insereConsultaProntuario(Prontuario_t prontuario, void* consulta);
void liberaProntuario(Prontuario_t prontuario);

/* Funções auxiliares exportadas */
void liberaString(char* string);

#endif // __PRONTUARIO_h__