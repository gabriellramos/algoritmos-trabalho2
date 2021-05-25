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
}ProcessoElem;

typedef struct {
	ProcessoElem *primeiro;
}Processos;


//fun��o para criar processo
ProcessoElem* criaProcesso(int idProcesso, int inicio, int tempoExecucao);

//inicializar o escalonamento
Processos* criaEscalonamento();
void inserirProcesso(Processos*, ProcessoElem*);

//imprimir o escalonamento de acordo com o FCFS - FIFO
void saidaEscalonamento(ProcessoElem*);
void saidaTempoFinal(ProcessoElem* processoElem);

//liberar o escalonamento da memória
void terminarEscalonamento(ProcessoElem*);

//calcular turnaround e tempo de espera médio
double turnaround(ProcessoElem* processoElem, double qtdProcessos);
double tempoEsperaMedio(ProcessoElem* processoElem, double qtdProcessos);

int main(){
	setlocale(LC_ALL,"portuguese");
	int i, inicio, execucao, idTeste=1;
	double qtdElementos=1;
	Processos *processos;
	
	while(qtdElementos!=0){
		scanf("%lf",&qtdElementos);
		
		if (qtdElementos==0) break;
		
		processos = criaEscalonamento();
		
		for (i=0;i<qtdElementos;i++){
			scanf("%d %d",&inicio, &execucao);
			inserirProcesso(processos, criaProcesso(i+1,inicio,execucao));
		}
		
		printf ("Teste %d\n",idTeste++);
		printf ("Tempo médio de execução: %.4lf s\n", turnaround(processos->primeiro,qtdElementos));
		printf ("Tempo médio de espera: %.4lf s\n", tempoEsperaMedio(processos->primeiro,qtdElementos));
		saidaEscalonamento(processos->primeiro);
		printf("\n");
		terminarEscalonamento(processos->primeiro);
	}
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
	}	
	return p;
}

Processos* criaEscalonamento(){
	Processos *escalonamento = (Processos*) malloc (sizeof(Processos));	
	if (escalonamento!=NULL){
		escalonamento->primeiro = NULL;
	}
	return escalonamento;
}

void inserirProcesso(Processos* processos, ProcessoElem* novoProcessoElem){
	ProcessoElem *ant=NULL, *atual = processos->primeiro;

	if (processos->primeiro==NULL){
		processos->primeiro = novoProcessoElem;
		novoProcessoElem->tempoFinal = novoProcessoElem->instanteInicio + novoProcessoElem->tempoDeExecucao;
	}
	else{
		while (atual!=NULL){
			ant = atual;
			atual = atual->prox;
		}
		
		int tempoOcioso = 0;
		 
		ant->prox = novoProcessoElem;
		if (ant->tempoFinal < ant->prox->instanteInicio){
			tempoOcioso = ant->prox->instanteInicio - ant->tempoFinal;
			novoProcessoElem->tempoFinal = ant->tempoFinal + tempoOcioso + novoProcessoElem->tempoDeExecucao;		
		}else{
			novoProcessoElem->tempoFinal = ant->tempoFinal + novoProcessoElem->tempoDeExecucao;
		}
		
		novoProcessoElem->prox = atual;
		
		
	}
}

void saidaEscalonamento(ProcessoElem* processoElem){
	if(processoElem!=NULL){
		printf ("%s ", processoElem->nomeProcesso);
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
