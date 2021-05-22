//rr scheduling
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

//lista de processos duplamente encadeada
typedef struct processo{
	int id; //P1 , P2, P3 .... PN
	int instanteInicio;
	int tempoDeExecucao;
	int tempoFinal; //tempo final na timeline
	int tempoRestante;
	int statusFinal;
	struct processo *prox;
}ProcessoElem;

typedef struct {
	ProcessoElem *primeiro;
	int tExecucaoProcessamento;
	int processosEmFila;
}Processos;


//funï¿½ï¿½o para criar processo
ProcessoElem* criaProcesso(int idProcesso, int inicio, int tempoExecucao);

//inicializar o escalonamento
Processos* criaEscalonamento();
void inserirProcesso(Processos*, ProcessoElem*);

//imprimir o escalonamento de acordo com o FCFS - FIFO
void saidaEscalonamento(ProcessoElem*);
void saidaTempoFinal(ProcessoElem* processoElem);

//liberar o escalonamento da memÃ³ria
void terminarEscalonamento(ProcessoElem*);

//calcular turnaround e tempo de espera mÃ©dio
double turnaround(ProcessoElem* processoElem, double qtdProcessos);
double tempoEsperaMedio(ProcessoElem* processoElem, double qtdProcessos);

//escalonamento round-robin
void rr (Processos*, Processos*, int quantum);
void insereProcessoNoQuantum(ProcessoElem*, Processos*, int quantum);


int main(){
	setlocale(LC_ALL,"portuguese");
	FILE *arquivo = fopen("casos-teste.txt","r");
	
	int i, inicio, execucao, idTeste=1, quantum;
	double qtdElementos=1;
	Processos *processos, *resultadoProcessos;
	
	fscanf(arquivo,"%d", &quantum);
	
	while(qtdElementos!=0){
		
		fscanf(arquivo,"%lf",&qtdElementos);
		
		if (qtdElementos==0) break;
		
		processos = criaEscalonamento();
		processos->processosEmFila = qtdElementos;
		resultadoProcessos = criaEscalonamento();
		
		
		for (i=0;i<qtdElementos;i++){
			fscanf(arquivo, "%d %d",&inicio, &execucao);
			inserirProcesso(processos, criaProcesso(i+1,inicio,execucao));
		}
		
		rr(processos, resultadoProcessos, quantum);
		
		printf ("\n\nTeste %d\n",idTeste++);
		printf ("Tempo médio de execução: %.2lfs\n", turnaround(processos->primeiro,qtdElementos));
		printf ("Tempo médio de espera: %.2lfs\n", tempoEsperaMedio(processos->primeiro,qtdElementos));
		saidaEscalonamento(resultadoProcessos->primeiro);
		//saidaTempoFinal(resultadoProcessos->primeiro);
		printf("\n");
		terminarEscalonamento(processos->primeiro);
		terminarEscalonamento(resultadoProcessos->primeiro);
	}
	fclose(arquivo);
}


ProcessoElem* criaProcesso(int idProcesso, int inicio, int tempoExecucao){
	ProcessoElem *p = (ProcessoElem*) malloc (sizeof(ProcessoElem));
	if (p!=NULL){
		
		p->id = idProcesso;
		p->instanteInicio = inicio;
		p->tempoDeExecucao = tempoExecucao;
		p->tempoRestante;
		p->statusFinal=0;
		p->tempoFinal = 0;
		p->prox = NULL;
	}	
	return p;
}

Processos* criaEscalonamento(){
	Processos *escalonamento = (Processos*) malloc (sizeof(Processos));	
	if (escalonamento!=NULL){
		escalonamento->primeiro = NULL;
		escalonamento->tExecucaoProcessamento = 0;
		escalonamento->processosEmFila = 0;
	}
	return escalonamento;
}

void inserirProcesso(Processos* processos, ProcessoElem* novoProcessoElem){
	ProcessoElem *ant=NULL, *atual = processos->primeiro;
	printf ("NUMERO DE PROCESSOS EM EXECUCAO: [%d]\n", processos->processosEmFila);
	if (processos->primeiro==NULL){
		processos->primeiro = novoProcessoElem;
		novoProcessoElem->tempoFinal = novoProcessoElem->instanteInicio + novoProcessoElem->tempoDeExecucao;
		processos->tExecucaoProcessamento = novoProcessoElem->instanteInicio;
		processos->processosEmFila += 1;
	}
	else{
		while (atual!=NULL){
			ant = atual;
			atual = atual->prox;
		}
		
		int tempoOcioso = 0;
		 
		ant->prox = novoProcessoElem;
		
		if (novoProcessoElem->tempoRestante == novoProcessoElem->tempoDeExecucao) 
			novoProcessoElem->statusFinal = 1;
			
		if (ant->tempoFinal < ant->prox->instanteInicio){
			tempoOcioso = ant->prox->instanteInicio - ant->tempoFinal;
			novoProcessoElem->tempoFinal = ant->tempoFinal + tempoOcioso + novoProcessoElem->tempoDeExecucao;		
		}else{
			novoProcessoElem->tempoFinal = ant->tempoFinal + novoProcessoElem->tempoDeExecucao;
		}
		
		novoProcessoElem->prox = atual;	
		processos->processosEmFila += 1;
	}
	processos->tExecucaoProcessamento += novoProcessoElem->tempoDeExecucao;	
}

void saidaEscalonamento(ProcessoElem* processoElem){
	if(processoElem!=NULL){
		printf ("P%d ", processoElem->id);
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

void rr (Processos* listaPronto, Processos* listaExecucao, int quantum){
	ProcessoElem *atual = listaPronto->primeiro;
	ProcessoElem *copia = listaExecucao->primeiro;
	ProcessoElem *aux = NULL;
	
	while(atual!=NULL && listaPronto->processosEmFila!=0){
		printf ("processos dentro da execucao: [%d]\n", listaPronto->processosEmFila);
		
		if (atual->tempoRestante==0) {
			listaPronto->processosEmFila -= 1;
		}
		
		if (atual->statusFinal == 0){
			insereProcessoNoQuantum(atual,listaExecucao, quantum);
			printf ("insere P%d na lista\n",atual->id);
		}
		else {
			atual = atual->prox;
			listaPronto->processosEmFila += atual->instanteInicio <= listaExecucao->tExecucaoProcessamento ? 1 : 0;
		}
		
		atual = atual->prox;
		
		if (atual == NULL && listaPronto->processosEmFila!=0)
			atual = listaPronto->primeiro;
		
		
	}
	saidaEscalonamento(listaExecucao->primeiro);	
}

void insereProcessoNoQuantum(ProcessoElem* atual, Processos* listaExecucao, int quantum){
	//inserir processo quantum
	if (atual->tempoRestante == quantum){
		inserirProcesso(listaExecucao, criaProcesso(atual->id, atual->instanteInicio, quantum));
		atual->tempoRestante -= quantum;
		atual->statusFinal=1;
	}else if (atual->tempoRestante > quantum) { 
		inserirProcesso(listaExecucao, criaProcesso(atual->id, atual->instanteInicio, quantum));
		atual->tempoRestante -= quantum;
	}else{
		inserirProcesso(listaExecucao, criaProcesso(atual->id, atual->instanteInicio, atual->tempoRestante));
		atual->tempoRestante -= atual->tempoRestante;
		atual->statusFinal = 1;
	}
}
