#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

//lista de processos duplamente encadeada
typedef struct processo{
	char nomeProcesso[3]; //P1 , P2, P3 .... PN
	int instanteInicio;
	int tempoDeExecucao;
	int tempoFinal; //tempo final na timeline
	struct processo *prox;
	struct processo *ant;
}ProcessoElem;

typedef struct {
	ProcessoElem *primeiro;
	ProcessoElem *ultimo;
	int tempoDeEscalonamento;
}Processos;


//função para criar processo
ProcessoElem* criaProcesso(int idProcesso, int inicio, int tempoExecucao);

//inicializar o escalonamento
Processos* criaEscalonamento();
void inserirProcesso(Processos*, ProcessoElem*);

void sjf(Processos*, Processos*);

//imprimir o escalonamento de acordo com o SJF
void saidaEscalonamento(ProcessoElem*);
void saidaTempoFinal(ProcessoElem* processoElem);

//liberar o escalonamento da memória
void terminarEscalonamento(ProcessoElem*);

void removeProcesso(Processos*, ProcessoElem* );

//calcular turnaround e tempo de espera médio
double turnaround(ProcessoElem* processoElem, double qtdProcessos);
double tempoEsperaMedio(ProcessoElem* processoElem, double qtdProcessos);

int main(){
   	setlocale(LC_ALL,"portuguese");
	int i, inicio, execucao, idTeste=1;
	double qtdElementos=1;
	Processos *processos, *copia;
	
	while(qtdElementos!=0){
		scanf("%lf",&qtdElementos);
		
		if (qtdElementos==0) break;
		
		processos = criaEscalonamento();
        copia = criaEscalonamento();
		
		for (i=0;i<qtdElementos;i++){
			scanf("%d %d",&inicio, &execucao);
			inserirProcesso(processos, criaProcesso(i+1,inicio,execucao));
		}
		
        sjf(processos,copia);

		printf ("Teste %d\n",idTeste++);
		printf ("Tempo m�dio de retorno: %.4lf s\n", turnaround(copia->primeiro,qtdElementos));
		printf ("Tempo m�dio de espera: %.4lf s\n", tempoEsperaMedio(copia->primeiro,qtdElementos));
        saidaEscalonamento(copia->primeiro);
		
		printf("\n");
		saidaTempoFinal(copia->primeiro);
		printf("\n");
		
		terminarEscalonamento(processos->primeiro);
        terminarEscalonamento(copia->primeiro);
	}
    return 0;
}


ProcessoElem* criaProcesso(int idProcesso, int inicio, int tempoExecucao){
	ProcessoElem *p = (ProcessoElem*) malloc (sizeof(ProcessoElem));
	if (p!=NULL){
		char aux[2];
		sprintf (aux,"%d",idProcesso);
		strcpy(p->nomeProcesso,"P");
		strcat(p->nomeProcesso,aux);
		
		p->instanteInicio = inicio;
		p->tempoDeExecucao = tempoExecucao;
		p->tempoFinal = 0;
		p->prox = NULL;
		p->ant = NULL;
	}	
	return p;
}

Processos* criaEscalonamento(){
	Processos *escalonamento = (Processos*) malloc (sizeof(Processos));	

	if (escalonamento!=NULL){
		escalonamento->primeiro = NULL;
		escalonamento->ultimo = NULL;
		escalonamento->tempoDeEscalonamento = 0;
	}
	return escalonamento;
}

void inserirProcesso(Processos* processos, ProcessoElem* novoProcessoElem){
	ProcessoElem *ant=NULL, *atual = processos->primeiro;
	int tempoOcioso;

	if (processos->primeiro==NULL){
		processos->primeiro = novoProcessoElem;
		processos->ultimo = novoProcessoElem;
		novoProcessoElem->tempoFinal = novoProcessoElem->instanteInicio + novoProcessoElem->tempoDeExecucao;
		processos->tempoDeEscalonamento = novoProcessoElem->tempoFinal;
	}else{
		
		processos->ultimo->prox = novoProcessoElem;
		novoProcessoElem->ant = processos->ultimo;
		processos->ultimo = novoProcessoElem;
		novoProcessoElem->prox = NULL;
	/*
		tempoOcioso = 0;

		if (processos->tempoDeEscalonamento < novoProcessoElem->instanteInicio)
			tempoOcioso = novoProcessoElem->instanteInicio - processos->tempoDeEscalonamento;
	*/
		novoProcessoElem->tempoFinal = processos->tempoDeEscalonamento + novoProcessoElem->tempoDeExecucao;
		 
		processos->tempoDeEscalonamento += novoProcessoElem->tempoFinal;
	}
	
	
}


void saidaEscalonamento(ProcessoElem* processoElem){
	if(processoElem!=NULL){
		printf ("%s ", processoElem->nomeProcesso);
		//printf ("%s %d\n", processoElem->nomeProcesso, processoElem->tempoDeExecucao);
		saidaEscalonamento(processoElem->prox);
	}
}

void saidaTempoFinal(ProcessoElem* processoElem){
	if(processoElem!=NULL){
		printf ("%d ", processoElem->tempoFinal);
		saidaTempoFinal(processoElem->prox);
	}
}

void terminarEscalonamento(ProcessoElem* processoElem){
	ProcessoElem *atual=processoElem, *prox=NULL;
	
	while(atual!=NULL){
		prox=atual->prox;
		free(atual);
		atual=prox;	
	}
}

double turnaround(ProcessoElem* processoElem, double qtdProcessos){
	double soma=0;
	double tmr;
	ProcessoElem *atual=processoElem;
	while(atual!=NULL){
		soma += atual->tempoFinal - atual->instanteInicio;
		atual = atual->prox; 		
	}
	tmr = soma/qtdProcessos;
	return tmr;
}

double tempoEsperaMedio(ProcessoElem* processoElem, double qtdProcessos){
	double soma=0;
	double tme;
	
	ProcessoElem *atual = processoElem;
	while(atual!=NULL){
		int tempoFinal = atual->tempoFinal;
		int inicio = atual->instanteInicio;
		int tempoExecucao = atual->tempoDeExecucao;
		
		double aux = 0;
		aux = tempoFinal - (tempoExecucao + inicio);
		soma += aux;
		atual = atual->prox;
	}
	
	tme = soma/qtdProcessos;
	return tme;
}

void sjf(Processos* filaPronto, Processos* copia){
	ProcessoElem *menor, *ant, *prox, *aux, *atual, *novo;
	int i=1;
	atual = filaPronto->primeiro;
	novo = copia->primeiro;
	
	menor = ant = prox = aux = NULL;
	
	//outra tentativa no dia 13/05
	while(atual!=NULL){
		printf ("percorrendo lista %d vez\n", i++);
		printf ("FILA PRONTOS\n");
		saidaEscalonamento(filaPronto->primeiro);
		printf ("\nFILA DE EXECU��O\n");
		saidaEscalonamento(copia->primeiro);
		printf ("\n");
		
		menor = atual;
		
		aux = atual->prox;
		//loop para percorrer os elementos at� o tempo de execu��o atual
		while (aux!=NULL && aux->instanteInicio >= copia->tempoDeEscalonamento){
			printf ("comparando %s com %s no tempo %d\n", menor->nomeProcesso, aux->nomeProcesso, copia->tempoDeEscalonamento);
			if (aux->tempoDeExecucao < menor->tempoDeExecucao){
				
				menor = aux;
			}
			aux = aux->prox;
		}
	
	//	printf ("Trocando...\n");
		//insere o menor na fila de execu��o
		char idP[2], strAux[2];
    	strAux[0]=menor->nomeProcesso[1];
    	strAux[1]= '\0';
    	strcpy(idP, strAux); // pega o numero da string P1, P2, P[n]
    
		int idProcesso = atoi(idP);
		inserirProcesso(copia, criaProcesso(idProcesso, menor->instanteInicio, menor->tempoDeExecucao));
		
		
		removeProcesso(filaPronto, menor);
	
		atual = filaPronto->primeiro;
		
		
	}
	
}

void removeProcesso(Processos* filaPronto, ProcessoElem* processo){
//	printf ("remove processo: %s\n", processo->nomeProcesso);
	ProcessoElem *aux=NULL, *removeProcesso=NULL;
	if (filaPronto->primeiro == NULL) return;
	if (processo == filaPronto->primeiro){
		printf ("removendo %s processo do inicio\n", filaPronto->primeiro);
		removeProcesso = filaPronto->primeiro;
		filaPronto->primeiro = filaPronto->primeiro->prox;
	}else if (processo == filaPronto->ultimo){
	//	printf ("Removendo processo do fim\n");
		removeProcesso = filaPronto->ultimo;
		filaPronto->ultimo = filaPronto->ultimo->ant;
	}else{ // {p1(5) - p2(2)}=0
		//printf ("removendo processo do meio\n");
		aux = filaPronto->primeiro;
		while(aux!=processo && aux!=NULL)	aux = aux->prox; //para quando aux == processo
		
		aux->ant->prox = aux->prox;
		aux->prox->ant = aux->ant;
		removeProcesso = aux;
	}
	free(removeProcesso);
}
