/**
* @file main.c
* @brief Arquivo com a implementação das funções de inicialização do programa.
* @author Amanda Bueno
* @date 2021-07-10
*/

/* Inclusões */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "funcoes.h"

/* Tipos */
typedef void (*operacoesMenu)(Arvore_t);

/* Funções */
void imprimeDisplayInicial() {
	system("cls");
	(void)fprintf(stdout,
		"8 888888888o   8 888888888o.      ,o888888o.     b.             8 8888888 8888888888 8 8888      88        .8.          8 888888888o.    8 8888     ,o888888o.     \n"
	    "8 8888    `88. 8 8888    `88.  . 8888     `88.   888o.          8       8 8888       8 8888      88       .888.         8 8888    `88.   8 8888  . 8888     `88.   \n"
	    "8 8888     `88 8 8888     `88 ,8 8888       `8b  Y88888o.       8       8 8888       8 8888      88      :88888.        8 8888     `88   8 8888 ,8 8888       `8b  \n"
	    "8 8888     ,88 8 8888     ,88 88 8888        `8b .`Y888888o.    8       8 8888       8 8888      88     . `88888.       8 8888     ,88   8 8888 88 8888        `8b \n"
	    "8 8888.   ,88' 8 8888.   ,88' 88 8888         88 8o. `Y888888o. 8       8 8888       8 8888      88    .8. `88888.      8 8888.   ,88'   8 8888 88 8888         88 \n"
	    "8 888888888P'  8 888888888P'  88 8888         88 8`Y8o. `Y88888o8       8 8888       8 8888      88   .8`8. `88888.     8 888888888P'    8 8888 88 8888         88 \n"
	    "8 8888         8 8888`8b      88 8888        ,8P 8   `Y8o. `Y8888       8 8888       8 8888      88  .8' `8. `88888.    8 8888`8b        8 8888 88 8888        ,8P \n"
	    "8 8888         8 8888 `8b.    `8 8888       ,8P  8      `Y8o. `Y8       8 8888       ` 8888     ,8P .8'   `8. `88888.   8 8888 `8b.      8 8888 `8 8888       ,8P  \n" 
		"8 8888         8 8888   `8b.   ` 8888     ,88'   8         `Y8o.`       8 8888         8888   ,d8P .888888888. `88888.  8 8888   `8b.    8 8888  ` 8888     ,88'   \n"
		"8 8888         8 8888     `88.    `8888888P'     8            `Yo       8 8888          `Y88888P' .8'       `8. `88888. 8 8888     `88.  8 8888     `8888888P'     \n\n"
		"`8.`888b           ,8'  8 8888 8 888888888o. 8888888 8888888888 8 8888      88        .8.          8 8888        \n"
		" `8.`888b         ,8'   8 8888 8 8888    `88.      8 8888       8 8888      88       .888.         8 8888        \n"
		"  `8.`888b       ,8'    8 8888 8 8888     `88      8 8888       8 8888      88      :88888.        8 8888        \n"
		"   `8.`888b     ,8'     8 8888 8 8888     ,88      8 8888       8 8888      88     . `88888.       8 8888        \n"
		"    `8.`888b   ,8'      8 8888 8 8888.   ,88'      8 8888       8 8888      88    .8. `88888.      8 8888        \n"
		"     `8.`888b ,8'       8 8888 8 888888888P'       8 8888       8 8888      88   .8`8. `88888.     8 8888        \n"
		"      `8.`888b8'        8 8888 8 8888`8b           8 8888       8 8888      88  .8' `8. `88888.    8 8888        \n"
		"       `8.`888'         8 8888 8 8888 `8b.         8 8888       ` 8888     ,8P .8'   `8. `88888.   8 8888        \n"
		"        `8.`8'          8 8888 8 8888   `8b.       8 8888         8888   ,d8P .888888888. `88888.  8 8888        \n"
		"         `8.`           8 8888 8 8888     `88.     8 8888          `Y88888P' .8'       `8. `88888. 8 888888888888\n");

	(void)fprintf(stdout, "\n\n+------------------------------------------+\n"
		                  "|     Bem-vindo ao prontuario virtual!     |\n"
		                  "| Selecione uma das opcoes do menu abaixo. |\n"
		                  "+------------------------------------------+\n\n\n");
}

int selecionaOperacao() {
	int operacao;
	(void)fprintf(stdout, "******************************\n"
		                  " Menu:\n"
		                  " 0 - Encerrar o programa\n"
		                  " 1 - Consultar um paciente\n"
		                  " 2 - Consultar data\n"
		                  " 3 - Inserir consulta\n"
		                  " 4 - Remover prontuario\n"
		                  "******************************\n\n");
	(void)fprintf(stdout, "Digite o valor da operacao que deseja realizar\n> ");
	(void)fscanf(stdin, "%d%*c", &operacao);

	if ((operacao > 4) || (operacao < 0)) {
		(void)fprintf(stdout, "Operacao invalida\n> ");
		return NULL;
	}
	else return operacao;
}

void executaOperacao(Arvore_t arvore, int operacao) {

}

int main(int agrc, char* agrv[]) {
	const operacoesMenu funcoes[] = { ConsultarPaciente, ConsultarData, InserirConsulta, RemoverProntuario };
	int operacao = -1;

	Arvore_t arvore = criaArvore();

	while (operacao != 0) {
		imprimeDisplayInicial();
		operacao = selecionaOperacao();
		if (!operacao) break;
		funcoes[operacao - 1](arvore);
		system("pause");
		system("cls");
	}

	liberaArvore(arvore);

	return 0;
}