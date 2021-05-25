#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

int tempoDeExecucao = 0;

float turnaround(int *tFinal, int *tInicio, int qtdProcessos){
	float soma=0;
	float tmr;
	int i;
	for (i=0;i<qtdProcessos;i++){
		soma+=tFinal[i] - tInicio[i];
	}
	tmr = soma/qtdProcessos;
	return tmr;
}

float tempoEspera (int *tFinal, int *tInicio, int *tExecucao, int qtdProcessos){
	float soma=0;
	float tme;
	int i;
	for (i=0;i<qtdProcessos;i++){
		soma+=tFinal[i] - tExecucao[i] - tInicio[i];
	}
	tme = soma/qtdProcessos;
	return tme;
}



void rr (int *tFinal, int *tInicio, int *tExecucao, int *id, int qtdProcessos, int quantum ){
	int i=0, y=qtdProcessos, j, soma=0;
	
	int *tRestante = (int*) malloc (qtdProcessos*sizeof(int));
	
	for (i=0; i<qtdProcessos; i++) tRestante[i] = tExecucao[i];
	
	for (i=0; y!=0; ){
		printf ("P%d ", id[i]);
		
		if (tRestante[i] <= quantum && tRestante[i]>0){
			
		}
	}
}

void imprimeTeste(int teste,int *tFinal, int *tInicio, int *tExecucao, int *id, int qtdProcessos ){
	int i;
	printf ("Teste %d\n", teste);
	printf ("Tempo médio de execução: %fs\n", turnaround(tFinal, tInicio, qtdProcessos));
	printf ("Tempo médio de espera: %fs\n", tempoEspera(tFinal, tInicio, tExecucao, qtdProcessos));
	
	for (i = 0; i<qtdProcessos; i++){
		printf("P%d ", id[i]);
	}
	printf ("\n");
}


int main(){
	setlocale(LC_ALL, "Portuguese");\
	int qtdProcessos = 1, teste=1, i, j, k=0;
	int *tempoDeInicio, *tempoFinal, *tempoExecucao, *id, *tRestante,soma=0;
	int quantum, nProcessosRR=0;  
	scanf("%d", &quantum);
	while (qtdProcessos != 0){
		tempoDeExecucao = 0;
		
		scanf ("%d", &qtdProcessos);
		if (qtdProcessos == 0) break;
		
		id = (int*) malloc (qtdProcessos * sizeof(int));
		tempoDeInicio = (int*) malloc (qtdProcessos * sizeof(int));
		tempoFinal = (int*) malloc (qtdProcessos * sizeof(int));
		tempoExecucao = (int*) malloc (qtdProcessos * sizeof(int));
		tRestante = (int*) malloc (qtdProcessos * sizeof(int));
		
		if ((id != NULL && tempoDeInicio!=NULL) 
			&& (tempoFinal!=NULL && tempoExecucao!=NULL)){
			
			for (i = 0; i<qtdProcessos; i++){
				scanf("%d %d", &tempoDeInicio[i], &tempoExecucao[i]);
				id[i] = i+1;
				
				tRestante[i] = tempoExecucao[i];
				
				if (quantum % 2 == 0)
					if (tempoExecucao[i]%2==0)
						nProcessosRR += tempoExecucao[i]/2;
					else nProcessosRR += tempoExecucao[i]/2 +1;
				else
					if (tempoExecucao[i]%2==1)
						nProcessosRR += tempoExecucao[i]/2 +1;
					else nProcessosRR += tempoExecucao[i]/2;
			}
			
			printf ("Tamanho final de processos rr: %d\n", nProcessosRR);
			
			int *idRR = (int*) malloc (nProcessosRR*sizeof(int));
			int *tFinalRR = (int*) malloc (nProcessosRR*sizeof(int));
			
		
			for (i = 0; i<nProcessosRR; i++){
				printf("P%d ", idRR[i]);
			}
			
		//	rr(tempoFinal,tempoDeInicio,tempoExecucao,id,qtdProcessos, quantum);
		//	imprimeTeste(teste++,tempoFinal,tempoDeInicio,tempoExecucao,id,qtdProcessos);
		}
	}
}
