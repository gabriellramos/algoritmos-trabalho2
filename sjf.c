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

void sjf (int *tFinal, int *tInicio, int *tExecucao, int *id, int qtdProcessos ){
	int i, pos, j, k=0;
	for (i = 0; i<qtdProcessos; i++){
		pos = i;
		for (j=i+1; j<qtdProcessos; j++){
			if (tExecucao[j] < tExecucao[pos]){
				if (tInicio[j] <= tempoDeExecucao)
					pos = j;
			}
		}
		
		int tempoOcioso = 0;
		int aux = tExecucao[i];
		tExecucao[i] = tExecucao[pos];
		tExecucao[pos] = aux;
		
		aux = id[i];
		id[i] = id[pos];
		id[pos] = aux;
		
		aux = tInicio[i];
		tInicio[i] = tInicio[pos];
		tInicio[pos] = aux;
		
		if (tInicio[i] > tempoDeExecucao)
			tempoOcioso = tInicio[i] - tempoDeExecucao;
			
		tempoDeExecucao += tempoOcioso + tExecucao[i];
		tFinal[i] = tempoDeExecucao;
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
	int *tempoDeInicio, *tempoFinal, *tempoExecucao, *id, pos=0;
	while (qtdProcessos != 0){
		tempoDeExecucao = 0;
		scanf ("%d", &qtdProcessos);
		if (qtdProcessos == 0) break;
		
		id = (int*) malloc (qtdProcessos * sizeof(int));
		tempoDeInicio = (int*) malloc (qtdProcessos * sizeof(int));
		tempoFinal = (int*) malloc (qtdProcessos * sizeof(int));
		tempoExecucao = (int*) malloc (qtdProcessos * sizeof(int));
		
		if ((id != NULL && tempoDeInicio!=NULL) 
			&& (tempoFinal!=NULL && tempoExecucao!=NULL)){
			
			for (i = 0; i<qtdProcessos; i++){
				scanf("%d %d", &tempoDeInicio[i], &tempoExecucao[i]);
				id[i] = i+1;
			}
				
			sjf (tempoFinal,tempoDeInicio,tempoExecucao,id,qtdProcessos);
			imprimeTeste(teste++,tempoFinal,tempoDeInicio,tempoExecucao,id,qtdProcessos);
		}
	}
}
