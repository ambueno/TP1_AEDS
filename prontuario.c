/**
 * @file   prontuario.c
 * @brief  Arquivo com a implementação do TAD das estruturas de dados que compõe o prontuario.
 * @author Amanda Bueno
* @date 2021-07-10
 */

 /* Inclusões */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "prontuario.h"

/* Constantes */
#define MIN_ANO 1900
#define MAX_ANO 2025
#define MIN_MES 1
#define MAX_MES 12
#define MIN_DIA 1
#define MAX_DIA 31

#define TRUE (1==1)
#define FALSE (!TRUE)

#define MAX_STRING 256
/* Tipos */
//typedef char String[MAX_STRING];

typedef unsigned char bool_t;

/* Funções auxiliares */
void liberaString(char *string){
	free(string);
}

/* Manipulção da estrutura Data*/
static bool_t eBissexto(int ano) {
	if ((((ano % 4) == 0) && !((ano % 100) == 0)) || ((ano % 400) == 0)) return TRUE;
	return FALSE;
}

static bool_t dataValida(Data_t data) {
	if ((data->ano < MIN_ANO) || (data->ano > MAX_ANO)) return FALSE;
	if ((data->mes < MIN_MES) || (data->mes > MAX_MES)) return FALSE;
	if ((data->dia < MIN_DIA) || (data->dia > MAX_DIA)) return FALSE;

	if (data->mes == 2) {
		if (eBissexto(data->ano)) {
			if (data->dia > (MAX_DIA - 2)) return FALSE;
		}
		if (data->dia > (MAX_DIA - 3)) return FALSE;
	}

	if (data->mes == 4 || data->mes == 6 || data->mes == 9 || data->mes == 11) {
		if (data->mes > (MAX_MES - 1)) return FALSE;
	}

	return TRUE;
}

 Data_t novaData(Data_t data, int ano, int mes, int dia){
	data->ano = ano;
	data->mes = mes;
	data->dia = dia;
	if(dataValida) return data;
	return NULL;
}

void liberaData(Data_t data) {
	free(data);
}

int comparaData(Data_t dataComparada, Data_t dataReferencia) {
	int tempoTotal1 = dataComparada->dia + (dataComparada->mes * MAX_DIA) + (dataComparada->ano * MAX_DIA * MAX_MES + 1); // numero total de dias
	int tempoTotal2 = dataReferencia->dia + (dataReferencia->mes * MAX_DIA) + (dataReferencia->ano * MAX_DIA * MAX_MES + 1); // numero total de dias 
	return tempoTotal1 - tempoTotal2;
}

static void imprimeData(Data_t data){
	(void)fprintf(stdout, "[%d/%d%d]\n", data->dia, data->mes, data->ano);
}

/* Manipulção da estrutura Consulta */
Consulta_t novaConsulta(char *observacao, Data_t data) {
    Consulta_t consulta = (Consulta_t)malloc(sizeof(struct Consulta_s));
	if(!data) (data = novaData(data, data->dia, data->mes, data->dia));
	consulta->data = data;
	
	consulta->observacao = (char*)malloc(sizeof(strlen(observacao) + 1)); // aloca espaço para o tamanho exato da string 
	strcpy(consulta->observacao, observacao);

	if (consulta) return consulta;
	return NULL;
}

void liberaConsulta(Consulta_t consulta) {
	liberaData(consulta->data);
	liberaString(consulta->observacao);
	free(consulta);
}

int comparaConsulta(Consulta_t consultaComparada, Consulta_t consultaReferencia) {
	return comparaData(consultaComparada->data, consultaReferencia->data);
}

void imprimeConsulta(Consulta_t consulta) {
	imprimeData(consulta->data);
	(void)fprintf(stdout, "%s\n", consulta->observacao);
}

/* Manipulção da estrutura Prontuario */
Prontuario_t novoProntuario(char *nome) {
	Prontuario_t prontuario = (Prontuario_t)malloc(sizeof(struct Prontuario_s));
	prontuario->nome = (char*)malloc(strlen(nome) + 1); // aloca o tamanho exato do nome
	strcpy(prontuario->nome, nome);
	prontuario->listaConsultas = novaLista();
	return prontuario;
}

void insereConsultaProntuario(Prontuario_t prontuario, void *consulta) {
	insereOrdenadoLista(prontuario->listaConsultas, consulta);
}

int comparaNomeProntuario(Prontuario_t prontuarioComparado, Prontuario_t prontuarioReferencia) {
	return strcmp(prontuarioComparado->nome, prontuarioReferencia->nome);
}

int comparaNome(char* nome, Prontuario_t prontuario){
	return strcmp(nome, prontuario->nome);
}

void imprimeProntuario(Prontuario_t prontuario) {
	(void)fprintf("Paciente '%s':\n", prontuario->nome);
	imprimeLista(prontuario->listaConsultas);
}

void imprimeProntuarioNomeData(Prontuario_t prontuario, Data_t data) {
	if (listaBuscaData(prontuario->listaConsultas, data)){
		printf("Paciente '%s'.\n", prontuario->nome);
	}
}

void liberaProntuario(Prontuario_t prontuario){
	liberaLista(prontuario->listaConsultas);
	free(prontuario->nome);
	free(prontuario);
}