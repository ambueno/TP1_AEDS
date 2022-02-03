/* Inclusões */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

 /* Constantes */
#define SUCESSO 0
#define MAX_STRING (29+1)

/* Tipos */
// estrutura que representa um tipo ingrediente
typedef struct ingrediente_s {
	char nome[MAX_STRING];
	int codigo;
	int criacao;
} ingrediente_t;

// estrutura que representa um tipo de ingrediente de receita, armazenando o codigo do ingrediente e sua quantidade na receita
typedef struct receita_ingrediente_s {
	int codigo;
	int quantidade;
} receita_ingrediente_t;

// estrutura que representa um tipo receita
typedef struct receita_s {
	char nome[MAX_STRING];
	int codigo;
	int criacao;
	int nIngredientes;
	receita_ingrediente_t* receitaIngrediente;
} receita_t;

// estrutura que representa um tipo lista de ingredientes, 
// contendo um vetor dinamico do tipo ingrediente_t e um inteiro 
// que armazena o tamanho do vetor
typedef struct listaIngredientes_s {
	ingrediente_t* listaIngredientes;
	int tamanho;
} listaIngredientes_t;

// estrutura que representa um tipo lista de receitas, 
// contendo um vetor dinamico do tipo receita_t e um inteiro 
// que armazena o tamanho do vetor
typedef struct listaReceitas_s {
	receita_t* listaReceitas;
	int tamanho;
} listaReceitas_t;

// tipos de ponteiro de funcao
typedef void (*operacoesMenu)(listaReceitas_t*, listaIngredientes_t*);
typedef void (*ordenaIngredientes)(listaIngredientes_t*);
typedef void (*ordenaReceitas)(listaReceitas_t*, listaIngredientes_t*);
typedef void (*ordenaReceitasIngredientes)(listaReceitas_t*, listaIngredientes_t*, int);
typedef void (*ordenaIngredientesReceitas)(listaIngredientes_t*, receita_t*, receita_ingrediente_t*);

/* Funções */

// funções de ordenação
// implementação do quicksort para ordenação de strings
void swapString(const char** stringX, const char** stringY) {
	const char* temporaria = *stringX;
	*stringX = *stringY;
	*stringY = temporaria;
}

void quicksortString(char const** vetorString, int tamanho) {
	int pivot = 0;
	if (tamanho <= 1) return;

	for (int i = 0; i < tamanho; i++) {
		// a funcao strcmp funciona como uma funcao particiona
		if (strcmp(vetorString[i], vetorString[tamanho - 1]) < 0) swapString(vetorString + i, vetorString + pivot++);
	}
	swapString(vetorString + pivot, vetorString + tamanho - 1);

	quicksortString(vetorString, pivot++);
	quicksortString(vetorString + pivot, tamanho - pivot);
}

// implementação do quicksort para ordenação de inteiros
// a implentacao utilizada foi a apresentada na aula
// troca as posicoes de 2 interios
void swap(int* x, int* y) {
	int temporaria = *x;
	*x = *y;
	*y = temporaria;
}

int particiona(int* vetor, int low, int high) {
	int pivot = vetor[high];
	int i = (low - 1);

	for (int j = low; j < high; j++) {
		if (vetor[j] <= pivot) {
			i++;
			swap(&vetor[i], &vetor[j]);
		}
	}

	swap(&vetor[i + 1], &vetor[high]);
	return (i + 1);
}

// implementacao recursiva do quicksort com chamada para os valores menores e os maiores que o pivot 
void quicksort(int* vetor, int low, int high) {
	if (low < high) {
		int pivot = particiona(vetor, low, high);
		quicksort(vetor, low, pivot - 1);
		quicksort(vetor, pivot + 1, high);
	}
}

// funções para manipulação dos ingredientes 
// aloca espaço na memória para a lista de ingredientes
void alocarIngrediente(listaIngredientes_t* lista) {
	// contabiliza o tamanho da lista, ou seja, quantos elementos há no vetor de ingredientes, incrementando a cada novo ingrediente a ser inserido na lista 
	(lista->tamanho)++;
	// realoca o ponteiro, adaptando para o novo tamanho da lista
	lista->listaIngredientes = (ingrediente_t*)realloc((lista->listaIngredientes), (lista->tamanho) * sizeof(ingrediente_t));
}

// inicializa ingrediente fora do cadastro
void inicializarIngrediente(listaIngredientes_t *lista, char *nome, int codigo, int criacao, int quantidade) {
    strcpy(lista->listaIngredientes[(lista->tamanho) - 1].nome, nome);
    lista->listaIngredientes[(lista->tamanho) - 1].codigo = codigo;
    lista->listaIngredientes[(lista->tamanho) - 1].criacao = criacao;
}

// interage com o usuario para receber os dados e os armazena na memoria 
void cadastrarIngrediente(listaReceitas_t* listaReceitas, listaIngredientes_t* lista) {
	// realoca a receita
	alocarIngrediente(lista);
	// recebe os dados e inicializa na memoria 
	(void)fprintf(stdout, "> Cadastro de ingrediente:\n");
	(void)fprintf(stdout, "Digite o nome do ingrediente: ");
	fgets(lista->listaIngredientes[(lista->tamanho) - 1].nome, MAX_STRING, stdin);
	lista->listaIngredientes[(lista->tamanho) - 1].nome[strlen(lista->listaIngredientes[(lista->tamanho) - 1].nome) - 1] = '\0';
	(void)fprintf(stdout, "Digite um codigo para o ingrediente (Obs.: Cada ingrediente deve possuir um codigo unico): ");
	(void)fscanf(stdin, "%d%*c", &(lista->listaIngredientes[(lista->tamanho) - 1].codigo));
	//(void)fprintf(stdout, "Digite a quantidade do ingrediente: ");
	//(void)fscanf(stdin, "%d%*c", &(lista->listaIngredientes[(lista->tamanho) - 1].quantidade));
	lista->listaIngredientes[(lista->tamanho) - 1].criacao = lista->tamanho;
}

// procura um ingrediente na lista através de seu código 
ingrediente_t* buscarIngredienteCodigo(listaIngredientes_t* lista, int codigo) {
	// percorre a lista ate o ingrediente ser encontrado
	for (int i = 0; i < (lista->tamanho); i++) {
		// armazena o codigo do ingrediente atual 
		int atual = lista->listaIngredientes[i].codigo;
		// se o codigo atual é igual àquele que estamos procurando significa que encontramos
		if (atual == codigo) {
			//retorna o ponteiro para o ingrediente que possui o codigo procurado 
			return &(lista->listaIngredientes[i]);
		}
	}
}

// procura um ingrediente na lista através de seu nome
ingrediente_t* buscarIngredienteDescricao(listaIngredientes_t* lista, const char* descricao) {
	// percorre a lista ate o ingrediente ser encontrado
	for (int i = 0; i < (lista->tamanho); i++) {
		// armazena o nome do ingrediente atual 
		int atual = lista->listaIngredientes[i].nome;
		// se o nome atual é igual àquele que estamos procurando significa que encontramos
		if ((strcmp((lista->listaIngredientes[i].nome), descricao)) == 0) {
			//retorna o ponteiro para o ingrediente que possui o nome procurado 
			return &(lista->listaIngredientes[i]);
		}
	}
}

// procura um ingrediente na lista através do seu numero de criacao, ou seja, da sua posicao quando foi inicializado no vetor 
ingrediente_t* buscarIngredienteCriacao(listaIngredientes_t* lista, int cadastro) {
	// percorre a lista ate o ingrediente ser encontrado
	for (int i = 0; i < (lista->tamanho); i++) {
		// armazena o numero de criacao do ingrediente atual 
		int atual = lista->listaIngredientes[i].criacao;
		// se o numero atual é igual àquele que estamos procurando significa que encontramos
		if (atual == cadastro) {
			//retorna o ponteiro para o ingrediente que possui o numero procurado 
			return &(lista->listaIngredientes[i]);
		}
	}
}

// imprime todos os ingredientes de uma lista de ingredientes 
void imprimirIngredientes(listaIngredientes_t* lista) {
	(void)fprintf(stdout, "Codigo  | Ingrediente\n");
	// percorre toda a lista 
	for (int i = 0; i < (lista->tamanho); i++) {
		// imprime os dados
		(void)fprintf(stdout, "%-8d| %s\n", (lista->listaIngredientes[i].codigo), (lista->listaIngredientes[i].nome));
	}
}

// imprime todos os ingredientes de uma lista de ingredientes ordenados por seu codigo 
void listarIngredientesCodigo(listaIngredientes_t* lista) {
	// cria um vetor de inteiros com todos os codigos dos ingredientes da lista de ingredientes
	int* vetor = (int*)malloc(lista->tamanho * sizeof(int));
	for (int i = 0; i < (lista->tamanho); i++) {
		vetor[i] = (lista->listaIngredientes[i].codigo);
	}
	// ordena esse vetor 
	quicksort(vetor, 0, lista->tamanho - 1);

	(void)fprintf(stdout, "Codigo  | Ingrediente\n");
	// percorre toda lista de ingredientes, buscando o ingrediente pelo codigo, seguindo a ordem do vetor ordenado e imprime seus dados
	ingrediente_t* ingrediente;
	for (int i = 0; i < lista->tamanho; i++) {
		ingrediente = buscarIngredienteCodigo(lista, vetor[i]);
		// imprime os dados do ingrediente que possui o codigo da atual posicao no vetor
		(void)fprintf(stdout, "%-8d| %s\n", (ingrediente->codigo), (ingrediente->nome));
	}

	// libera a memoria alocada 
	free(vetor);
}

// imprime todos os ingredientes de uma lista de ingredientes ordenados, em ordem alfabética, por sua descricao
void listarIngredientesDescricao(listaIngredientes_t* lista) {
	// cria um vetor de strings com todos os nomes dos ingredientes da lista de ingredientes
	const char** vetor = (char**)malloc(lista->tamanho * sizeof(char*));
	for (int i = 0; i < lista->tamanho; i++) {
		vetor[i] = (char*)malloc(MAX_STRING * sizeof(char));
	}

	for (int i = 0; i < (lista->tamanho); i++) {
		strcpy(vetor[i], lista->listaIngredientes[i].nome);
	}
	// ordena esse vetor 
	quicksortString(vetor, lista->tamanho);

	(void)fprintf(stdout, "Codigo  | Ingrediente\n");
	// percorre toda lista de ingredientes, buscando o ingrediente pelo nome, seguindo a ordem do vetor ordenado e imprime seus dados
	ingrediente_t* ingrediente;
	for (int i = 0; i < lista->tamanho; i++) {
		ingrediente = buscarIngredienteDescricao(lista, vetor[i]);
		// imprime os dados do ingrediente que possui o codigo da atual posicao no vetor
		(void)fprintf(stdout, "%-8d| %s\n", (ingrediente->codigo), (ingrediente->nome));
	}

	// libera a memoria alocada 
	for (int i = 0; i < (lista->tamanho); i++) {
		free(vetor[i]);
	}
	free(vetor);
}

// imprime todos os ingredientes de uma lista de ingredientes ordenados pela ordem de criacao
void listarIngredientesCriacao(listaIngredientes_t* lista) {
	// cria um vetor de inteiros com todos os numeros de ordem de criacao dos ingredientes da lista de ingredientes
	int* vetor = (int*)malloc(lista->tamanho * sizeof(int));
	for (int i = 0; i < (lista->tamanho); i++) {
		vetor[i] = (lista->listaIngredientes[i].criacao);
	}
	// ordena esse vetor
	quicksort(vetor, 0, lista->tamanho - 1);

	(void)fprintf(stdout, "Codigo  | Ingrediente\n");
	// percorre toda lista de ingredientes, buscando o ingrediente pelo numero de criacao, seguindo a ordem do vetor ordenado e imprime seus dados
	ingrediente_t* ingrediente;
	for (int i = 0; i < lista->tamanho; i++) {
		ingrediente = buscarIngredienteCriacao(lista, vetor[i]);
		// imprime os dados do ingrediente que possui o codigo da atual posicao no vetor
		(void)fprintf(stdout, "%-8d| %s\n", (ingrediente->codigo), (ingrediente->nome));
	}

	// libera a memoria alocada 
	free(vetor);
}

// interage com o usuario para receber o valor da operacao que desejar realizar 
int selecionarOrdenacaoIngredientes() {
	int operacao;
	(void)fprintf(stdout, "Escolha a ordem em que gostaria que os ingredientes cadastrados sejam listados: \n"
		" 1 - Ordenados por ordem de codigo\n"
		" 2 - Ordenados por ordem de descricao\n"
		" 3 - Ordenados por ordem de criacao\n");
	(void)fprintf(stdout, "Digite o valor desejado\n> ");
	(void)fscanf(stdin, "%d%*c", &operacao);

	// verifica se a operacao é valida 
	if ((operacao > 3) || (operacao < 1)) {
		(void)fprintf(stdout, "Operacao invalida\n> ");
		return NULL;
	}

	// retorna a operacao desejada
	else return operacao;
}

// chama a funcao que corresponde à operacao selecionada pelo usuário 
void listarIngredientes(listaReceitas_t* listaReceitas, listaIngredientes_t* listaIngredientes) {
	// vetor do tipo ponteiro de funcao contendo as operacoes de listar ingredientes para diferentes parametros de ordenacao
	const ordenaIngredientes funcoes[] = { listarIngredientesCodigo,  listarIngredientesDescricao, listarIngredientesCriacao };
	// recebe o valor da operacao 
	int operacao = selecionarOrdenacaoIngredientes();
	if (!operacao) return;
	// chama a funcao do vetor respectiva à operacao desejada 
	funcoes[operacao - 1](listaIngredientes);
}

// funções para manipulação das receitas
// aloca espaço na memória para a lista de receitas
void alocarReceita(listaReceitas_t* lista) {
	// contabiliza o tamanho da lista, ou seja, quantos elementos há no vetor de receitas, incrementando a cada nova receita a ser inserida na lista 
	(lista->tamanho)++;
	// realoca o ponteiro, adaptando para o novo tamanho da lista
	lista->listaReceitas = (receita_t*)realloc((lista->listaReceitas), (lista->tamanho) * sizeof(receita_t));
}

// inicializa receita fora do cadastro
void inicializarReceita(listaReceitas_t* lista, char* nome, int codigo, int criacao, int nIngredientes, int* ingredientes) {
	strcpy(lista->listaReceitas[(lista->tamanho) - 1].nome, nome);
	lista->listaReceitas[(lista->tamanho) - 1].codigo = codigo;
	lista->listaReceitas[(lista->tamanho) - 1].criacao = criacao;
	lista->listaReceitas[(lista->tamanho) - 1].nIngredientes = nIngredientes;
}

// interage com o usuario para receber os dados e os armazena na memoria 
void cadastrarReceita(listaReceitas_t* lista, listaIngredientes_t* listaIngredientes) {
	// realoca a receita
	alocarReceita(lista);
	receita_t* receita = &lista->listaReceitas[(lista->tamanho) - 1];
	// recebe os dados e inicializa na memoria 
	(void)fprintf(stdout, "> Cadastro de receita:\n");
	(void)fprintf(stdout, "Digite o nome da receita: ");
	fgets(receita->nome, MAX_STRING, stdin);
	receita->nome[strlen(receita->nome) - 1] = '\0';
	(void)fprintf(stdout, "Digite um codigo para a receita (Obs.: Cada ingrediente deve possuir um codigo unico): ");
	(void)fscanf(stdin, "%d%*c", &(receita->codigo));
	(void)fprintf(stdout, "Ingredientes disponiveis:\n ");
	imprimirIngredientes(listaIngredientes);
	(void)fprintf(stdout, "Digite o numero de ingredientes que a receita possui: ");
	(void)fscanf(stdin, "%d%*c", &(receita->nIngredientes));

	receita->receitaIngrediente = (receita_ingrediente_t*)malloc(receita->nIngredientes * sizeof(receita_ingrediente_t));
	char* nomeAux = (char*)malloc(MAX_STRING * sizeof(char));
	ingrediente_t* ingredienteAux;
	// cada receita possui um vetor de inteiros onde são armazenados os códigos dos ingredientes que ela possui
	for (int i = 0; i < receita->nIngredientes; i++) {
		// recebe o nome do ingrediente que a receita possui
		(void)fprintf(stdout, "Digite o nome do %d ingrediente: ", i + 1);
		fgets(nomeAux, MAX_STRING, stdin);
		nomeAux[strlen(nomeAux) - 1] = '\0';
		// busca o ingrediente pelo nome na lista de ingredentes 
		ingredienteAux = buscarIngredienteDescricao(listaIngredientes, nomeAux);
		// salva o codigo do ingrediente no vetor
		receita->receitaIngrediente[i].codigo = ingredienteAux->codigo;
		(void)fprintf(stdout, "Digite a quantidade desse ingrediente: ");
		// salva a quantidade do ingrediente utilizada na receita
		(void)fscanf(stdin, "%d%*c", &(receita->receitaIngrediente[i].quantidade));
	}
	(void)fprintf(stdout, "\n");
	receita->criacao = lista->tamanho;

	// libera a memoria alocada 
	free(nomeAux);
}

// procura uma receita na lista através de seu código 
receita_t* buscarReceitaCodigo(listaReceitas_t* lista, int codigo) {
	// percorre a lista ate o ingrediente ser encontrado
	for (int i = 0; i < (lista->tamanho); i++) {
		// armazena o codigo do ingrediente atual 
		int atual = lista->listaReceitas[i].codigo;
		// se o codigo atual é igual àquele que estamos procurando significa que encontramos
		if (atual == codigo) {
			//retorna o ponteiro para o ingrediente que possui o codigo procurado 
			return &(lista->listaReceitas[i]);
		}
	}
}

// procura uma receita na lista através de seu nome 
receita_t* buscarReceitaDescricao(listaReceitas_t* lista, const char* descricao) {
	// percorre a lista ate o ingrediente ser encontrado
	for (int i = 0; i < (lista->tamanho); i++) {
		// armazena o nome do ingrediente atual 
		int atual = lista->listaReceitas[i].nome;
		// se o nome atual é igual àquele que estamos procurando significa que encontramos
		if ((strcmp((lista->listaReceitas[i].nome), descricao)) == 0) {
			//retorna o ponteiro para o ingrediente que possui o nome procurado 
			return &(lista->listaReceitas[i]);
		}
	}
}

// procura uma receita na lista através de seu numero de criacao 
receita_t* buscarReceitaCriacao(listaReceitas_t* lista, int criacao) {
	// percorre a lista ate o ingrediente ser encontrado
	for (int i = 0; i < (lista->tamanho); i++) {
		// armazena o numero de criacao do ingrediente atual 
		int atual = lista->listaReceitas[i].criacao;
		// se o numero de criacao é igual àquele que estamos procurando significa que encontramos
		if (atual == criacao) {
			//retorna o ponteiro para o ingrediente que possui o numero de criacao procurado 
			return &(lista->listaReceitas[i]);
		}
	}
}

// imprime todas as receitas de uma lista de receitas
void imprimirReceitas(listaReceitas_t* lista) {
	(void)fprintf(stdout, "Codigo  | Receita\n");
	for (int i = 0; i < (lista->tamanho); i++) {
		(void)fprintf(stdout, "%-8d| %s\n", (lista->listaReceitas[i].codigo), (lista->listaReceitas[i].nome));
	}
}

// imprime todas as de uma lista de receitas ordenadas por seu codigo 
void listarReceitasCodigo(listaReceitas_t* lista) {
	// cria um vetor de inteiros com todos os codigos das receitas da lista de receitas
	int* vetor = (int*)malloc(lista->tamanho * sizeof(int));
	for (int i = 0; i < (lista->tamanho); i++) {
		vetor[i] = (lista->listaReceitas[i].codigo);
	}
	// ordena esse vetor
	quicksort(vetor, 0, lista->tamanho - 1);

	(void)fprintf(stdout, "Codigo  | Receita\n");
	receita_t* receita;
	// percorre toda lista de receitas, buscando a receita pelo codigo, seguindo a ordem do vetor ordenado e imprime seus dados
	for (int i = 0; i < lista->tamanho; i++) {
		receita = (receita_t*)buscarReceitaCodigo(lista, vetor[i]);
		// imprime os dados da receita que possui o codigo da atual posicao no vetor
		(void)fprintf(stdout, "%-8d| %s\n", (receita->codigo), (receita->nome));
	}

	// libera a memoria alocada 
	free(vetor);
}

// imprime todas as de uma lista de receitas ordenadas por seu nome
void listarReceitasDescricao(listaReceitas_t* lista) {
	// cria um vetor de strings com todos os nomes das receitas da lista de receitas
	const char** vetor = (char**)malloc(lista->tamanho * sizeof(char*));
	for (int i = 0; i < lista->tamanho; i++) {
		vetor[i] = (char*)malloc(MAX_STRING * sizeof(char));
	}
	for (int i = 0; i < (lista->tamanho); i++) {
		strcpy(vetor[i], lista->listaReceitas[i].nome);
	}
	// ordena esse vetor
	quicksortString(vetor, lista->tamanho);

	(void)fprintf(stdout, "Codigo  | Receita\n");
	receita_t* receita;
	// percorre toda lista de receitas, buscando a receita pelo nome, seguindo a ordem do vetor ordenado e imprime seus dados
	for (int i = 0; i < lista->tamanho; i++) {
		receita = (receita_t*)buscarReceitaDescricao(lista, vetor[i]);
		// imprime os dados da receita que possui o nome da atual posicao no vetor
		(void)fprintf(stdout, "%-8d| %s\n", (receita->codigo), (receita->nome));
	}

	// libera a memoria alocada 
	for (int i = 0; i < (lista->tamanho); i++) {
		free(vetor[i]);
	}
	free(vetor);
}

// imprime todas as de uma lista de receitas ordenadas por seu numero de criacao
void listarReceitasCriacao(listaReceitas_t* lista) {
	// cria um vetor de inteiros com todos os numeros de criacao das receitas da lista de receitas
	int* vetor = (int*)malloc(lista->tamanho * sizeof(int));
	for (int i = 0; i < lista->tamanho; i++) {
		vetor[i] = (lista->listaReceitas[i].criacao);
	}
	// ordena esse vetor
	quicksort(vetor, 0, lista->tamanho - 1);

	(void)fprintf(stdout, "Codigo  | Receita\n");
	receita_t* receita;
	// percorre toda lista de receitas, buscando a receita pelo numero de criacao, seguindo a ordem do vetor ordenado e imprime seus dados
	for (int i = 0; i < lista->tamanho; i++) {
		receita = (receita_t*)buscarReceitaCriacao(lista, vetor[i]);
		// imprime os dados da receita que possui o numero de criacao da atual posicao no vetor
		(void)fprintf(stdout, "%-8d| %s\n", (receita->codigo), (receita->nome));
	}

	// libera a memoria alocada 
	free(vetor);
}

// interage com o usuario para receber o valor da operacao que desejar realizar 
int selecionarOrdenacaoReceitas() {
	int operacao;
	(void)fprintf(stdout, "Escolha a ordem em que gostaria que as receitas cadastradas sejam listadas: \n"
		" 1 - Ordenadas por ordem de codigo\n"
		" 2 - Ordenadas por ordem de descricao\n"
		" 3 - Ordenadas por ordem de criacao\n");
	(void)fprintf(stdout, "Digite o valor desejado\n> ");
	(void)fscanf(stdin, "%d%*c", &operacao);

	// verifica se a operacao é valida 
	if ((operacao > 3) || (operacao < 1)) {
		(void)fprintf(stdout, "Operacao invalida\n> ");
		return NULL;
	}

	//  retorna a operacao desejada 
	else return operacao;
}

// chama a funcao que corresponde à operacao selecionada pelo usuário
void listarReceitas(listaReceitas_t* listaReceitas, listaIngredientes_t* listaIngredientes) {
	const ordenaReceitas funcoes[] = { listarReceitasCodigo,  listarReceitasDescricao, listarReceitasCriacao };
	// recebe o valor da operacao
	int operacao = selecionarOrdenacaoReceitas();
	if (!operacao) return;
	// chama a funcao do vetor respectiva à operacao desejada 
	funcoes[operacao - 1](listaReceitas, listaIngredientes);
	system("pause");
	system("cls");
}

// cria uma lista de ingredientes temporaria a partir dos codigos deles
listaIngredientes_t* criarListaIngredientes(receita_t* receita, listaIngredientes_t* lIngredientes) {
	listaIngredientes_t* lista = (listaIngredientes_t*)malloc(sizeof(listaIngredientes_t));
	lista->listaIngredientes = (ingrediente_t*)malloc(receita->nIngredientes * sizeof(ingrediente_t));
	// percorre todos os ingredientes da receita 
	for (int i = 0; i < receita->nIngredientes; i++) {
		// para cada codigo de ingrediente salvo da receita é feita uma busca na lista de ingredientes 
// é retornado o ponteiro para esse ingrediente, que por sua vez, é adicionado à lista de ingredientes 
		lista->listaIngredientes[i] = *buscarIngredienteCodigo(lIngredientes, receita->receitaIngrediente[i].codigo);
	}
	lista->tamanho = receita->nIngredientes;
	// retorna a lista de ingredientes
	return lista;
}

// procura um ingrediente na lista de ingredientes da receita através do código 
receita_ingrediente_t* buscarIngredienteReceitaCodigo(receita_t* receita, receita_ingrediente_t* receitaIngrediente, int codigo) {
	// percorre a lista ate o ingrediente ser encontrado
	for (int i = 0; i < (receita->nIngredientes); i++) {
		// armazena o codigo do ingrediente atual 
		int atual = receita->receitaIngrediente[i].codigo;
		// se o codigo atual é igual àquele que estamos procurando significa que encontramos
		if (atual == codigo) {
			//retorna o ponteiro para o ingrediente que possui o codigo procurado 
			return &(receita->receitaIngrediente[i]);
		}
	}
}

// imprime todos os ingredientes de uma lista de ingredientes ordenados por seu codigo 
void listarIngredientesReceitasCodigo(listaIngredientes_t* lista, receita_t* receita, receita_ingrediente_t* receitaIngrediente) {
	// cria um vetor de inteiros com todos os codigos dos ingredientes da lista de ingredientes
	int* vetor = (int*)malloc(lista->tamanho * sizeof(int));
	for (int i = 0; i < (lista->tamanho); i++) {
		vetor[i] = (lista->listaIngredientes[i].codigo);
	}
	// ordena esse vetor 
	quicksort(vetor, 0, lista->tamanho - 1);

	(void)fprintf(stdout, "Codigo  | Quantidade | Ingrediente\n");
	// percorre toda lista de ingredientes, buscando o ingrediente pelo codigo, seguindo a ordem do vetor ordenado e imprime seus dados
	ingrediente_t* ingrediente;
	receita_ingrediente_t* qntdIngrediente;
	for (int i = 0; i < lista->tamanho; i++) {
		ingrediente = buscarIngredienteCodigo(lista, vetor[i]);
		qntdIngrediente = buscarIngredienteReceitaCodigo(receita, receitaIngrediente, vetor[i]);
		// imprime os dados do ingrediente que possui o codigo da atual posicao no vetor
		(void)fprintf(stdout, "%-8d| %-10d |%s\n", (ingrediente->codigo), (qntdIngrediente->quantidade), (ingrediente->nome));
	}

	// libera a memória alocada 
	free(vetor);
}

// imprime todos os ingredientes de uma lista de ingredientes ordenados, em ordem alfabética, por sua descricao
void listarIngredientesReceitasDescricao(listaIngredientes_t* lista, receita_t* receita, receita_ingrediente_t* receitaIngrediente) {
	// cria um vetor de strings com todos os nomes dos ingredientes da lista de ingredientes
	const char** vetor = (char**)malloc(lista->tamanho * sizeof(char*));
	for (int i = 0; i < lista->tamanho; i++) {
		vetor[i] = (char*)malloc(MAX_STRING * sizeof(char));
	}

	for (int i = 0; i < (lista->tamanho); i++) {
		strcpy(vetor[i], lista->listaIngredientes[i].nome);
	}
	// ordena esse vetor 
	quicksortString(vetor, lista->tamanho);

	(void)fprintf(stdout, "Codigo  | Quantidade | Ingrediente\n");
	// percorre toda lista de ingredientes, buscando o ingrediente pelo nome, seguindo a ordem do vetor ordenado e imprime seus dados
	ingrediente_t* ingrediente;
	receita_ingrediente_t* qntdIngrediente;
	for (int i = 0; i < lista->tamanho; i++) {
		ingrediente = buscarIngredienteDescricao(lista, vetor[i]);
		qntdIngrediente = buscarIngredienteReceitaCodigo(receita, receitaIngrediente, ingrediente->codigo);
		// imprime os dados do ingrediente que possui o codigo da atual posicao no vetor
		(void)fprintf(stdout, "%-8d| %-10d | %s\n", (ingrediente->codigo), (qntdIngrediente->quantidade), (ingrediente->nome));
	}

	// libera a memória alocada
	for (int i = 0; i < (lista->tamanho); i++) {
		free(vetor[i]);
	}
	free(vetor);
}

// imprime todos os ingredientes de uma lista de ingredientes ordenados pela ordem de criacao
void listarIngredientesReceitasCriacao(listaIngredientes_t* lista, receita_t* receita, receita_ingrediente_t* receitaIngrediente) {
	// cria um vetor de inteiros com todos os numeros de ordem de criacao dos ingredientes da lista de ingredientes
	int* vetor = (int*)malloc(lista->tamanho * sizeof(int));
	for (int i = 0; i < (lista->tamanho); i++) {
		vetor[i] = (lista->listaIngredientes[i].criacao);
	}
	// ordena esse vetor
	quicksort(vetor, 0, lista->tamanho - 1);

	(void)fprintf(stdout, "Codigo  | Quantidade | Ingrediente\n");
	// percorre toda lista de ingredientes, buscando o ingrediente pelo numero de criacao, seguindo a ordem do vetor ordenado e imprime seus dados
	ingrediente_t* ingrediente;
	receita_ingrediente_t* qntdIngrediente;
	for (int i = 0; i < lista->tamanho; i++) {
		ingrediente = buscarIngredienteCriacao(lista, vetor[i]);
		qntdIngrediente = buscarIngredienteReceitaCodigo(receita, receitaIngrediente, ingrediente->codigo);
		// imprime os dados do ingrediente que possui o codigo da atual posicao no vetor
		(void)fprintf(stdout, "%-8d| %-10d |%s\n", (ingrediente->codigo), (qntdIngrediente->quantidade), (ingrediente->nome));
	}

	// libera a memória alocada 
	free(vetor);
}

// imprime todos as receitas ordenadas por ordem de codigo e seus respectivos ingredientes pela ordem selecionada no vetor
void listarReceitasIngredientesCodigo(listaReceitas_t* lReceitas, listaIngredientes_t* lIngredientes, int operacaoIngredientes) {
	const ordenaIngredientesReceitas funcoes[] = { listarIngredientesReceitasCodigo,  listarIngredientesReceitasDescricao, listarIngredientesReceitasCriacao };
	// cria um vetor de inteiros com todos os numeros de ordem de criacao dos ingredientes da lista de ingredientes
	int* vetorReceitas = (int*)malloc(lReceitas->tamanho * sizeof(int));
	for (int i = 0; i < (lReceitas->tamanho); i++) {
		vetorReceitas[i] = (lReceitas->listaReceitas[i].codigo);
	}
	// ordena esse vetor
	quicksort(vetorReceitas, 0, lReceitas->tamanho - 1);

	receita_t* receita;
	for (int i = 0; i < lReceitas->tamanho; i++) {
		receita = (receita_t*)buscarReceitaCodigo(lReceitas, vetorReceitas[i]);
		(void)fprintf(stdout, "%-8d| %s\n", (receita->codigo), (receita->nome));
		listaIngredientes_t* listaIngredientesReceita;
		(void)fprintf(stdout, "Ingredientes:\n");
		listaIngredientesReceita = criarListaIngredientes(receita, lIngredientes);
		funcoes[operacaoIngredientes - 1](listaIngredientesReceita, receita, receita->receitaIngrediente);
		free(listaIngredientesReceita->listaIngredientes);
		free(listaIngredientesReceita);
		(void)fprintf(stdout, "\n");
	}

	// libera a memória alocada 
	free(vetorReceitas);
}

void listarReceitasIngredientesDescricao(listaReceitas_t* lReceitas, listaIngredientes_t* lIngredientes, int operacaoIngredientes) {
	const ordenaIngredientesReceitas funcoes[] = { listarIngredientesReceitasCodigo,  listarIngredientesReceitasDescricao, listarIngredientesReceitasCriacao };
	const char** vetorReceitas = (char**)malloc(lReceitas->tamanho * sizeof(char*));
	for (int i = 0; i < (lReceitas->tamanho); i++) {
		vetorReceitas[i] = (char*)malloc(MAX_STRING * sizeof(char));
		strcpy(vetorReceitas[i], lReceitas->listaReceitas[i].nome);
	}
	// ordena o vetor
	quicksortString(vetorReceitas, lReceitas->tamanho);

	receita_t* receita;
	for (int i = 0; i < lReceitas->tamanho; i++) {
		receita = (receita_t*)buscarReceitaDescricao(lReceitas, vetorReceitas[i]);
		(void)fprintf(stdout, "%-8d| %s\n", (receita->codigo), (receita->nome));
		listaIngredientes_t* listaIngredientesReceita;
		(void)fprintf(stdout, "Ingredientes:\n");
		listaIngredientesReceita = criarListaIngredientes(receita, lIngredientes);
		funcoes[operacaoIngredientes - 1](listaIngredientesReceita, receita, receita->receitaIngrediente);
		free(listaIngredientesReceita->listaIngredientes);
		free(listaIngredientesReceita);
		(void)fprintf(stdout, "\n");
	}

	for (int i = 0; i < (lReceitas->tamanho); i++) {
		free(vetorReceitas[i]);
	}

	// libera a memoria alocada
	free(vetorReceitas);
}

void listarReceitasIngredientesCriacao(listaReceitas_t* lReceitas, listaIngredientes_t* lIngredientes, int operacaoIngredientes) {
	const ordenaIngredientesReceitas funcoes[] = { listarIngredientesReceitasCodigo,  listarIngredientesReceitasDescricao, listarIngredientesReceitasCriacao };
	int* vetorReceitas = (int*)malloc(lReceitas->tamanho * sizeof(int));
	for (int i = 0; i < (lReceitas->tamanho); i++) {
		vetorReceitas[i] = (lReceitas->listaReceitas[i].criacao);
	}
	// ordena o vetor
	quicksort(vetorReceitas, 0, lReceitas->tamanho - 1);

	receita_t* receita;
	for (int i = 0; i < lReceitas->tamanho; i++) {
		receita = (receita_t*)buscarReceitaCriacao(lReceitas, vetorReceitas[i]);
		(void)fprintf(stdout, "%-8d| %s\n", (receita->codigo), (receita->nome));
		listaIngredientes_t* listaIngredientesReceita;
		(void)fprintf(stdout, "Ingredientes:\n");
		listaIngredientesReceita = criarListaIngredientes(receita, lIngredientes);
		funcoes[operacaoIngredientes - 1](listaIngredientesReceita, receita, receita->receitaIngrediente);
		free(listaIngredientesReceita->listaIngredientes);
		free(listaIngredientesReceita);
		(void)fprintf(stdout, "\n");
	}

	// libera a memória alocada 
	free(vetorReceitas);
}

// interage com o usuario para receber o valor da operacao que desejar realizar 
int selecionarOrdenacaoReceitasIngredientes(int operacao[2]) {
	(void)fprintf(stdout, "Escolha a ordem em que gostaria que as receitas cadastradas sejam listadas: \n"
		" 1 - Ordenadas por ordem de codigo\n"
		" 2 - Ordenadas por ordem de descricaoo\n"
		" 3 - Ordenadas por ordem de criacao\n");
	(void)fprintf(stdout, "Digite o valor desejado\n> ");
	(void)fscanf(stdin, "%d%*c", &operacao[0]);
	(void)fprintf(stdout, "Agora, escolha a ordem em que gostaria que os ingredientes de cada receita sejam listados: \n"
		" 1 - Ordenados por ordem de codigo\n"
		" 2 - Ordenados por ordem de descricao\n"
		" 3 - Ordenados por ordem de criacao\n");
	(void)fprintf(stdout, "Digite o valor desejado\n> ");
	(void)fscanf(stdin, "%d%*c", &operacao[1]);

	// verifica se a operacao é válida 
	if ((operacao[0] > 3) || (operacao[0] < 1) || (operacao[1] > 3) || (operacao[1] < 1)) {
		(void)fprintf(stdout, "Operacao invalida\n> ");
		return 0;
	}
	else return 1;
}

// chama a funcao que corresponde à operacao selecionada pelo usuário
void listarReceitasIngredientes(listaReceitas_t* listaReceitas, listaIngredientes_t* listaIngredientes) {
	const ordenaReceitasIngredientes funcoes[] = { listarReceitasIngredientesCodigo,  listarReceitasIngredientesDescricao, listarReceitasIngredientesCriacao };
	int operacao[2];
	int resultado = selecionarOrdenacaoReceitasIngredientes(operacao);
	if (!resultado) return;
	funcoes[operacao[0] - 1](listaReceitas, listaIngredientes, operacao[1]);
	system("pause");
	system("cls");
}

// interage com o usuario para receber o valor da operacao que desejar realizar 
int selecionaOperacao() {
	int operacao;
	(void)fprintf(stdout, "******************************\n"
		" Menu:\n"
		" 0 - Encerrar o programa\n"
		" 1 - Cadastrar ingrediente\n"
		" 2 - Listar ingredientes\n"
		" 3 - Cadastrar receita\n"
		" 4 - Listar receitas\n"
		" 5 - Listar todas as receitas cadastradas, com seus respectivos ingredientes ordenados\n"
		"******************************\n\n");
	(void)fprintf(stdout, "Digite o valor da operacao que deseja realizar\n> ");
	(void)fscanf(stdin, "%d%*c", &operacao);

	if ((operacao > 5) || (operacao < 0)) {
		(void)fprintf(stdout, "Operacao invalida\n> ");
		return NULL;
	}
	else return operacao;
}

// inicializa uma lista de ingredientes na memória
void inicializaLista(listaIngredientes_t* lista) {
	char const* ingredientes[] = {
		"Mussarela",
		"Massa",
		"Frango",
		"Presunto",
		"Palmito",
		"Tomate",
		"Pimentao",
		"Granulado",
		"M&M",
		"Peperoni",
		"Calabresa",
		"Catupiry",
		"Azeitona",
		"Parmesao",
		"Oregano",
		"Molho de Tomate",
		"Ketchup",
		"Azeite",
		"Sorvete",
		"Bacon",
		"Cheddar",
		"Gorgonzola",
		"Provolone",
		"Cebola"
	};
	const int tamanho = sizeof(ingredientes) / sizeof(*ingredientes);
	lista->tamanho = tamanho;
	lista->listaIngredientes = (ingrediente_t*)realloc(lista->listaIngredientes, tamanho * sizeof(ingrediente_t));
	for (int i = 0; i < tamanho; i++) {
		strcpy(lista->listaIngredientes[i].nome, ingredientes[i]);
		lista->listaIngredientes[i].codigo = i;
		lista->listaIngredientes[i].criacao = i;
	}
}

// lê os dados do arquivo a salva na memoria 
void lerArquivo(FILE* arquivo, listaReceitas_t* listaReceitas, listaIngredientes_t* listaIngredientes) {
	(void)fscanf(arquivo, "%d %d ", &(listaIngredientes->tamanho), &(listaReceitas->tamanho));
	listaIngredientes->listaIngredientes = (ingrediente_t*)realloc(
		listaIngredientes->listaIngredientes, listaIngredientes->tamanho * sizeof(ingrediente_t));
	listaReceitas->listaReceitas = (receita_t*)realloc(
		listaReceitas->listaReceitas, listaReceitas->tamanho * sizeof(receita_t));
	for (int i = 0; i < listaIngredientes->tamanho; i++) {
		fgets(listaIngredientes->listaIngredientes[i].nome, MAX_STRING, arquivo);
		listaIngredientes->listaIngredientes[i].nome[strlen(listaIngredientes->listaIngredientes[i].nome) - 1] = '\0';
		(void)fscanf(arquivo, "%d %d ", &(listaIngredientes->listaIngredientes[i].codigo), &(listaIngredientes->listaIngredientes[i].criacao));
	}
	for (int i = 0; i < listaReceitas->tamanho; i++) {
		fgets(listaReceitas->listaReceitas[i].nome, MAX_STRING, arquivo);
		listaReceitas->listaReceitas[i].nome[strlen(listaReceitas->listaReceitas[i].nome) - 1] = '\0';
		(void)fscanf(arquivo, "%d %d %d ", &(listaReceitas->listaReceitas[i].codigo), &(listaReceitas->listaReceitas[i].criacao), &(listaReceitas->listaReceitas[i].nIngredientes));
		listaReceitas->listaReceitas[i].receitaIngrediente = (receita_ingrediente_t*)
			malloc(listaReceitas->listaReceitas[i].nIngredientes * sizeof(receita_ingrediente_t));
		for (int j = 0; j < listaReceitas->listaReceitas[i].nIngredientes; j++) {
			(void)fscanf(arquivo, "%d ", &(listaReceitas->listaReceitas[i].receitaIngrediente[j].codigo));
		}
		for (int j = 0; j < listaReceitas->listaReceitas[i].nIngredientes; j++) {
			(void)fscanf(arquivo, "%d ", &(listaReceitas->listaReceitas[i].receitaIngrediente[j].quantidade));
		}
	}

}

// lê os dados da memória e salva no arquivo
void escreverArquivo(FILE* arquivo, listaReceitas_t* listaReceitas, listaIngredientes_t* listaIngredientes) {
	(void)fprintf(arquivo, "%d %d ", (listaIngredientes->tamanho), (listaReceitas->tamanho));
	for (int i = 0; i < listaIngredientes->tamanho; i++) {
		(void)fprintf(arquivo, "%s\n%d %d\n", (listaIngredientes->listaIngredientes[i].nome), (listaIngredientes->listaIngredientes[i].codigo), (listaIngredientes->listaIngredientes[i].criacao));
	}
	for (int i = 0; i < listaReceitas->tamanho; i++) {
		(void)fprintf(arquivo, "%s\n%d %d %d\n", (listaReceitas->listaReceitas[i].nome), (listaReceitas->listaReceitas[i].codigo), (listaReceitas->listaReceitas[i].criacao), (listaReceitas->listaReceitas[i].nIngredientes));
		for (int j = 0; j < listaReceitas->listaReceitas[i].nIngredientes; j++) {
			(void)fprintf(arquivo, "%d ", (listaReceitas->listaReceitas[i].receitaIngrediente[j].codigo));
		}
		for (int j = 0; j < listaReceitas->listaReceitas[i].nIngredientes; j++) {
			(void)fprintf(arquivo, "%d ", (listaReceitas->listaReceitas[i].receitaIngrediente[j].quantidade));
		}
		(void)fprintf(arquivo, "\n");
	}
}

// MAIN
int main(int argc, char* argv[]) {
	FILE* arquivo;
	const char* caminhoArquivo = "./pizzaria.bin";

	const operacoesMenu funcoes[] = { cadastrarIngrediente, listarIngredientes, cadastrarReceita, listarReceitas, listarReceitasIngredientes };
	int operacao = -1;

	listaIngredientes_t* listaIngredientes;
	listaReceitas_t* listaReceitas;

	listaIngredientes = (listaIngredientes_t*)malloc(sizeof(listaIngredientes_t));
	listaReceitas = (listaReceitas_t*)malloc(sizeof(listaReceitas_t));

	listaIngredientes->tamanho = 0;
	listaIngredientes->listaIngredientes = NULL;
	listaReceitas->tamanho = 0;
	listaReceitas->listaReceitas = NULL;

	// abre o arquivo para leitura 
	arquivo = fopen(caminhoArquivo, "rb");

	// se o arquivo já exisitr 
	if (arquivo != NULL) {
		// lê o arquivo e inicializa para a memória
		lerArquivo(arquivo, listaReceitas, listaIngredientes);
		// fecha o arquivo
		fclose(arquivo);
	}
	else {
		// se o arquivo não existir 
		// inicializa a memória com a lista padronizada 
		inicializaLista(listaIngredientes);
	}

	// executa as operacoes selecionadas pelo usuario
	while (operacao != 0) {
		operacao = selecionaOperacao();
		if (!operacao) break;
		funcoes[operacao - 1](listaReceitas, listaIngredientes);
		system("pause");
		system("cls");
	}

	// abre o arquivo para escrita
	arquivo = fopen(caminhoArquivo, "wb");

	// escreve o conteudo das listas para o arquivo
	escreverArquivo(arquivo, listaReceitas, listaIngredientes);

	// fecha o arquivo 
	fclose(arquivo);

	// libera a memoria alocada 
	for (int i = 0; i < listaReceitas->tamanho; i++) {
		free(listaReceitas->listaReceitas[i].receitaIngrediente);
	}
	free(listaReceitas->listaReceitas);
	free(listaReceitas);

	free(listaIngredientes->listaIngredientes);
	free(listaIngredientes);

	// se chegou até aqui é porque tudo deu certo
	return SUCESSO;
}
