/**
* @file funcoes.c
* @brief Arquivo com a implementação das funções principais do programa.
* @author Amanda Bueno
* @date 2021-07-10
*/
/* Inclusões */
#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"

#define MAX_STRING 256

/* Funções */
void ConsultarPaciente(Arvore_t arvore) {
	char nome[MAX_STRING];
	(void)fprintf(stdout, "Digite o nome do paciente: ");
	fgets(nome, MAX_STRING, stdin);
	nome[strlen(nome) - 1] = '\0';

	// 
	Prontuario_t prontuario = arvoreBuscaProntuario(arvore, nome);
	if (prontuario) (imprimeProntuario(prontuario));
	else ((void)fprintf(stdout, "Paciente nao encontrado.\n\n"));
}

void ConsultarData(Arvore_t arvore) {
	Data_t data = (Data_t)malloc(sizeof(struct Data_s));
	int dia, mes, ano;
	(void)fprintf(stdout, "Digite a data (DD/MM/AAAA): ");
	(void)fscanf(stdin, "%d/%d/%d%*c", &dia, &mes, &ano);
	data = novaData(data, ano, mes, dia);
	if (!(data)) {
		(void)fprintf(stdout, "Data invalida\n");
		return;
	}


	(void)fprintf(stdout, "Pacientes:\n");
	acessaProntuarioArvoreRecursivo(arvore->raiz, data);
	(void)fprintf(stdout, "\n");
	liberaData(data);
}

void InserirConsulta(Arvore_t arvore) {
	Data_t data = (Data_t)malloc(sizeof(struct Data_s));
	int dia, mes, ano;
	(void)fprintf(stdout, "Digite a data da consulta (DD/MM/AAAA): ");
	(void)fscanf(stdin, "%d/%d/%d%*c", &dia, &mes, &ano);
	data = novaData(data, ano, mes, dia);
	if (!(data)) {
		(void)fprintf(stdout, "Data invalida\n");
		return;
	}

	char nome[MAX_STRING];
	(void)fprintf(stdout, "Digite o nome do paciente: ");
	fgets(nome, MAX_STRING, stdin);
	nome[strlen(nome) - 1] = '\0';
	
	Prontuario_t prontuario = arvoreBuscaProntuario(arvore, nome);

	char observacao[MAX_STRING];
	(void)fprintf(stdout, "Digite uma observacao sobre a consulta: ");
	fgets(observacao, MAX_STRING, stdin);
	observacao[strlen(observacao) - 1] = '\0';

	Consulta_t consulta = novaConsulta(observacao, nome);

	if (prontuario == NULL) {
		prontuario = novoProntuario(nome);
		criaNoArvore(arvore, prontuario);
	}
	insereConsultaProntuario(prontuario, consulta);
	(void)fprintf(stdout, "A consulta foi computada.\n");
}

void RemoverProntuario(Arvore_t arvore) {
	char nome[MAX_STRING];
	(void)fprintf(stdout, "Digite o nome do paciente: ");
	fgets(nome, MAX_STRING, stdin);
	nome[strlen(nome) - 1] = '\0';
	Prontuario_t prontuario = novoProntuario(nome);
	Prontuario_t prontuarioAux = removeArvore(arvore, prontuario);
	if (prontuarioAux) {
		(void)fprintf(stdout, "O paciente foi removido.\n");
		liberaProntuario(prontuarioAux);
	}
	liberaProntuario(prontuario);
}